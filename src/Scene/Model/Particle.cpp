#include "Particle.hpp"

#include "../../basicmath.hpp"
#include "../../MainUiManager/MainUiManager.hpp"

ParticleData::ParticleData(const EntityData& entityData)
        : EntityData(entityData) {

    //this->radius = radius;
}



Particle::Particle() : Particle(emptyParticleData, 0, 0, 0, 0, 1, 1, 1) {}
Particle::Particle(const ParticleData &data, float x, float y, float xvel, float yvel, float radius, float maxLife, float mass)
        : Entity(data, x, y, xvel, yvel, radius, maxLife, mass) {}

void Particle::doTick() {
    Entity::doTick();
    --life;

    // Drag force is proportional to the square of the velocity
    // (Other factors for the proportion are cross section, shape and fluid density and viscosity)
    // But screw that, too much to balance
    //xvel *= .9f;
    //yvel *= .9f;

    // Add wind
    applyForce(
        (-0.2f - xvel)*.0001f,
        ( 0.0f - yvel)*.0001f);

    // decay
    radius *= .95f;
    //mass *= .86f;
    mass *= .95f;
}

void Particle::draw(
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

