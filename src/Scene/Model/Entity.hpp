#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <functional>
class MainUiManager;



struct EntityData {
    //

    EntityData();
};
const EntityData genericEntityData;



class Entity {
    protected:
        // Nothing sacred so far...

    public:
        const EntityData *data;
		float life, maxLife; // Can be thought of as health, or a timer, or simply an indicator of destruction
        float x, y, radius;
        float xvel, yvel;
        float mass;

        Entity(); // default constructor
        Entity(const EntityData &data, float x, float y, float xvel, float yvel, float radius, float maxLife, float mass);

        const EntityData* getData() const;
        float getLife() const;
        float getLifeFraction() const;
        virtual bool isDead() const;
        bool isColliding(const Entity& other) const;

        void applyForce(float forceX, float forceY);

        virtual void doTick();
        virtual void draw(
                std::function<void(int&, int&, float, float)> gameToScreenCoords,
                std::function<float(float)> gameToScreenLength,
                MainUiManager *uiManager);
};

#endif // ENTITY_HPP
