#ifndef NIER_ACTION_DRUID_H
#define NIER_ACTION_DRUID_H

#include "Nier_Base.h"

class Nier_Druid :public Nier_Base
{
public:
    Nier_Druid(Player* pmMe);
    void InitializeCharacter(uint32 pmTargetLevel, uint32 pmSpecialtyTabIndex);
    void ResetTalent();
    bool InitializeEquipments(bool pmReset);
    void Prepare();
    bool DPS(Unit* pmTarget, bool pmRushing, float pmDistanceMax, float pmDistanceMin, bool pmHolding, bool pmInstantOnly, bool pmChasing);
    bool AOE(Unit* pmTarget, bool pmRushing, float pmDistanceMax, float pmDistanceMin, bool pmHolding, bool pmInstantOnly, bool pmChasing);
    bool Cure(Unit* pmTarget);
    bool Buff(Unit* pmTarget);
    bool Revive(Player* pmTarget);
    bool Mark(Unit* pmTarget, int pmRTI);
    bool Assist(int pmRTI);    

public:
    uint32 spell_InsectSwarm;
    uint32 spell_MoonkinForm;
    uint32 spell_Typhoon;
    uint32 spell_Starfall;
    uint32 spell_Wrath;
    uint32 spell_Rebirth;
    uint32 spell_Innervate;
    uint32 spell_RemoveCurse;
    uint32 spell_Thorns;
    uint32 spell_FaerieFire;
    uint32 spell_EntanglingRoots;
    uint32 spell_Hurricane;
    uint32 spell_Revive;
    uint32 spell_Barkskin;
    uint32 spell_Starfire;
    uint32 spell_Hibernate;
    uint32 spell_Gift_Of_The_Wild;
    uint32 spell_Mark_Of_The_Wild;
    uint32 spell_Moonfire;
    uint32 spell_Force_Of_Nature;
    uint32 spell_CurePoison;

    uint32 aura_Eclipse_Solar;
    uint32 aura_Eclipse_Lunar;

    ObjectGuid ogThornTarget;
};
#endif
