#ifndef EXPLOSION_HPP
#define EXPLOSION_HPP

#include "Entity.hpp"

struct ExplosionData {
    float radius;
    float maxLife;
    float maxDamage;

    ExplosionData(float radius, float maxLife, float maxDamage);
};
const ExplosionData genericExplosionData(4, 15, .05f);



// Explosion does damage to all enemies within it on its initial tick. Everything after that is just for visuals.
class Explosion : public ImmovableEntity {
    public:
        const ExplosionData * const data;

        Explosion(); // default constructor
        Explosion(const ExplosionData &data, float x, float y);

        float getRadius() const;
        float getMaxLife() const;
        float getMaxDamage() const;
        bool isOnInitialTick() const;

        void pushEntity(Entity &e);
        void damageEntity(ImmovableEntity &e);

        virtual void doTick();
        virtual void draw(UiManager &uiManager);
};

#endif // EXPLOSION_HPP

