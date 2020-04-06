#ifndef ENTITY_MANAGER_HPP
#define ENTITY_MANAGER_HPP

#include <forward_list>
#include <functional>
#include "../../basicmath.hpp"
class MainUiManager;

template <class TEntity>
class EntityManager {
    // Let all the different EntityManager<> classes talk to each other
    // Needed for checkCollisions() to work
    template<class UEntity>
    friend class EntityManager;

    protected:
        std::forward_list<TEntity> entities; // Convert to TEntity* to handle the TEntity's derivatives as well

    public:
        EntityManager();
        ~EntityManager();

        TEntity* addEntity(const TEntity& entity);
        void clearEntities();

        void doTick();
        void doTick(std::function<void(const TEntity*)> entityDeletedFunc); // Lets the parent dereference any entity it might be pointing to that has been deleted

        void checkCollisionsSelf(
                std::function<void(TEntity&, TEntity&)> collisionFunc );

        template <class UEntity>
        void checkCollisions(
                EntityManager<UEntity>& otherManager,
                std::function<void(TEntity&, UEntity&)> collisionFunc );

        TEntity* pickEntity(float x, float y);

        void draw(
                std::function<void(int&, int&, float, float)> gameToScreenCoords,
                std::function<float(float)> gameToScreenLength,
                MainUiManager *uiManager);
};



template <class TEntity>
EntityManager<TEntity>::EntityManager() {}

template <class TEntity>
EntityManager<TEntity>::~EntityManager() {}

template <class TEntity>
TEntity* EntityManager<TEntity>::addEntity(const TEntity& entity) {
    entities.push_front(entity);
    return &(entities.front());
}

template <class TEntity>
void EntityManager<TEntity>::clearEntities() {
    entities.clear();
}

template <class TEntity>
void EntityManager<TEntity>::doTick() {
    // Remove dead entities
    entities.remove_if( [](const TEntity& entity) -> bool { return entity.isDead(); } );

    // Update the rest
    for (TEntity &entity : entities) {
        entity.doTick();
    }
}
template <class TEntity>
void EntityManager<TEntity>::doTick(std::function<void(const TEntity*)> entityDeletedFunc) {
    // Remove dead entities
    entities.remove_if( [entityDeletedFunc](const TEntity& entity) -> bool {
        if (entity.isDead()) {
            entityDeletedFunc(&entity);
            return true;
        } else return false;
    } );

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
              er = entity.radius;

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
void EntityManager<TEntity>::draw(
        std::function<void(int&, int&, float, float)> gameToScreenCoords,
        std::function<float(float)> gameToScreenLength,
        MainUiManager *uiManager) {

    // Implement draw-culling some time
    for (TEntity &entity : entities) {
        if (entity.isWithinScreen(gameToScreenCoords, uiManager))
            entity.draw(gameToScreenCoords, gameToScreenLength, uiManager);
    }
}

#endif // ENTITY_MANAGER_HPP
