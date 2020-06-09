#ifndef WEAPON_HPP
#define WEAPON_HPP

#include <unordered_map>
#include "Projectile.hpp"
class GameModelManager; // Weapons have to spawn a Projectile *somewhere*

struct WeaponData {
    const ProjectileData* projectileData; // nullptr = no projectile fired
    float projectileSpeed; // (On Projectile spawn, anyway) (Can think of how to address the case where the owner can specify the speed)
    float reloadPeriod; // (Minimum) time in between successive shots, in ticks
    bool hasAutofire; // !! not actually in use
};
const WeaponData    genericWeaponData = {&  genericProjectileData, 1.2, 4, true};
const WeaponData     pistolWeaponData = {&    lightProjectileData, 1.2, 20, true};
const WeaponData machineGunWeaponData = {&    lightProjectileData, 1.2, .618, true};
const WeaponData  explosiveWeaponData = {&explosiveProjectileData, 0.8, 10, true};



class Weapon {
    public:
        const WeaponData * const data;

        Weapon(); // default constructor
        Weapon(const WeaponData &data);
        virtual ~Weapon();

        float getTimeout() const;
        bool isReadyToFire() const;

        // Shoot the weapon
        // Note: All except fireUntilNotReady() assume the reloadPeriod is at least 1 tick.
        // Note: does not actually use data->projectileSpeed; that's for the owner to reference and control instead
        Projectile* fireIfReady(GameModelManager &model, float x, float y, float xvel, float yvel); // Only fire if ready
        void fireUntilNotReady(GameModelManager &model, float x, float y, float xvel, float yvel); // Fire until timeout is positive
        Projectile* fire(GameModelManager &model, float x, float y, float xvel, float yvel); // Ignore fire rate restrictions

        void doTick();

    protected:
        float timeout; // Time left till the weapon is ready to fire again
};



/**
 *  Put this WeaponManager in whichever Entity class potentially uses Weapons.
 */
typedef unsigned char WeaponManagerWeaponId;
class WeaponManager {
    public:
        WeaponManager();
        virtual ~WeaponManager();

        WeaponManagerWeaponId addWeapon(const WeaponData &weaponData); // Returns the ID of the new weapon (Note: What to return on failure? Throw exception?)
        bool removeWeapon(WeaponManagerWeaponId id); // Returns true on success
        // Will return nullptr if ID does not exist
        Weapon* getWeapon(WeaponManagerWeaponId id);
        const Weapon* getWeapon(WeaponManagerWeaponId id) const;

        void doTick();

    protected:
        std::unordered_map<WeaponManagerWeaponId, Weapon> weapons;

        WeaponManagerWeaponId nextId;
};

#endif // WEAPON_HPP
