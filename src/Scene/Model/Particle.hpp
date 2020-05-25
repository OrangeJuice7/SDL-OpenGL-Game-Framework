#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include "Entity.hpp"

// Define specific Particle types in subclasses, or ID/Data system?
// Derivatives would define appearance, behaviour and variety
class Particle : public Entity {
    public:
        float radius;
        float maxLife;
        float mass;

        Particle(); // default constructor
        Particle(float x, float y, float xvel, float yvel, float radius, float maxLife, float mass);

        float getRadius() const;
        float getMaxLife() const;
        float getMass() const;

        virtual void doTick();
        virtual void draw(UiManager &uiManager);
};

#endif // PARTICLE_HPP

