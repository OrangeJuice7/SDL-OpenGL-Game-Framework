#include "Mob.hpp"

#include "../../basicmath.hpp"
#include "../../MainUiManager/MainUiManager.hpp"

MobData::MobData(const EntityData& entityData, float radius, float maxLife, float mass)
        : EntityData(entityData) {

    this->radius = radius;
    this->maxLife = maxLife;
    this->mass = mass;
}



Mob::Mob() : Mob(genericMobData, 0, 0) {}
Mob::Mob(const MobData &data, float x, float y)
        : Entity(data, x, y, 0, 0, data.radius, data.maxLife, data.mass) {}

void Mob::doTick() {
    Entity::doTick();

    float maxVelChange = .1f;
    float vel = getdist(xvel, yvel);
    if (vel <= maxVelChange) xvel = yvel = 0;
    else {
        float mod = (vel - maxVelChange) / vel;
        xvel *= mod;
        yvel *= mod;
    }
}

void Mob::draw(
        std::function<void(int&, int&, float, float)> gameToScreenCoords,
        std::function<float(float)> gameToScreenLength,
        MainUiManager *uiManager) {

    float r = gameToScreenLength(radius);
    int sx, sy;
    gameToScreenCoords(sx, sy, x, y);

    float a = getLifeFraction()*0x100;
    if (a < 0) a = 0;
    else if (a > 0xff) a = 0xff;

    uiManager->setDrawColor(0x80, (Uint8)(a), (Uint8)(a));
    uiManager->drawLineCircle(sx, sy, r);
}
