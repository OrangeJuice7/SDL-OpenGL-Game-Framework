#ifndef MOB_AI_HPP
#define MOB_AI_HPP

#include <functional>
class Mob;
class GameModelManager;

// Mob AI Base class, essentially just an interface
class MobAi {
    public:
        MobAi();
        virtual ~MobAi();

        virtual void act(Mob& mob, GameModelManager& model)=0;
};

// A function that constructs a new MobAi to assign to a new mob
typedef std::function<MobAi*()> MobAiConstructor;

// AiConstructor for "No AI"
const MobAiConstructor emptyMobAiConstructor = [](){ return nullptr; };



class GunnerMobAi : public MobAi {
    public:
        GunnerMobAi();
        ~GunnerMobAi();

        void act(Mob& mob, GameModelManager& model);
};
const MobAiConstructor gunnerMobAiConstructor = []() -> GunnerMobAi* { return new GunnerMobAi(); };

#endif // MOB_AI_HPP
