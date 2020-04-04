#ifndef GAME_MODEL_MANAGER_HPP
#define GAME_MODEL_MANAGER_HPP

#include "ModelManager.hpp"
#include "EntityManager.hpp"
#include "Particle.hpp"

class GameModelManager : public ModelManager {
    protected:
        /**  UI  **/
        //Entity *activeEntity; // or Entities, if drag-select is used

        /**  Model  **/
        //EntityManager<Mob> mobs;
        //EntityManager<Projectile> projectiles;
        EntityManager<Particle> particles;

        //std::array<Player> players;
        //Player* activePlayer

        void updateOneTick();

    public:
        GameModelManager();
        ~GameModelManager();

        void spawnParticleExplosion(int numOfParticles, float x, float y, float maxVel, float maxRadius);

        /**  UI  **/
        void pickActiveEntity(float x, float y);
        void click();

        void draw(MainUiManager *uiManager);
};

#endif // GAME_MODEL_MANAGER_HPP
