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

        // Map borders?

        void doTick(GameModelManager& model);
        void draw(UiManager &uiManager) const;

    protected:
        float windVelX,
              windVelY;
};

#endif // MAP_HPP
