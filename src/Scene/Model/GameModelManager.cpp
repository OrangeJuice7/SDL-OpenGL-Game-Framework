#include "GameModelManager.hpp"

#include "../../basicmath.hpp"
#include "../../MainUiManager/MainUiManager.hpp"

GameModelManager::GameModelManager()
        : ModelManager(32)
        , particles() {

    //(nothing)
}
GameModelManager::~GameModelManager() {}

void GameModelManager::updateOneTick() {
    // Update the entities individually
    particles.doTick();

    // Inter-entity interactions (esp. collision detection and resolution)
    /*particles.checkCollisionsSelf([](const Particle& p1, const Particle& p2) {
        // particle-particle interaction code here
    });
    particles.checkCollisions(projectiles, [](const Particle& particle, const Projectile& projectile) {
        // particle-projectile interaction code here
    });*/
}

void GameModelManager::spawnParticleExplosion(int numOfParticles, float x, float y, float maxVel, float maxRadius) {
    Particle p(emptyParticleData, x, y, 0, 0, .2f, 30, 1);

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

void GameModelManager::pickActiveEntity(float x, float y) {
    //
}
void GameModelManager::click() {
    //
}

void GameModelManager::draw(MainUiManager *uiManager) {
    auto gameToScreenCoordsFunc = getGameToScreenCoordsFunc(uiManager);
    auto gameToScreenLengthFunc = getGameToScreenLengthFunc();

    particles.draw(gameToScreenCoordsFunc, gameToScreenLengthFunc, uiManager);
}
