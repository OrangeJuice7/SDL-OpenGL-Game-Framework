#ifndef MOB_HPP
#define MOB_HPP

#include "Entity.hpp"



struct MobData : EntityData {
    float radius;
    float maxLife;
    float mass;

    MobData(const EntityData& entityData, float radius, float maxLife, float mass);
};
const MobData genericMobData(genericEntityData, 1, 1, 1);



class Mob : public Entity {
    protected:
        // (nothing)

    public:
        Mob(); // default constructor
        Mob(const MobData &data, float x, float y);

        virtual void doTick();
        virtual void draw(
                std::function<void(int&, int&, float, float)> gameToScreenCoords,
                std::function<float(float)> gameToScreenLength,
                MainUiManager *uiManager);
};

#endif // MOB_HPP

