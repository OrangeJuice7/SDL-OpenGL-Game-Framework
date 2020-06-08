#include "Mob.hpp"

#include "../../util/math.hpp"
#include "../../ui/UiManager.hpp"

MobData::MobData(float radius, float maxLife, float mass) {
    this->radius = radius;
    this->maxLife = maxLife;
    this->mass = mass;
}



Mob::Mob() : Mob(genericMobData, 0, 0) {}
Mob::Mob(const MobData &data, float x, float y)
        : Entity(x, y, 0, 0, data.maxLife)
        , data(&data) {}
Mob::~Mob() {}

float Mob::getRadius() const { return data->radius; }
float Mob::getMaxLife() const { return data->maxLife; }
float Mob::getMass() const { return data->mass; }

WeaponManagerWeaponId Mob::addWeapon(const WeaponData &weaponData) {
    return weapons.addWeapon(weaponData);
}
bool Mob::removeWeapon(WeaponManagerWeaponId id) {
    return weapons.removeWeapon(id);
}

Projectile* Mob::fireAtPositionIfReady(WeaponManagerWeaponId weaponId, GameModelManager &model, float targetX, float targetY) {
    Weapon *weapon = weapons.getWeapon(weaponId);
    if (!weapon) return nullptr; // No weapon, abort

    // Get direction vector of target from this Entity
    float dirX = targetX - x,
          dirY = targetY - y;

    // Normalize direction vector
    float dist = getdist(dirX, dirY);
    dirX /= dist;
    dirY /= dist;

    float projectileOffset = getRadius() + weapon->data->projectileData->radius;
    float vel = weapon->data->projectileSpeed;

    return weapon->fireIfReady(model,
        x + dirX * projectileOffset,
        y + dirY * projectileOffset,
        dirX * vel,
        dirY * vel);
}
Projectile* Mob::fireAtEntityIfReady(WeaponManagerWeaponId weaponId, GameModelManager &model, const ImmovableEntity& target) {
    return fireAtPositionIfReady(weaponId, model, target.x, target.y);
}
Projectile* Mob::leadAndFireAtEntityIfReady(WeaponManagerWeaponId weaponId, GameModelManager &model, const Entity& target) {
    float targetX = target.x,
          targetY = target.y;

    // p = projectile
    // e = target's current position
    // t = time till collision
    // .r = radius
    // Have to solve for the new target position e' when t = (dist(this, e') - this->r, p.r, e.r) / p.speed, and e' = e + t*e.vel

    return fireAtPositionIfReady(weaponId, model, targetX, targetY);
}

void Mob::doTick() {
    Entity::doTick();

    weapons.doTick();

    // Add drag
    float maxVelChange = .1f;
    float vel = getdist(xvel, yvel);
    if (vel <= maxVelChange) xvel = yvel = 0;
    else {
        float mod = (vel - maxVelChange) / vel;
        xvel *= mod;
        yvel *= mod;
    }
}

void Mob::draw(UiManager &uiManager) {
    float a = getLifeFraction();
    uiManager.setColorMask({1, a, a});
    uiManager.setObjectScale(getRadius());
    uiManager.setAtlasPhase(true, uiManager.getUiTick() * .02f, 0);
    uiManager.drawSprite(x, y, SPRITE_ID_ELF);
}
