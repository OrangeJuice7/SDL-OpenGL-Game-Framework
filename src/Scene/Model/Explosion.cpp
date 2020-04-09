#include "Explosion.hpp"

#include "../../basicmath.hpp"
#include "../../MainUiManager/MainUiManager.hpp"

ExplosionData::ExplosionData(float radius, float maxLife, float damage) {
    this->radius = radius;
    this->maxLife = maxLife;
    this->damage = damage;
}



Explosion::Explosion() : Explosion(genericExplosionData, 0, 0) {}
Explosion::Explosion(const ExplosionData &data, float x, float y)
        : ImmovableEntity(x, y, data.maxLife) {

    this->data = &data;

    // Add a one-tick buffer, since all entities are updated by 1 tick before they are allowed to interact with other entities
    ++life;
}

float Explosion::getRadius() const { return data->radius; }
float Explosion::getMaxLife() const { return data->maxLife; }

bool Explosion::isOnInitialTick() const {
    return life > getMaxLife() - .01f; // life starts at maxLife and ticks down by 1 per frame
}

void Explosion::doTick() {
    --life;
}

void Explosion::draw(
        std::function<void(int&, int&, float, float)> gameToScreenCoords,
        std::function<float(float)> gameToScreenLength,
        MainUiManager *uiManager) {

    float r = gameToScreenLength(getRadius());
    int sx, sy;
    gameToScreenCoords(sx, sy, x, y);

    float a = getLifeFraction()*0x100;
    if (a < 0) a = 0;
    else if (a > 0xff) a = 0xff;

    uiManager->setDrawColor(0xff, (Uint8)(a), 0x00);
    uiManager->drawLineCircle(sx, sy, r);
}

