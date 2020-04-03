#ifndef MENU_MODEL_MANAGER_HPP
#define MENU_MODEL_MANAGER_HPP

#include "ModelManager.hpp"

class MenuModelManager : public ModelManager {
    protected:
        void updateOneTick();

    public:
        MenuModelManager();

        /**  UI  **/
        void draw(MainUiManager *uiManager);
};

#endif // MENU_MODEL_MANAGER_HPP
