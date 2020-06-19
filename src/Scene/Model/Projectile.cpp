#include "Projectile.hpp"

#include "../../util/math.hpp"
#include "GameModelManager.hpp"
#include "../../ui/UiManager.hpp"

ProjectileData::ProjectileData(float radius, float maxLife, float mass, float damage, const ExplosionData* explosionData, SpriteId spriteId) {
    this->radius = radius;
    this->maxLife = maxLife;
    this->mass = mass;
    this->damage = damage;
    this->explosionData = explosionData;

    this->spriteId = spriteId;
}



Projectile::Projectile() : Projectile(genericProjectileData, 0, 0, 0, 0) {}
Projectile::Projectile(const ProjectileData &data, float x, float y, float xvel, float yvel)
        : Entity(x, y, xvel, yvel, data.maxLife)
        , data(&data) {}

float Projectile::getRadius() const { return data->radius; }
float Projectile::getMaxLife() const { return data->maxLife; }
float Projectile::getMass() const { return data->mass; }
float Projectile::getDamage() const { return data->damage; }
const ExplosionData* Projectile::getExplosionData() const { return data->explosionData; }

void Projectile::pushEntity(Entity &e) {
    // Add all of this projectile's momentum to e
    e.applyForce(xvel*getMass(), yvel*getMass());
}

void Projectile::damageEntity(ImmovableEntity &e) {
    e.takeDamage(getDamage());
}

void Projectile::doTick(GameModelManager& model) {
    Entity::doTick(model);
    --life;

    // Drag force is proportional to the square of the velocity
    // (Other factors for the proportion are cross section, shape and fluid density and viscosity)
    // But screw that, too much to balance
    //xvel *= .9f;
    //yvel *= .9f;

    // Add wind
    applyForce(
        (model.getWindVelX() - xvel)*.0001f,
        (model.getWindVelY() - yvel)*.0001f);
}

void Projectile::draw(UiManager &uiManager) const {
    float a = getLifeFraction();
    uiManager.setColorMask({1, a, 0});
    uiManager.setObjectScale(getRadius());
    uiManager.drawSprite(x, y, data->spriteId);
}

