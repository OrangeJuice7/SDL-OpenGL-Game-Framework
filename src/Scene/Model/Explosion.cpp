#include "Explosion.hpp"

#include "../../basicmath.hpp"
#include "../../MainUiManager/MainUiManager.hpp"

ExplosionData::ExplosionData(const EntityData& entityData, float radius, float maxLife)
        : EntityData(entityData) {

    this->radius = radius;
    this->maxLife = maxLife;
}



Explosion::Explosion() : Explosion(genericExplosionData, 0, 0) {}
Explosion::Explosion(const ExplosionData &data, float x, float y)
        : Entity(data, x, y, 0, 0, data.radius, data.maxLife, 1) {

    ++life; // Add a one-tick buffer, since all entities are updated by 1 tick before they are allowed to interact with other entities
}

bool Explosion::isOnInitialTick() const {
    return life > maxLife-.01f; // life starts at maxLife and ticks down by 1 per frame
}

void Explosion::doTick() {
    Entity::doTick();
    --life;
}

void Explosion::draw(
        std::function<void(int&, int&, float, float)> gameToScreenCoords,
        std::function<float(float)> gameToScreenLength,
        MainUiManager *uiManager) {

    float r = gameToScreenLength(radius);
    int sx, sy;
    gameToScreenCoords(sx, sy, x, y);

    float a = getLifeFraction()*0x100;
    if (a < 0) a = 0;
    else if (a > 0xff) a = 0xff;

    uiManager->setDrawColor(0xff, (Uint8)(a), 0x00);
    uiManager->drawLineCircle(sx, sy, r);
}

