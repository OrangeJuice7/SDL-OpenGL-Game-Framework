#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include "Entity.hpp"
class ExplosionData;

struct ProjectileData {
    float radius;
    float maxLife;
    float mass;
    float damage; // Damage on contact; this is in addition to explosion damage
    ExplosionData* explosion; // Set to nullptr for no explosion

    ProjectileData(float radius, float maxLife, float mass, float damage, ExplosionData* explosion);
};
const ProjectileData genericProjectileData(.1f, 30, .1f, .2f, nullptr);



class Projectile : public Entity {
    public:
        const ProjectileData *data;

        Projectile(); // default constructor
        Projectile(const ProjectileData &data, float x, float y, float xvel, float yvel);

        float getRadius() const;
        float getMaxLife() const;
        float getMass() const;

        virtual void doTick();
        virtual void draw(
                std::function<void(int&, int&, float, float)> gameToScreenCoords,
                std::function<float(float)> gameToScreenLength,
                MainUiManager *uiManager);
};

#endif // PROJECTILE_HPP

