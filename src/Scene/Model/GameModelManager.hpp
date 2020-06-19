#ifndef GAME_MODEL_MANAGER_HPP
#define GAME_MODEL_MANAGER_HPP

#include "ModelManager.hpp"
#include "Map.hpp"
#include "EntityManager.hpp"
#include "Mob.hpp"
#include "Projectile.hpp"
#include "Explosion.hpp"
#include "Particle.hpp"

class GameModelManager : public ModelManager {
    protected:
        /**  UI  **/
        Mob *activeMob; // (TODO) or Mobs, if drag-select is used

        /**  Model  **/
        Map map;
        EntityManager<Mob> mobs;
        EntityManager<Projectile> projectiles;
        EntityManager<Explosion> explosions;
        EntityManager<Particle> particles;

        // TODO: add players
        //std::array<Player> players;
        //Player* activePlayer
        Mob *playerMob; // The mob that the player controls

        void updateOneTick();

    public:
        GameModelManager();
        ~GameModelManager();

        // Map access
        float getWindVelX() const;
        float getWindVelY() const;

        // Misc. access
        Mob* getActiveMob() const;
        Mob* getPlayerMob() const;

        // Spawning
        Mob* spawnMob(const MobData &data, float x, float y);
        Mob* spawnPlayerMob(const MobData &data, float x, float y);
        Projectile* spawnProjectile(const ProjectileData &data, float x, float y, float xvel, float yvel);
        Explosion* spawnExplosion(const ExplosionData &data, float x, float y);
        void spawnParticleExplosion(int numOfParticles, float x, float y, float maxVel, float maxRadius);

        /**  UI  **/
        void pickSelectedEntity(float x, float y);
        void click();

        void draw(UiManager &uiManager) const;
};

#endif // GAME_MODEL_MANAGER_HPP
