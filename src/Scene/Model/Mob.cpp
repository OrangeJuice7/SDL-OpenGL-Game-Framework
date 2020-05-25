#include "Mob.hpp"

#include "../../basicmath.hpp"
#include "../../ui/UiManager.hpp"

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
    uiManager.setColorMask({.5f, a, a});
    uiManager.setObjectScale(getRadius());
    uiManager.drawSprite(x, y, SPRITE_ID_CIRCLE);
}
