#ifndef ENTITY_MANAGER_HPP
#define ENTITY_MANAGER_HPP

#include <forward_list>
#include <functional>
class MainUiManager;

template <class TEntity>
class EntityManager {
    protected:
        std::forward_list<TEntity> entities; // Convert to TEntity* to handle the TEntity's derivatives as well

    public:
        EntityManager();
        ~EntityManager();

        void addEntity(const TEntity& entity);
        void clearEntities();

        void doTick();

        void checkCollisionsSelf(
                std::function<void(const TEntity&, const TEntity&)> collisionFunc );

        template <class UEntity>
        void checkCollisions(
                const EntityManager<UEntity>& otherManager,
                std::function<void(const TEntity&, const UEntity&)> collisionFunc );

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
void EntityManager<TEntity>::addEntity(const TEntity& entity) {
    entities.push_front(entity);
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
void EntityManager<TEntity>::checkCollisionsSelf(
        std::function<void(const TEntity&, const TEntity&)> collisionFunc ) {

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
        const EntityManager<UEntity>& otherManager,
        std::function<void(const TEntity&, const UEntity&)> collisionFunc ) {

    for (TEntity &entity : entities) {
        //if (entity.isDead()) continue;
        for (UEntity &otherEntity : otherManager.entities) {
            //if (otherEntity.isDead()) continue;
            collisionFunc(entity, otherEntity);
        }
    }
}

template <class TEntity>
void EntityManager<TEntity>::draw(
        std::function<void(int&, int&, float, float)> gameToScreenCoords,
        std::function<float(float)> gameToScreenLength,
        MainUiManager *uiManager) {

    // Implement draw-culling some time
    for (TEntity &entity : entities) {
        entity.draw(gameToScreenCoords, gameToScreenLength, uiManager);
    }
}

#endif // ENTITY_MANAGER_HPP

