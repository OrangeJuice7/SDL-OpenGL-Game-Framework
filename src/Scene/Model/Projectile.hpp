#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include "Entity.hpp"
#include "Explosion.hpp"
#include "../../ui/SpriteId.hpp"

struct ProjectileData {
    float radius;
    float maxLife;
    float mass;
    float damage; // Damage on contact; this is in addition to explosion damage
    const ExplosionData* explosionData; // Set to nullptr for no explosion

    SpriteId spriteId;

    ProjectileData(float radius, float maxLife, float mass, float damage, const ExplosionData* explosionData, SpriteId spriteId);
};
const ProjectileData   genericProjectileData(.1f, 30, .1f, .08f, nullptr, SPRITE_ID_CIRCLE);
const ProjectileData     lightProjectileData(.1f, 30, .1f, .04f, nullptr, SPRITE_ID_CIRCLE);
const ProjectileData explosiveProjectileData(.2f, 36, .4f, 0, &genericExplosionData, SPRITE_ID_CIRCLE);



class Projectile : public Entity {
    public:
        const ProjectileData * const data;

        Projectile(); // default constructor
        Projectile(const ProjectileData &data, float x, float y, float xvel, float yvel);

        float getRadius() const;
        float getMaxLife() const;
        float getMass() const;
        float getDamage() const;
        const ExplosionData* getExplosionData() const;

        void pushEntity(Entity &e);
        void damageEntity(ImmovableEntity &e);

        virtual void doTick(GameModelManager& model);
        virtual void draw(UiManager &uiManager) const;
};

#endif // PROJECTILE_HPP

