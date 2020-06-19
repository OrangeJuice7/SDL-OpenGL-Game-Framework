#ifndef MAP_HPP
#define MAP_HPP

class UiManager;

class Map {
    public:
        Map();
        virtual ~Map();

        float getWindVelX() const;
        float getWindVelY() const;

        // Map borders?

        void draw(UiManager &uiManager) const;

    protected:
        float windVelX,
              windVelY;
};

#endif // MAP_HPP
