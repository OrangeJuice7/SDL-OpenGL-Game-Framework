#include "GameModelManager.hpp"

#include "../../basicmath.hpp"
#include "../../MainUiManager/MainUiManager.hpp"

GameModelManager::GameModelManager()
        : ModelManager(32)
        , mobs()
        , particles() {

    activeMob = nullptr;
    playerMob = nullptr;
}
GameModelManager::~GameModelManager() {}

Mob* GameModelManager::getActiveMob() const {
    return activeMob;
}
Mob* GameModelManager::getPlayerMob() const {
    return playerMob;
}

void GameModelManager::updateOneTick() {
    spawnParticleExplosion(2, 0, 0, .1f, .2f);

    // Update the entities individually
    mobs.doTick([=](const Mob* pMob) {
        if (activeMob == pMob) activeMob = nullptr;
        if (playerMob == pMob) playerMob = nullptr;
    });

    particles.doTick();

    /** Inter-entity interactions (esp. collision detection and resolution) **/

    // Mob-mob
    mobs.checkCollisionsSelf([](Mob& m1, Mob& m2) {
        if (m1.isColliding(m2)) { // Colliding
            // Repel
            float distx = m1.x - m2.x,
                  disty = m1.y - m2.y;
            float overlap = (m1.radius + m2.radius) - getdist(distx, disty);

            m1.applyForce( distx*overlap, disty*overlap);
            m2.applyForce(-distx*overlap,-disty*overlap);

            // Add damage
            /*m1.life -= .2f;
            m2.life -= .2f;*/
        }
    });

    // Particle-projectile
    /*particles.checkCollisions(projectiles, [](Particle& particle, Projectile& projectile) {
        //
    });*/
}

void GameModelManager::spawnParticleExplosion(int numOfParticles, float x, float y, float maxVel, float maxRadius) {
    Particle p(genericParticleData, x, y, 0, 0, .2f, 30, 1);

    for (int i = 0; i < numOfParticles; ++i) {
        p.radius = (1 - .5f*pow(getrand(), 3))*maxRadius;
        p.mass = 0.5f * pow(p.radius, 3);

        p.life = p.maxLife = p.radius*150;

        float angle = getrand() * TWO_PI;
        float a = getrand();
        float vel = sqrt(1-a*a) * maxVel; vel /= p.mass*100; vel *= getrand();
        p.xvel = sin(angle)*vel;
        p.yvel = cos(angle)*vel;

        particles.addEntity(p);
    }
}
Mob* GameModelManager::spawnMob(const MobData &data, float x, float y) {
    Mob mob(data, x, y);
    return mobs.addEntity(mob);
}
Mob* GameModelManager::spawnPlayerMob(const MobData &data, float x, float y) {
    return playerMob = spawnMob(data, x, y);
}

void GameModelManager::pickActiveEntity(float x, float y) {
    activeMob = mobs.pickEntity(x,y);
}
void GameModelManager::click() {
    //
}

void GameModelManager::draw(MainUiManager *uiManager) {
    auto gameToScreenCoordsFunc = getGameToScreenCoordsFunc(uiManager);
    auto gameToScreenLengthFunc = getGameToScreenLengthFunc();

    mobs.draw(gameToScreenCoordsFunc, gameToScreenLengthFunc, uiManager);
    particles.draw(gameToScreenCoordsFunc, gameToScreenLengthFunc, uiManager);
}
