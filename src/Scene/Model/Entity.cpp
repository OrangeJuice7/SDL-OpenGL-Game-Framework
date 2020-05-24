#include "Entity.hpp"

#include <SDL2/SDL.h>
#include "../../basicmath.hpp"
#include "../../ui/UiManager.hpp"

ImmovableEntity::ImmovableEntity() : ImmovableEntity(0, 0, 1) {}
ImmovableEntity::ImmovableEntity(float x, float y, float life) {
    this->x = x;
    this->y = y;
    this->life = life;
}
ImmovableEntity::~ImmovableEntity() {}

float ImmovableEntity::getLifeFraction() const {
    return life / getMaxLife();
}
bool ImmovableEntity::isDead() const {
    return life <= 0;
}

bool ImmovableEntity::isColliding(const ImmovableEntity& other) const {
    float x2 = other.x,
          y2 = other.y,
          r = getRadius() + other.getRadius();

    // Bounding box check
    if (x < x2-r || x > x2+r ||
        y < y2-r || y > y2+r ) return false;

    // Circle check
    return (getdist2(x2-x,y2-y) <= r*r);
}

void ImmovableEntity::takeDamage(float dmg) {
    life -= dmg;
}

void ImmovableEntity::kill() {
    life = -1; // 0 should work, but -1 just to be safe from floating point errors
}

void ImmovableEntity::doTick() {}

bool ImmovableEntity::isWithinScreen(
        std::function<void(int&, int&, float, float)> gameToScreenCoords,
        UiManager *uiManager) const {

    // Bounding box check
    int bx, bX, by, bY;
    float r = getRadius();
    gameToScreenCoords(bx, by, x-r, y+r);
    gameToScreenCoords(bX, bY, x+r, y-r);

    return (bX >= 0 && bx < uiManager->SCREEN_RECT.w &&
            bY >= 0 && by < uiManager->SCREEN_RECT.h );
}
void ImmovableEntity::draw(
        std::function<void(int&, int&, float, float)> gameToScreenCoords,
        std::function<float(float)> gameToScreenLength,
        UiManager *uiManager) {

    float a = getLifeFraction();
    uiManager->setColorMask({a, 0, a});
    uiManager->setObjectScale(getRadius());
    uiManager->drawSprite(x, y, SPRITE_ID_CIRCLE);
}



Entity::Entity() : Entity(0, 0, 0, 0, 1) {}
Entity::Entity(float x, float y, float xvel, float yvel, float life)
        : ImmovableEntity(x, y, life) {

    this->xvel = xvel;
    this->yvel = yvel;
}
Entity::~Entity() {}

void Entity::applyForce(float forceX, float forceY) {
    xvel += forceX / getMass();
    yvel += forceY / getMass();
}

void Entity::backtrackToPointOfContact(const ImmovableEntity &e) {
    float speed = getdist(xvel, yvel);
    float velDirX = xvel / speed,
          velDirY = yvel / speed;

    float distX = e.x - x,
          distY = e.y - y;
    float r = e.getRadius() + getRadius();
    // Magic maffs
    {   float a = velDirX*distX + velDirY*distY; // dist between p and (m projected to p.vel)
        float l = sqrt(r*r + a*a - getdist2(distX, distY)); // dist between (m projected to p.vel) and actual point of intersection
        float f = a-l;
        x += f * velDirX;
        y += f * velDirY;
    }
}

void Entity::doTick() {
    x += xvel;
    y += yvel;
}
