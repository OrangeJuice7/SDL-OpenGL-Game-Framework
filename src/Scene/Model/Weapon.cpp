#include "Weapon.hpp"

#include "GameModelManager.hpp"

Weapon::Weapon() : Weapon(genericWeaponData) {}
Weapon::Weapon(const WeaponData &data)
        : data(&data) {

    timeout = 0;
}
Weapon::~Weapon() {}

float Weapon::getTimeout() const {
    return timeout;
}
bool Weapon::isReadyToFire() const {
    return timeout <= 0;
}

Projectile* Weapon::fireIfReady(GameModelManager &model, float x, float y, float xvel, float yvel) {
    if (isReadyToFire()) return fire(model, x, y, xvel, yvel);
    else return nullptr;
}
void Weapon::fireUntilNotReady(GameModelManager &model, float x, float y, float xvel, float yvel) {
    while (isReadyToFire()) fire(model, x, y, xvel, yvel);
}
Projectile* Weapon::fire(GameModelManager &model, float x, float y, float xvel, float yvel) {
    // Sub-tick correction
    // Warning: Does not account for other updates within the Projectile, such as life drain
    float timeCorrection = -timeout;
    x += xvel * timeCorrection;
    y += yvel * timeCorrection;

    // Increment the timeout
    timeout += data->reloadPeriod;

    // Spawn the projectile
    return model.spawnProjectile(*(data->projectileData), x, y, xvel, yvel);
}

void Weapon::doTick() {
    // Tick down the timeout
    // Note: Done this way to give some spillover to the timeout, if the reloadPeriod has sub-tick precision
    if (timeout <= 0) {
        timeout = 0;
    } else {
        --timeout;
    }
}



WeaponManager::WeaponManager() {
    nextId = 0;
}
WeaponManager::~WeaponManager() {}

WeaponManagerWeaponId WeaponManager::addWeapon(const WeaponData &weaponData) {
    WeaponManagerWeaponId oldId = nextId;

    while (!weapons.emplace(nextId, weaponData).second) {
        ++nextId;
        if (nextId == oldId) return 0; // Allocation failed
    }
    return nextId++;
}
bool WeaponManager::removeWeapon(WeaponManagerWeaponId id) {
    return weapons.erase(id) == 1;
}
Weapon* WeaponManager::getWeapon(WeaponManagerWeaponId id) {
    Weapon* weapon = nullptr;
    try {
        weapon = &(weapons.at(id));
    } catch (const std::out_of_range& oor) {
        weapon = nullptr;
    }
    return weapon;
}

void WeaponManager::doTick() {
    for (auto it = weapons.begin(); it != weapons.end(); ++it) {
        it->second.doTick();
    }
}
