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

        // Respawn a mob somewhere
        const MobData* data = (MobData*)m->data; // Really needs to be replaced once a better Entity system is in
        if (playerMob == nullptr) spawnPlayerMob(*data, 0, 0);
        else spawnMob(*data, getrand()*16 -8, getrand()*16 -8);
    });
    projectiles.doTick();
    explosions.doTick();
    particles.doTick();

    /** Inter-entity interactions (esp. collision detection and resolution) **/
    // Note: spawn all explosions first, then check interactions with them

    // Mob-mob
    mobs.checkCollisionsSelf([](Mob& m1, Mob& m2) {
        if (m1.isColliding(m2)) { // Colliding
            // Repel
            float dirX = m1.x - m2.x,
                  dirY = m1.y - m2.y;
            float dist = getdist(dirX, dirY);
            dirX /= dist;
            dirY /= dist;

            /*float momDiffX = m1.xvel*m1.getMass() - m2.xvel*m2.getMass(),
                  momDiffY = m1.yvel*m1.getMass() - m2.yvel*m2.getMass();
            float mag = getdist(momDiffX, momDiffY);*/
            float mag = .1f * (1 + getdist(m1.xvel-m2.xvel, m1.yvel-m2.yvel));

            float forceX = dirX * mag,
                  forceY = dirY * mag;
            m1.applyForce( forceX *m1.getMass(), forceY *m1.getMass()); // Already conserves momentum
            m2.applyForce(-forceX *m2.getMass(),-forceY *m2.getMass());
        }
    });

    // Projectile-mob
    projectiles.checkCollisions<Mob>(mobs, [this](Projectile& p, Mob& m) {
        if (p.isColliding(m)) { // Colliding
            // Backtrack projectile to point of contact
            float pVelDirX = p.xvel,
                  pVelDirY = p.yvel;
            float pSpeed = getdist(pVelDirX, pVelDirY);
            pVelDirX /= pSpeed;
            pVelDirY /= pSpeed;

            float distX = m.x - p.x,
                  distY = m.y - p.y;
            float r = m.getRadius() + p.getRadius();
            // Magic maffs
            {   float a = pVelDirX*distX + pVelDirY*distY; // dist between p and (m projected to p.vel)
                float l = sqrt(r*r + a*a - getdist2(distX, distY)); // dist between (m projected to p.vel) and actual point of intersection
                float f = a-l;
                p.x += f * pVelDirX;
                p.y += f * pVelDirY;
            }

            // Do damage
            //m.life -= .2f;

            // Spawn (killzone) explosion
            spawnExplosion(genericExplosionData, p.x, p.y);

            // Push back mob with momentum from projectile i.e. add all of the projectile's momentum to the mob
            // new_m.momentum = p.momentum + m.momentum => mm*nv = pm*pv + mm*mv => nv = pm*pv/mm + mv
            m.xvel += p.xvel * p.getMass() / m.getMass();
            m.yvel += p.yvel * p.getMass() / m.getMass();

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
            float sdist = sqrt(dist2) - m.getRadius(); if (sdist < 0) sdist = 0; // "short" distance

            // Do damage (decays with distance from epicenter, to 1/2 damage at edge)
            float maxDamage = .05f;
            m.life -= maxDamage / (sdist / e.getRadius() + 1);

            // Push back, inversely proportionate to squared distance
            float forceMod = .1f / dist2;
            m.applyForce( distx*forceMod, disty*forceMod);
        }
    });

    // Explosion-projectile
    /*explosions.checkCollisions<Projectile>(projectiles, [](Explosion& e, Projectile& p) {
        if (!e.isOnInitialTick()) return; // Only do stuff on the initial tick
        if (e.isColliding(p)) { // Colliding
            float distx = p.x - e.x,
                  disty = p.y - e.y;
            float dist2 = getdist2(distx, disty);

            // Push back, inversely proportionate to squared distance
            float forceMod = .1f / dist2;
            p.applyForce( distx*forceMod, disty*forceMod);
        }
    });*/

    // Explosion-particle
    /*explosions.checkCollisions<Particle>(particles, [](Explosion& e, Particle& p) {
        if (!e.isOnInitialTick()) return; // Only do stuff on the initial tick
        if (e.isColliding(p)) { // Colliding
            float distx = p.x - e.x,
                  disty = p.y - e.y;
            float dist2 = getdist2(distx, disty);

            // Push back, inversely proportionate to squared distance
            float forceMod = .1f / dist2;
            p.applyForce( distx*forceMod, disty*forceMod);
        }
    });*/
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
    Particle p(x, y, 0, 0, .2f, 30, 1);

    for (int i = 0; i < numOfParticles; ++i) {
        p.radius = (1 - .5f*pow(getrand(), 3))*maxRadius;
        p.mass = 0.5f * pow(p.getRadius(), 3);

        p.life = p.maxLife = p.getRadius()*150;

        float angle = getrand() * TWO_PI;
        float a = getrand();
        float vel = sqrt(1-a*a) * maxVel; vel /= p.getMass()*100; vel *= getrand();
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
