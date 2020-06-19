#ifndef MENU_MODEL_MANAGER_HPP
#define MENU_MODEL_MANAGER_HPP

#include "ModelManager.hpp"

class MenuModelManager : public ModelManager {
    protected:
        void updateOneTick();

    public:
        MenuModelManager();

        /**  UI  **/
        void draw(UiManager &uiManager) const;
};

#endif // MENU_MODEL_MANAGER_HPP
