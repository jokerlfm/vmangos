#ifndef NIER_WARLOCK_H
#define NIER_WARLOCK_H

#include "Nier_Base.h"

enum WarlockCurseType :uint32
{
    WarlockCurseType_None = 0,
    WarlockCurseType_Element = 1,
    WarlockCurseType_Weakness = 2,
    WarlockCurseType_Tongues = 3,
};

class Nier_Base;

class Nier_Warlock :public Nier_Base
{
public:
    Nier_Warlock();
    bool Attack(Unit* pTarget);
    bool Tank(Unit* pTarget);
    bool Heal(Unit* pTarget);
    bool Cure(Unit* pTarget);
    bool Buff(Unit* pTarget);
    bool Revive(Unit* pTarget);
    bool InitializeCharacter(uint32 pTargetLevel);
    bool ResetTalentsAndSpells();
    void EquipRandomItem(uint32 pEquipSlot);

    uint32 curseType;
    int curseDelay;
    int manaCheckDelay;
    int soulstoneDelay;
    int soulLinkDelay;
    int felArmorDelay;
    int wardDelay;
    int summonDelay;
    int soulHarvestDelay;
    int soulburnDelay;
    int soulFireDelay;
    int soulshatterDelay;
    int shadowfuryDelay;
    int conflagrateDelay;
    int immolateDelay;
    int shadowburnDelay;
    int chaosBoltDelay;
    int baneOfHavocDelay;
    int empoweredImpDelay;
};
#endif
