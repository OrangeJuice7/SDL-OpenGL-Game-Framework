#include "Entity.hpp"

#include <SDL.h>
#include "../../MainUiManager/MainUiManager.hpp"

EntityData::EntityData() {
    //this->radius = radius;
}



Entity::Entity() : Entity(emptyEntityData, 0, 0, 0, 0, 1, 1, 1) {}
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

void Entity::applyForce(float forceX, float forceY) {
    xvel += forceX / mass;
    yvel += forceY / mass;
}

void Entity::doTick() {
    x += xvel;
    y += yvel;
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
