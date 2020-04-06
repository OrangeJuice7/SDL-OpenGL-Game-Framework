#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include "Entity.hpp"



struct ProjectileData : EntityData {
    float radius;
    float maxLife;
    float mass;
    // float damage; [OR] ExplosionData explosion;
    // bool explodeOnDeath;

    ProjectileData(const EntityData& entityData, float radius, float maxLife, float mass);
};
const ProjectileData genericProjectileData(genericEntityData, .1f, 30, .1f);



class Projectile : public Entity {
    protected:
        // (nothing)

    public:
        Projectile(); // default constructor
        Projectile(const ProjectileData &data, float x, float y, float xvel, float yvel);

        virtual void doTick();
        virtual void draw(
                std::function<void(int&, int&, float, float)> gameToScreenCoords,
                std::function<float(float)> gameToScreenLength,
                MainUiManager *uiManager);
};

#endif // PROJECTILE_HPP

