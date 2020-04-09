#include "Mob.hpp"

#include "../../basicmath.hpp"
#include "../../MainUiManager/MainUiManager.hpp"

MobData::MobData(float radius, float maxLife, float mass) {
    this->radius = radius;
    this->maxLife = maxLife;
    this->mass = mass;
}



Mob::Mob() : Mob(genericMobData, 0, 0) {}
Mob::Mob(const MobData &data, float x, float y)
        : Entity(x, y, 0, 0, data.maxLife) {

    this->data = &data;
}

float Mob::getRadius() const { return data->radius; }
float Mob::getMaxLife() const { return data->maxLife; }
float Mob::getMass() const { return data->mass; }

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

    float r = gameToScreenLength(getRadius());
    int sx, sy;
    gameToScreenCoords(sx, sy, x, y);

    float a = getLifeFraction()*0x100;
    if (a < 0) a = 0;
    else if (a > 0xff) a = 0xff;

    uiManager->setDrawColor(0x80, (Uint8)(a), (Uint8)(a));
    uiManager->drawLineCircle(sx, sy, r);
}
