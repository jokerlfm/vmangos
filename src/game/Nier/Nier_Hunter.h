#ifndef NIER_ACTION_HUNTER_H
#define NIER_ACTION_HUNTER_H

#include "Nier_Base.h"

enum HunterAspectType :uint32
{
    HunterAspectType_Hawk = 0,
    HunterAspectType_Monkey,
    HunterAspectType_Wild,
    HunterAspectType_Pack,
};

class Nier_Hunter :public Nier_Base
{
public:
    Nier_Hunter(Player* me);
    void InitializeCharacter(uint32 pmTargetLevel, uint32 pmSpecialtyTabIndex);
    void ResetTalent();
    bool InitializeEquipments(bool pmReset);
    void Prepare();
    bool DPS(Unit* pmTarget, bool pmRushing, float pmDistanceMax, float pmDistanceMin, bool pmHolding, bool pmInstantOnly, bool pmChasing);
    bool AOE(Unit* pmTarget, bool pmRushing, float pmDistanceMax, float pmDistanceMin, bool pmHolding, bool pmInstantOnly, bool pmChasing);
    bool Buff(Unit* pmTarget);
    bool Petting(bool pmSummon = true, bool pmReset = false);

    uint32 aspectType;

private:
    uint32 spell_ArcaneShot;
    uint32 spell_SerpentSting;
    uint32 spell_RapidFire;
    uint32 spell_HuntersMark;
    uint32 spell_Volley;
    uint32 spell_AspectOfTheHawk;
    uint32 spell_CallPet;
    uint32 spell_DismissPet;
    uint32 spell_RevivePet;
    uint32 spell_ConcussiveShot;
    uint32 spell_AutoShot;

    uint32 spell_TrueshotAura;

    uint32 ammoEntry;
};
#endif
