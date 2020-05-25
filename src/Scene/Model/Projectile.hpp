#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include "Entity.hpp"
#include "Explosion.hpp"

struct ProjectileData {
    float radius;
    float maxLife;
    float mass;
    float damage; // Damage on contact; this is in addition to explosion damage
    const ExplosionData* explosionData; // Set to nullptr for no explosion

    ProjectileData(float radius, float maxLife, float mass, float damage, const ExplosionData* explosionData);
};
const ProjectileData genericProjectileData(.1f, 30, .1f, .2f, nullptr);
const ProjectileData explosiveProjectileData(.1f, 30, .1f, 0, &genericExplosionData);



class Projectile : public Entity {
    public:
        const ProjectileData *data;

        Projectile(); // default constructor
        Projectile(const ProjectileData &data, float x, float y, float xvel, float yvel);

        float getRadius() const;
        float getMaxLife() const;
        float getMass() const;
        float getDamage() const;
        const ExplosionData* getExplosionData() const;

        void pushEntity(Entity &e);
        void damageEntity(ImmovableEntity &e);

        virtual void doTick();
        virtual void draw(UiManager &uiManager);
};

#endif // PROJECTILE_HPP

