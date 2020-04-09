#ifndef MOB_HPP
#define MOB_HPP

#include "Entity.hpp"

struct MobData {
    float radius;
    float maxLife;
    float mass;

    MobData(float radius, float maxLife, float mass);
};
const MobData genericMobData(1, 1, 1);
const MobData heavyMobData(2, 2, 8);



class Mob : public Entity {
    public:
        const MobData *data;

        Mob(); // default constructor
        Mob(const MobData &data, float x, float y);

        float getRadius() const;
        float getMaxLife() const;
        float getMass() const;

        virtual void doTick();
        virtual void draw(
                std::function<void(int&, int&, float, float)> gameToScreenCoords,
                std::function<float(float)> gameToScreenLength,
                MainUiManager *uiManager);
};

#endif // MOB_HPP

