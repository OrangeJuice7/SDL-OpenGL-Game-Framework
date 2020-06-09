#ifndef MOB_HPP
#define MOB_HPP

#include "Entity.hpp"
#include "Weapon.hpp"
#include "../../ui/SpriteId.hpp"

struct MobData {
    float radius;
    float maxLife;
    float mass;
    // default Weapons?

    SpriteId spriteId;

    MobData(float radius, float maxLife, float mass, SpriteId spriteId);
};
const MobData genericMobData(1, 1, 1, SPRITE_ID_ELF);
const MobData gunnerMobData(1, 1, 1, SPRITE_ID_ELF);
const MobData heavyMobData(2, 2, 8, SPRITE_ID_ELF);



class Mob : public Entity {
    public:
        const MobData * const data; // Change to `const MobData& data;`?

        Mob(); // default constructor
        Mob(const MobData &data, float x, float y);
        virtual ~Mob();

        float getRadius() const;
        float getMaxLife() const;
        float getMass() const;
        // Will return nullptr if ID does not exist
        Weapon* getWeapon(WeaponManagerWeaponId id);
        const Weapon* getWeapon(WeaponManagerWeaponId id) const;

        WeaponManagerWeaponId addWeapon(const WeaponData &weaponData);
        bool removeWeapon(WeaponManagerWeaponId id);

        // Fire this Mob's Weapon at the specified position (if the Weapon can fire etc.)
        void fireAtPosition(WeaponManagerWeaponId weaponId, GameModelManager &model, float targetX, float targetY);
        void fireAtEntity(WeaponManagerWeaponId weaponId, GameModelManager &model, const ImmovableEntity& target);
        void leadAndFireAtEntity(WeaponManagerWeaponId weaponId, GameModelManager &model, const Entity& target); // Lead the shot i.e. fire where the target is predicted to be (approx only)

        virtual void doTick();
        virtual void draw(UiManager &uiManager);

    protected:
        WeaponManager weapons;
};

#endif // MOB_HPP

