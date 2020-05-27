#ifndef ENTITY_MANAGER_HPP
#define ENTITY_MANAGER_HPP

#include <forward_list>
#include <functional>
#include "../../util/math.hpp"
class UiManager;

template <class TEntity>
class EntityManager {
    // Let all the different EntityManager<> classes talk to each other
    // Needed for checkCollisions() to work
    template<class UEntity>
    friend class EntityManager;

    protected:
        std::forward_list<TEntity> entities; // Convert to TEntity* to handle the TEntity's derivatives as well? Would also make external entity references safer, somewhat
        std::forward_list<TEntity> toAdd; // Buffer list, to prevent element additions in the middle of iterating thru entities (which will screw up the iterator)

    public:
        EntityManager();
        ~EntityManager();

        TEntity* addEntity(const TEntity& entity);
        void clearEntities();

        void doTick();
        void doTick(std::function<void(const TEntity&)> entityDeletedFunc); // Lets the parent dereference any entity it might be pointing to that has been deleted

        void checkCollisionsSelf(
                std::function<void(TEntity&, TEntity&)> collisionFunc );

        template <class UEntity>
        void checkCollisions(
                EntityManager<UEntity>& otherManager,
                std::function<void(TEntity&, UEntity&)> collisionFunc );

        TEntity* pickEntity(float x, float y);

        void draw(UiManager &uiManager);
};



template <class TEntity>
EntityManager<TEntity>::EntityManager() {}

template <class TEntity>
EntityManager<TEntity>::~EntityManager() {}

template <class TEntity>
TEntity* EntityManager<TEntity>::addEntity(const TEntity& entity) {
    toAdd.push_front(entity);
    return &(toAdd.front());
}

template <class TEntity>
void EntityManager<TEntity>::clearEntities() {
    entities.clear();
    toAdd.clear();
}

template <class TEntity>
void EntityManager<TEntity>::doTick() {
    // Remove dead entities
    entities.remove_if( [](const TEntity& entity) -> bool { return entity.isDead(); } );

    // Add buffered entities
    entities.splice_after(entities.before_begin(), toAdd);

    // Update the rest
    for (TEntity &entity : entities) {
        entity.doTick();
    }
}
template <class TEntity>
void EntityManager<TEntity>::doTick(std::function<void(const TEntity&)> entityDeletedFunc) {
    // Remove dead entities
    entities.remove_if( [this, entityDeletedFunc](const TEntity& entity) -> bool {
        if (entity.isDead()) {
            entityDeletedFunc(entity);
            return true;
        } else return false;
    } );

    // Add buffered entities
    entities.splice_after(entities.before_begin(), toAdd);

    // Update the rest
    for (TEntity &entity : entities) {
        entity.doTick();
    }
}

template <class TEntity>
void EntityManager<TEntity>::checkCollisionsSelf(
        std::function<void(TEntity&, TEntity&)> collisionFunc ) {

    for (auto entity = entities.begin(); entity != entities.end(); ++entity) {
        //if (entity.isDead()) continue;

        auto otherEntity = entity; ++otherEntity;
        for (; otherEntity != entities.end(); ++otherEntity) {
            //if (otherEntity.isDead()) continue;
            collisionFunc(*entity, *otherEntity);
        }
    }
}

template <class TEntity>
template <class UEntity>
void EntityManager<TEntity>::checkCollisions(
        EntityManager<UEntity>& otherManager,
        std::function<void(TEntity&, UEntity&)> collisionFunc ) {

    for (TEntity &entity : entities) {
        //if (entity.isDead()) continue;
        for (UEntity &otherEntity : otherManager.entities) {
            //if (otherEntity.isDead()) continue;
            collisionFunc(entity, otherEntity);
        }
    }
}

template <class TEntity>
TEntity* EntityManager<TEntity>::pickEntity(float x, float y) {
    for (TEntity &entity : entities) {
        float ex = entity.x,
              ey = entity.y,
              er = entity.getRadius();

        // Bounding box check
        if (x < ex-er || x > ex+er ||
            y < ey-er || y > ey+er ) continue;

        // Circle check
        if (getdist2(ex-x,ey-y) > er*er) continue;

        return &entity;
    }
    return nullptr;
}

template <class TEntity>
void EntityManager<TEntity>::draw(UiManager &uiManager) {
    for (TEntity &entity : entities) {
        if (entity.isWithinScreen(uiManager))
            entity.draw(uiManager);
    }
}

#endif // ENTITY_MANAGER_HPP
