#include "Entity.hpp"

#include <SDL.h>
#include "../../basicmath.hpp"
#include "../../MainUiManager/MainUiManager.hpp"

EntityData::EntityData() {
    //this->radius = radius;
}



Entity::Entity() : Entity(genericEntityData, 0, 0, 0, 0, 1, 1, 1) {}
Entity::Entity(const EntityData &data, float x, float y, float xvel, float yvel, float radius, float maxLife, float mass) {
    this->data = &data;
    this->x = x;
    this->y = y;
    this->xvel = xvel;
    this->yvel = yvel;
    this->radius = radius;
    this->life = this->maxLife = maxLife;
    this->mass = mass;
}

float Entity::getLifeFraction() const { return life / maxLife; }
bool Entity::isDead() const { return life <= 0; }
bool Entity::isColliding(const Entity& other) const {
    float x2 = other.x,
          y2 = other.y,
          r = radius + other.radius;

    // Bounding box check
    if (x < x2-r || x > x2+r ||
        y < y2-r || y > y2+r ) return false;

    // Circle check
    return (getdist2(x2-x,y2-y) <= r*r);
}

void Entity::applyForce(float forceX, float forceY) {
    xvel += forceX / mass;
    yvel += forceY / mass;
}

void Entity::doTick() {
    x += xvel;
    y += yvel;
}

bool Entity::isWithinScreen(
        std::function<void(int&, int&, float, float)> gameToScreenCoords,
        MainUiManager *uiManager) const {

    // Bounding box check
    int bx, bX, by, bY;
    gameToScreenCoords(bx, by, x - radius, y + radius);
    gameToScreenCoords(bX, bY, x + radius, y - radius);

    return (bX >= 0 && bx < uiManager->SCREEN_RECT.w &&
            bY >= 0 && by < uiManager->SCREEN_RECT.h );
}
void Entity::draw(
        std::function<void(int&, int&, float, float)> gameToScreenCoords,
        std::function<float(float)> gameToScreenLength,
        MainUiManager *uiManager) {

    // Just draw a magenta rect that fades with life, as a debug display

    float r = radius;

    SDL_Rect rect;
    gameToScreenCoords(rect.x, rect.y, x-r, y+r);
    gameToScreenCoords(rect.w, rect.h, x+r, y-r);
    rect.w -= rect.x;
    rect.h -= rect.y;

    uiManager->setDrawColor(0xff, 0x00, 0xff, (Uint8)(getLifeFraction()*0xff) );
    uiManager->drawFillRect(rect);
}
