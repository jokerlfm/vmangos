#ifndef NIER_SHAMAN_H
#define NIER_SHAMAN_H

#include "Nier_Base.h"

enum ShamanEarthTotemType :uint32
{
    ShamanEarthTotemType_EarthbindTotem = 0,
    ShamanEarthTotemType_StoneskinTotem,
    ShamanEarthTotemType_StoneclawTotem,
    ShamanEarthTotemType_StrengthOfEarthTotem
};

class Nier_Base;

class Nier_Shaman :public Nier_Base
{
public:
    Nier_Shaman();
    bool Attack(Unit* pTarget);
    bool Tank(Unit* pTarget);
    bool Heal(Unit* pTarget);
    bool Cure(Unit* pTarget);
    bool Buff(Unit* pTarget);
    bool Revive(Unit* pTarget);
    bool InitializeCharacter(uint32 pTargetLevel);
    bool ResetTalentsAndSpells();
    void EquipRandomItem(uint32 pEquipSlot);

    uint32 earthTotemType;
};
#endif
