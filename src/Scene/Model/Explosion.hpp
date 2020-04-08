#ifndef EXPLOSION_HPP
#define EXPLOSION_HPP

#include "Entity.hpp"



struct ExplosionData : EntityData {
    float radius;
    float maxLife;
    // float damage;

    ExplosionData(const EntityData& entityData, float radius, float maxLife);
};
const ExplosionData genericExplosionData(genericEntityData, 4, 15);



// Explosion does damage to all enemies within it on its initial tick. Everything after that is just for visuals.
class Explosion : public Entity {
    protected:
        // (nothing)

    public:
        Explosion(); // default constructor
        Explosion(const ExplosionData &data, float x, float y);

        bool isOnInitialTick() const;

        virtual void doTick();
        virtual void draw(
                std::function<void(int&, int&, float, float)> gameToScreenCoords,
                std::function<float(float)> gameToScreenLength,
                MainUiManager *uiManager);
};

#endif // EXPLOSION_HPP
