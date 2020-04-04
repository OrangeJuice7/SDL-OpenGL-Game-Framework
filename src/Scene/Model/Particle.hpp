#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include "Entity.hpp"



struct ParticleData : EntityData {
    //float radius;

    ParticleData(const EntityData& entityData);
};
const ParticleData emptyParticleData(emptyEntityData);

//const ParticleData genericParticleData(EntityData(.2f, 30, 1));



class Particle : public Entity {
    protected:
        // (nothing)

    public:
        Particle(); // default constructor
        Particle(const ParticleData &data, float x, float y, float xvel, float yvel, float radius, float maxLife, float mass);

        virtual void doTick();
        virtual void draw(
                std::function<void(int&, int&, float, float)> gameToScreenCoords,
                std::function<float(float)> gameToScreenLength,
                MainUiManager *uiManager);
};

#endif // PARTICLE_HPP

