#include "Explosion.hpp"

#include "../../util/math.hpp"
#include "../../ui/UiManager.hpp"

ExplosionData::ExplosionData(float radius, float maxLife, float maxDamage, SpriteId spriteId) {
    this->radius = radius;
    this->maxLife = maxLife;
    this->maxDamage = maxDamage;

    this->spriteId = spriteId;
}



Explosion::Explosion() : Explosion(genericExplosionData, 0, 0) {}
Explosion::Explosion(const ExplosionData &data, float x, float y)
        : ImmovableEntity(x, y, data.maxLife)
        , data(&data) {

    // Add a one-tick buffer, since all entities are updated by 1 tick before they are allowed to interact with other entities
    ++life;
}

float Explosion::getRadius() const { return data->radius; }
float Explosion::getMaxLife() const { return data->maxLife; }
float Explosion::getMaxDamage() const { return data->maxDamage; }

bool Explosion::isOnInitialTick() const {
    return life > getMaxLife() - .01f; // life starts at maxLife and ticks down by 1 per frame
}

void Explosion::pushEntity(Entity &e) {
    float distx = e.x - x,
          disty = e.y - y;
    float dist2 = getdist2(distx, disty);

    // Force is inversely proportionate to squared distance
    float forceMod = .1f / dist2;
    e.applyForce( distx*forceMod, disty*forceMod);
}

void Explosion::damageEntity(ImmovableEntity &e) {
    float distx = e.x - x,
          disty = e.y - y;
    float dist = getdist(distx, disty) - e.getRadius();
    if (dist < 0) dist = 0;

    // Do damage (decays with distance from epicenter, to 1/2 damage at edge)
    // Note that the full damage will never quite be dealt, because the epicenter will be the projectile's radius away from the edge of e.
    e.takeDamage(getMaxDamage() / (dist / getRadius() + 1));
}

void Explosion::doTick() {
    --life;
}

void Explosion::draw(UiManager &uiManager) {
    float a = getLifeFraction();
    uiManager.setColorMask({1, 1, 1});
    uiManager.setObjectScale(getRadius());
    uiManager.setAtlasPhase(false, 1-a, 0);
    uiManager.drawSprite(x, y, data->spriteId);
}

