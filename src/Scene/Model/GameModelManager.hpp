#ifndef GAME_MODEL_MANAGER_HPP
#define GAME_MODEL_MANAGER_HPP

#include "ModelManager.hpp"
#include "EntityManager.hpp"
#include "Particle.hpp"
#include "Mob.hpp"

class GameModelManager : public ModelManager {
    protected:
        /**  UI  **/
        Mob *activeMob; // or Mobs, if drag-select is used

        /**  Model  **/
        EntityManager<Mob> mobs;
        //EntityManager<Projectile> projectiles;
        EntityManager<Particle> particles;

        //std::array<Player> players;
        //Player* activePlayer
        Mob *playerMob; // The mob that the player controls

        void updateOneTick();

    public:
        GameModelManager();
        ~GameModelManager();

        Mob* getActiveMob() const;
        Mob* getPlayerMob() const;

        void spawnParticleExplosion(int numOfParticles, float x, float y, float maxVel, float maxRadius);
        Mob* spawnMob(const MobData &data, float x, float y);
        Mob* spawnPlayerMob(const MobData &data, float x, float y);

        /**  UI  **/
        void pickActiveEntity(float x, float y);
        void click();

        void draw(MainUiManager *uiManager);
};

#endif // GAME_MODEL_MANAGER_HPP
