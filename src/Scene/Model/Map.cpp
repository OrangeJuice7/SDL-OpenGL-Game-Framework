#include "Map.hpp"

#include "../../ui/UiManager.hpp"

Map::Map() {
    windVelX = -0.2f;
    windVelY =  0.0f;
}
Map::~Map() {}

float Map::getWindVelX() const {
    return windVelX;
}
float Map::getWindVelY() const {
    return windVelY;
}

void Map::draw(UiManager &uiManager) const {
    uiManager.resetColorMask();
    uiManager.setObjectScale(.5f);
    for (float x = -30; x <= 30; ++x) { for (float y = -30; y <= 30; ++y) {
        uiManager.drawSprite(x, y, SPRITE_ID_TILE_GRASS);
    }}
}
