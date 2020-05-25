#ifndef MODEL_MANAGER_HPP
#define MODEL_MANAGER_HPP

#include <cstdint>
#include <functional>
#include <SDL2/SDL.h>
#include "../../ui/ModelCamera.hpp"
class UiManager;

class ModelManager {
    protected:
        uint32_t modelTick;

        // Actual update function
        virtual void updateOneTick();

    public:
        ModelCamera camera; // Expose camera for free manipulation

        ModelManager(float initialModelScale);
        virtual ~ModelManager();

        uint32_t getModelTick() const;

        // Wraps updateOneTick() in some admin
        void doTick();

        /**  UI  **/
        // (x,y) in game coordinates
        virtual void pickActiveEntity(float x, float y);
        virtual void click();
        virtual void releaseMouse();

        virtual void draw(UiManager &uiManager);
};

#endif // MODEL_MANAGER_HPP
