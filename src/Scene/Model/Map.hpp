#ifndef MAP_HPP
#define MAP_HPP

class GameModelManager;
class UiManager;

class Map {
    public:
        Map();
        virtual ~Map();

        float getWindVelX() const;
        float getWindVelY() const;
        float getWindDragCoeff() const;

        // Map borders?

        void doTick(GameModelManager& model);
        void draw(UiManager &uiManager) const;

    protected:
        float windVelX,
              windVelY;
        float windDragCoeff; // This is the coeff in Hooke's law for springs (where the springed quantity is velocity)
};

#endif // MAP_HPP
