#include "MobAi.hpp"

#include "Mob.hpp"
#include "GameModelManager.hpp"

MobAi::MobAi() {}
MobAi::~MobAi() {}

GunnerMobAi::GunnerMobAi() : MobAi() {}
GunnerMobAi::~GunnerMobAi() {}
void GunnerMobAi::act(Mob& mob, GameModelManager& model) {
    Mob* playerMob = model.getPlayerMob();
    if (playerMob) {
        mob.leadAndFireAtEntity(0, model, *playerMob);
    }
}
