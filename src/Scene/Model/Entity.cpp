#include "Entity.hpp"

#include "../../util/math.hpp"
#include "GameModelManager.hpp"
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

void ImmovableEntity::doTick(GameModelManager& model) {}

bool ImmovableEntity::isWithinScreen(UiManager &uiManager) const {
    // Bounding box check
    float bx, by, bX, bY;
    float r = getRadius();
    uiManager.gameToScreenCoords(bx, by, x-r, y-r);
    uiManager.gameToScreenCoords(bX, bY, x+r, y+r);

    return (bX >= 0 && bx < uiManager.getScreenWidth() &&
            bY >= 0 && by < uiManager.getScreenHeight() );
}
void ImmovableEntity::draw(UiManager &uiManager) const {
    float a = getLifeFraction();
    uiManager.setColorMask({a, 0, a});
    uiManager.setObjectScale(getRadius());
    uiManager.drawSprite(x, y, SPRITE_ID_CIRCLE);
}



Entity::Entity() : Entity(0, 0, 0, 0, 1) {}
Entity::Entity(float x, float y, float xvel, float yvel, float life)
        : ImmovableEntity(x, y, life) {

    this->observedVelX = this->xvel = xvel;
    this->observedVelY = this->yvel = yvel;
}
Entity::~Entity() {}

float Entity::getObservedVelX() const { return observedVelX; }
float Entity::getObservedVelY() const { return observedVelY; }
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

void Entity::doTick(GameModelManager& model) {
    x += observedVelX = xvel;
    y += observedVelY = yvel;

    // Apply wind
    applyForce(
        (model.getWindVelX() - xvel) * model.getWindDragCoeff(),
        (model.getWindVelY() - yvel) * model.getWindDragCoeff());
}
