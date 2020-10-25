#ifndef EXPLOSION_HPP
#define EXPLOSION_HPP

#include "Entity.hpp"
#include "../../ui/SpriteId.hpp"

struct ExplosionData {
    float radius;
    float maxLife;
    float maxDamage;

    SpriteId spriteId;

    ExplosionData(float radius, float maxLife, float maxDamage, SpriteId spriteId);
};
const ExplosionData genericExplosionData(4, 15, .05f, SPRITE_ID_EXPLOSION);



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

        virtual void doTick(GameModelManager& model);
        virtual void draw(UiManager &uiManager) const;
};

#endif // EXPLOSION_HPP

