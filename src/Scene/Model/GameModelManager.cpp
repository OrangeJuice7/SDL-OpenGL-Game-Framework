#include "GameModelManager.hpp"

#include "../../basicmath.hpp"
#include "../../ui/UiManager.hpp"

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
            float diffX = m2.x - m1.x,
                  diffY = m2.y - m1.y;
            float dist2 = getdist2(diffX, diffY);
            if (dist2 <= 0) return; // Do nothing if the mobs are exactly on top of each other. Otherwise the position of the mobs might be yeeted to nan
            float dist = sqrt(dist2);

            // Repel: set velocity
            float diffVelX = m1.xvel - m2.xvel,
                  diffVelY = m1.yvel - m2.yvel;

            float a = -(diffX*diffVelX + diffY*diffVelY) / dist2;
            if (a < 0) {
                a *= std::min(m1.getMass(), m2.getMass());

                float forceX = a * diffX,
                      forceY = a * diffY;
                m1.applyForce( forceX, forceY);
                m2.applyForce(-forceX,-forceY);
            }

            // Repel: resolve overlap
            float overlap = m1.getRadius() + m2.getRadius() - sqrt(dist2);
            float totalMass = m1.getMass() + m2.getMass();
            float m1compense = overlap * (m2.getMass() / totalMass),
                  m2compense = overlap * (m1.getMass() / totalMass);
            m1.x -= diffX/dist * m1compense;
            m1.y -= diffY/dist * m1compense;
            m2.x += diffX/dist * m2compense;
            m2.y += diffY/dist * m2compense;
        }
    });

    // Projectile-mob
    projectiles.checkCollisions<Mob>(mobs, [this](Projectile& p, Mob& m) {
        if (p.isColliding(m)) { // Colliding
            p.backtrackToPointOfContact(m);
            p.damageEntity(m);
            p.pushEntity(m);

            // Kill projectile
            p.kill();
            // Spawn (killzone) explosion
            if (p.getExplosionData()) spawnExplosion(*p.getExplosionData(), p.x, p.y);
            // Spawn (particle) explosion
            spawnParticleExplosion(20, p.x, p.y, .1f, .2f);
        }
    });

    // Explosion-mob
    explosions.checkCollisions<Mob>(mobs, [](Explosion& e, Mob& m) {
        if (!e.isOnInitialTick()) return; // Only do stuff on the initial tick
        if (e.isColliding(m)) { // Colliding
            e.pushEntity(m);
            e.damageEntity(m);
        }
    });

    // Explosion-projectile
    /*explosions.checkCollisions<Projectile>(projectiles, [](Explosion& e, Projectile& p) {
        if (!e.isOnInitialTick()) return; // Only do stuff on the initial tick
        if (e.isColliding(p)) { // Colliding
            e.pushEntity(p);
        }
    });*/

    // Explosion-particle
    /*explosions.checkCollisions<Particle>(particles, [](Explosion& e, Particle& p) {
        if (!e.isOnInitialTick()) return; // Only do stuff on the initial tick
        if (e.isColliding(p)) { // Colliding
            e.pushEntity(p);
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

void GameModelManager::draw(UiManager *uiManager) {
    auto gameToScreenCoordsFunc = getGameToScreenCoordsFunc(uiManager);
    auto gameToScreenLengthFunc = getGameToScreenLengthFunc();

    mobs.draw(gameToScreenCoordsFunc, gameToScreenLengthFunc, uiManager);
    projectiles.draw(gameToScreenCoordsFunc, gameToScreenLengthFunc, uiManager);
    explosions.draw(gameToScreenCoordsFunc, gameToScreenLengthFunc, uiManager);
    particles.draw(gameToScreenCoordsFunc, gameToScreenLengthFunc, uiManager);
}
