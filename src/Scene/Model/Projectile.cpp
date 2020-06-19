#include "Projectile.hpp"

#include "../../util/math.hpp"
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
}

void Projectile::draw(UiManager &uiManager) const {
    float a = getLifeFraction();
    uiManager.setColorMask({1, a, 0});
    uiManager.setObjectScale(getRadius());
    uiManager.drawSprite(x, y, data->spriteId);
}

