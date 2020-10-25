#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <functional>
class GameModelManager;
class UiManager;

class ImmovableEntity {
    public:
        // Expose internal state to let other places modify at will
        float x, y;
		float life; // Can be thought of as health, or a timer, or simply an indicator for deletion
        // Circular vs Rectangular hitbox maybe

        ImmovableEntity(); // default constructor
        ImmovableEntity(float x, float y, float life);
        virtual ~ImmovableEntity();

        virtual float getRadius() const =0; // Should be >= 0
        virtual float getMaxLife() const =0; // Should be > 0
        float getLifeFraction() const;
        virtual bool isDead() const;
        bool isColliding(const ImmovableEntity& other) const;

        virtual void takeDamage(float dmg);
        void kill();
        virtual void doTick(GameModelManager& model); // May interact with (i.e. change) the model as well

        bool isWithinScreen(UiManager &uiManager) const;
        virtual void draw(UiManager &uiManager) const;
};

class Entity : public ImmovableEntity {
    public:
        float xvel, yvel;

        Entity(); // default constructor
        Entity(float x, float y, float xvel, float yvel, float life);
        virtual ~Entity();

        float getObservedVelX() const; // The actual visible frame-to-frame movement of the Entity. Unlike the normal vel, this is not subject to change (e.g. by forces) mid-frame
        float getObservedVelY() const;
        virtual float getMass() const =0; // Should be > 0

        void applyForce(float forceX, float forceY);
        void backtrackToPointOfContact(const ImmovableEntity &e); // Assumes they are already overlapping, otherwise this might "forward-track"
        virtual void doTick(GameModelManager& model);

    protected:
        float observedVelX, observedVelY;
};

#endif // ENTITY_HPP
