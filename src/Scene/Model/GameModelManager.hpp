#ifndef GAME_MODEL_MANAGER_HPP
#define GAME_MODEL_MANAGER_HPP

#include "ModelManager.hpp"

class GameModelManager : public ModelManager {
    protected:
        /**  UI  **/
        //int cameraX, cameraY;
        //Entity *activeEntity; // or Entities, if drag-select is used

        /**  Model  **/
        //std::array<Mob*> mobs;
        //std::array<Projectile*> projectiles;
        //std::array<Particle*> particles;

        //std::array<Player> players;
        //Player* activePlayer

        void updateOneTick();

    public:
        GameModelManager();

        /**  UI  **/
        void pickActiveEntity(int x, int y);
        void click();

        void draw(MainUiManager *uiManager);
};

#endif // GAME_MODEL_MANAGER_HPP
