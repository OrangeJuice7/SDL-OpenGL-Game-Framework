#ifndef MODEL_MANAGER_HPP
#define MODEL_MANAGER_HPP

#include <cstdint>
//#include <array>
//#include "Entity.hpp"
class MainUiManager;

class ModelManager {
    protected:
        uint32_t modelTick;

        // Actual update function
        virtual void updateOneTick();

    public:
        ModelManager();
        virtual ~ModelManager();

        uint32_t getModelTick();

        // Wraps updateOneTick() in some admin
        void doTick();

        /**  UI  **/
        virtual void pickActiveEntity(int x, int y);
        virtual void click();

        virtual void draw(MainUiManager *uiManager);
};

#endif // MODEL_MANAGER_HPP
