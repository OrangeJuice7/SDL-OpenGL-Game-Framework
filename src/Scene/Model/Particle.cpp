#include "Particle.hpp"

#include "../../util/math.hpp"
#include "../../ui/UiManager.hpp"

Particle::Particle() : Particle(0, 0, 0, 0, 1, 1, 1) {}
Particle::Particle(float x, float y, float xvel, float yvel, float radius, float maxLife, float mass)
        : Entity(x, y, xvel, yvel, maxLife) {

    this->radius = radius;
    this->maxLife = maxLife;
    this->mass = mass;
}

float Particle::getRadius() const { return radius; }
float Particle::getMaxLife() const { return maxLife; }
float Particle::getMass() const { return mass; }

void Particle::doTick(GameModelManager& model) {
    Entity::doTick(model);
    --life;

    // decay
    radius *= .95f;
    mass *= .95f; //.86f;
}

void Particle::draw(UiManager &uiManager) const {
    float a = getLifeFraction();
    uiManager.setColorMask({1, a, 0});
    uiManager.setObjectScale(getRadius());
    uiManager.drawSprite(x, y, SPRITE_ID_PARTICLE);
}

