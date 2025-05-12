#ifndef NIER_HUNTER_H
#define NIER_HUNTER_H

#include "Nier_Base.h"

enum HunterAspectType :uint32
{
    HunterAspectType_Hawk = 0,
    HunterAspectType_Monkey,
    HunterAspectType_Wild,
    HunterAspectType_Pack,
};

class Nier_Base;

class Nier_Hunter :public Nier_Base
{
public:
    Nier_Hunter();
    bool Attack(Unit* pTarget);
    bool Tank(Unit* pTarget);
    bool Heal(Unit* pTarget);
    bool Cure(Unit* pTarget);
    bool Buff(Unit* pTarget);
    bool Revive(Unit* pTarget);
    bool InitializeCharacter(uint32 pTargetLevel);
    bool ResetTalentsAndSpells();
    void EquipRandomItem(uint32 pEquipSlot);

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
