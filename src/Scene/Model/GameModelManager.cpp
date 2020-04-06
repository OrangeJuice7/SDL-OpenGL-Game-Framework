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
    //spawnParticleExplosion(2, 0, 0, .1f, .2f);

    /**  Update the entities individually **/
    mobs.doTick([=](const Mob* m) {
        // Dereference activeMob / playerMob
        if (activeMob == m) activeMob = nullptr;
        if (playerMob == m) playerMob = nullptr;

        // Spawn (particle) explosion
        spawnParticleExplosion(100, m->x, m->y, .8f, .4f);
    });
    projectiles.doTick();
    // Explosions are left to the end, since their initial state is important
    particles.doTick();

    /** Inter-entity interactions (esp. collision detection and resolution) **/
    // Note: spawn all explosions first, then check interactions with them

    // Mob-mob
    mobs.checkCollisionsSelf([](Mob& m1, Mob& m2) {
        if (m1.isColliding(m2)) { // Colliding
            // Repel
            // Note: not the best way to repel since the force depends on how far in the two mobs overlap, which is affected by how coarse the frame rate is
            float distx = m1.x - m2.x,
                  disty = m1.y - m2.y;
            float overlap = (m1.radius + m2.radius) - getdist(distx, disty);

            m1.applyForce( distx*overlap, disty*overlap);
            m2.applyForce(-distx*overlap,-disty*overlap);
        }
    });

    // Projectile-mob
    projectiles.checkCollisions<Mob>(mobs, [this](Projectile& p, Mob& m) {
        if (p.isColliding(m)) { // Colliding
            // Do damage
            //m.life -= .2f;

            // Spawn (killzone) explosion
            spawnExplosion(genericExplosionData, p.x, p.y);

            // Push back mob with momentum from projectile i.e. add all of the projectile's momentum to the mob
            // new_m.momentum = p.momentum + m.momentum => mm*nv = pm*pv + mm*mv => nv = pm*pv/mm + mv
            m.xvel += p.xvel * p.mass / m.mass;
            m.yvel += p.yvel * p.mass / m.mass;

            // Kill projectile
            p.kill();
            // Spawn (particle) explosion
            spawnParticleExplosion(20, p.x, p.y, .1f, .2f);
        }
    });

    // Explosion-mob
    explosions.checkCollisions<Mob>(mobs, [](Explosion& e, Mob& m) {
        if (!e.isOnInitialTick()) return; // Only do stuff on the initial tick
        if (e.isColliding(m)) { // Colliding
            float distx = m.x - e.x,
                  disty = m.y - e.y;
            float dist2 = getdist2(distx, disty);
            float sdist2 = dist2 - m.radius; if (sdist2 < 0) sdist2 = 0; // "short" distance

            // Do damage (decays with distance from epicenter, to 1/2 damage at edge)
            float maxDamage = .05f;
            m.life -= maxDamage / (sdist2 / e.radius*e.radius + 1);

            // Push back
            float forceMod = .1f / dist2;
            m.applyForce( distx*forceMod, disty*forceMod);
        }
    });

    // Explosion-projectile
    /*explosions.checkCollisions(projectiles, [](Explosion& e, Projectile& p) {
        //
    });*/

    // Explosion-particle
    /*explosions.checkCollisions(particles, [](Explosion& e, Particle& p) {
        //
    });*/

    explosions.doTick();
}

Mob* GameModelManager::spawnMob(const MobData &data, float x, float y) {
    Mob mob(data, x, y);
    return mobs.addEntity(mob);
}
Mob* GameModelManager::spawnPlayerMob(const MobData &data, float x, float y) {
    return playerMob = spawnMob(data, x, y);
}
Projectile* GameModelManager::spawnProjectile(const ProjectileData &data, float x, float y, float xvel, float yvel) {
    Projectile projectile(data, x, y, xvel, yvel);
    return projectiles.addEntity(projectile);
}
Explosion* GameModelManager::spawnExplosion(const ExplosionData &data, float x, float y) {
    Explosion explosion(data, x, y);
    return explosions.addEntity(explosion);
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
    projectiles.draw(gameToScreenCoordsFunc, gameToScreenLengthFunc, uiManager);
    explosions.draw(gameToScreenCoordsFunc, gameToScreenLengthFunc, uiManager);
    particles.draw(gameToScreenCoordsFunc, gameToScreenLengthFunc, uiManager);
}
