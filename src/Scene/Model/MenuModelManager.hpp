#ifndef GAME_MODEL_MANAGER_HPP
#define GAME_MODEL_MANAGER_HPP

#include "ModelManager.hpp"

class MenuModelManager : public ModelManager {
    protected:
        void updateOneTick();

    public:
        MenuModelManager();

        /**  UI  **/
        void draw(MainUiManager *uiManager);
};

#endif // GAME_MODEL_MANAGER_HPP
