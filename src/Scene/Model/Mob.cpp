#include "Mob.hpp"

#include "../../util/math.hpp"
#include "GameModelManager.hpp"
#include "../../ui/UiManager.hpp"

MobData::MobData(MobAiConstructor aiConstructor, float radius, float maxLife, float mass, SpriteId spriteId) {
    this->aiConstructor = aiConstructor;
    this->radius = radius;
    this->maxLife = maxLife;
    this->mass = mass;

    this->spriteId = spriteId;
}



Mob::Mob() : Mob(genericMobData, 0, 0) {}
Mob::Mob(const MobData &data, float x, float y)
        : Entity(x, y, 0, 0, data.maxLife)
        , data(&data) {

    ai = data.aiConstructor(); // May be nullptr
}
Mob::~Mob() {
    delete ai;
}

float Mob::getRadius() const { return data->radius; }
float Mob::getMaxLife() const { return data->maxLife; }
float Mob::getMass() const { return data->mass; }
Weapon* Mob::getWeapon(WeaponManagerWeaponId id) { return weapons.getWeapon(id); }
const Weapon* Mob::getWeapon(WeaponManagerWeaponId id) const { return weapons.getWeapon(id); }

WeaponManagerWeaponId Mob::addWeapon(const WeaponData &weaponData) {
    return weapons.addWeapon(weaponData);
}
bool Mob::removeWeapon(WeaponManagerWeaponId id) {
    return weapons.removeWeapon(id);
}

void Mob::fireAtPosition(WeaponManagerWeaponId weaponId, GameModelManager &model, float targetX, float targetY) {
    Weapon *weapon = weapons.getWeapon(weaponId);
    if (!weapon) return; // No weapon, abort

    // Get direction vector of target from this Entity
    float dirX = targetX - x,
          dirY = targetY - y;

    // Normalize direction vector
    float dist = getdist(dirX, dirY);
    dirX /= dist;
    dirY /= dist;

    float projectileOffset = getRadius() + weapon->data->projectileData->radius;
    float vel = weapon->data->projectileSpeed;

    weapon->fireUntilNotReady(model,
        x + dirX * projectileOffset,
        y + dirY * projectileOffset,
        dirX * vel,
        dirY * vel);
}
void Mob::fireAtEntity(WeaponManagerWeaponId weaponId, GameModelManager &model, const ImmovableEntity& target) {
    fireAtPosition(weaponId, model, target.x, target.y);
}
void Mob::leadAndFireAtEntity(WeaponManagerWeaponId weaponId, GameModelManager &model, const Entity& target) {
    Weapon *weapon = weapons.getWeapon(weaponId);
    if (!weapon) return; // No weapon, abort

    float targetVelX = target.getObservedVelX(),
          targetVelY = target.getObservedVelY();
    float targetSpeed = getdist(targetVelX, targetVelY);
    if (targetSpeed <= 0) { // If target is stationary, there's no leading to be had. Just deal with it normally and nothing more
        fireAtEntity(weaponId, model, target);
        return;
    }
    float targetVelDirX = targetVelX / targetSpeed,
          targetVelDirY = targetVelY / targetSpeed;

    float projectileSpeed = weapon->data->projectileSpeed;
    float projectileRadius = weapon->data->projectileData->radius;

    // p = projectile
    // e = target's current position
    // t = time till collision
    // .r = radius
    // r = distance compensation due to entity radii = this->r + 2*p.r + e.r
    float r = this->getRadius() + 2*projectileRadius + target.getRadius();
    // Have to solve for the new target position e' when t = (dist(this, e') - r) / p.speed, and e' = e + t*e.vel
    // We'll just solve for t, and derive e' from there

    // First, rewrite the coord system so that this mob is at the origin
    float targetX = target.x - x,
          targetY = target.y - y;
    // and +x is pointing in the direction of the target's velocity
    // (and it doesn't matter which direction +y is, as long as it's orthogonal to +x)
    {   float tx = targetX,
              ty = targetY;
        targetX = targetVelDirX * tx + targetVelDirY * ty; // Project (tx,ty) onto targetVelDir
        targetY = targetVelDirY * tx - targetVelDirX * ty; // Project (tx,ty) onto something orthonormal to targetVelDir
    }

    // Find t such that dist(e') - r = t * p.speed
    // e'.x^2 + e'.y^2 - r = t^2 * p.speed^2
    // (e.x + t * e.speed)^2 + e.y^2 - r = t^2 * p.speed^2
    // e.x^2 + 2*e.x*t*e.speed + t^2 * e.speed^2 + e.y^2 - r = t^2 * p.speed^2
    // Quadratic in t with a = e.speed^2 - p.speed^2, b = 2*e.x*e.speed, c = e.x^2 + e.y^2 - r
    float t = 0;
    {   float a = targetSpeed*targetSpeed - projectileSpeed*projectileSpeed;
        float b = 2 * targetX * targetSpeed;
        float c = getdist2(targetX, targetY) - r;

        float det = b*b - 4*a*c; // determinant

        if (det > 0) { // quadratic has 2 solutions
            float sqrtDet = sqrt(det);
            float two_a = 2*a;
            // The two solutions
            float t1 = (-b + sqrtDet) / two_a,
                  t2 = (-b - sqrtDet) / two_a;

            // Pick the least positive solution (want t to be positive so it's in the future, and low so that they get hit sooner)
            // Or if both are negative, just default to t = 0
            if (t1 < 0) {
                t = (t2 <  0) ?  0 : t2;
            } else {
                t = (t2 <  0) ? t1 :
                    (t2 < t1) ? t2 : t1;
            }
        } else if (det < 0) { // quadratic has no solution, so leave t = 0, i.e. just fire at the target's current position
            t = 0;
        } else { // det == 0 (almost never): one solution
            t = -b/(2*a);
            if (t < 0) t = 0; // Do check that the solution is non-negative
        }
    }

    // Find where the target will be after t has elapsed
    targetX = target.x + targetVelX * t;
    targetY = target.y + targetVelY * t;

    // Fire at that new position
    fireAtPosition(weaponId, model, targetX, targetY);
}

void Mob::doTick(GameModelManager& model) {
    // Invoke the AI to make decisions
    if (ai) ai->act(*this, model);

    // Move the Mob
    Entity::doTick(model);

    // Update the weapon cooldowns
    weapons.doTick();

    // Add drag
    float wantedVelX = 0,
          wantedVelY = 0;
    float maxVelChange = .1f;
    float vel = getdist(xvel - wantedVelX, yvel - wantedVelY);
    if (vel <= maxVelChange) {
        xvel = wantedVelX;
        yvel = wantedVelY;
    } else {
        float mod = (vel - maxVelChange) / vel;
        xvel = (xvel - wantedVelX)*mod + wantedVelX;
        yvel = (yvel - wantedVelY)*mod + wantedVelY;
    }
}

void Mob::draw(UiManager &uiManager) const {
    float a = getLifeFraction();
    uiManager.setColorMask({1, a, a});
    uiManager.setObjectScale(getRadius());
    uiManager.setAtlasPhase(true, uiManager.getUiTick() * .02f, 0);
    uiManager.drawSprite(x, y, data->spriteId);
}
