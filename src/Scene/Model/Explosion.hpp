#ifndef EXPLOSION_HPP
#define EXPLOSION_HPP

#include "Entity.hpp"

struct ExplosionData {
    float radius;
    float maxLife;
    float damage;

    ExplosionData(float radius, float maxLife, float damage);
};
const ExplosionData genericExplosionData(4, 15, .2f);



// Explosion does damage to all enemies within it on its initial tick. Everything after that is just for visuals.
class Explosion : public ImmovableEntity {
    public:
        const ExplosionData *data;

        Explosion(); // default constructor
        Explosion(const ExplosionData &data, float x, float y);

        float getRadius() const;
        float getMaxLife() const;
        bool isOnInitialTick() const;

        virtual void doTick();
        virtual void draw(
                std::function<void(int&, int&, float, float)> gameToScreenCoords,
                std::function<float(float)> gameToScreenLength,
                MainUiManager *uiManager);
};

#endif // EXPLOSION_HPP

