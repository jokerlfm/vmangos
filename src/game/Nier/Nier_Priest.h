#ifndef NIER_PRIEST_H
#define NIER_PRIEST_H

#include "Nier_Base.h"

class Nier_Base;

class Nier_Priest :public Nier_Base
{
public:
    Nier_Priest();
    bool Attack(Unit* pTarget);
    bool Tank(Unit* pTarget);
    bool Heal(Unit* pTarget);
    bool Cure(Unit* pTarget);
    bool Buff(Unit* pTarget);
    bool Revive(Unit* pTarget);
    bool InitializeCharacter(uint32 pTargetLevel);
    bool ResetTalentsAndSpells();
    void EquipRandomItem(uint32 pEquipSlot);

private:
    uint32 spell_Shoot;
    uint32 spell_Smite;

    uint32 spell_Renew;
    uint32 spell_LesserHeal;
    uint32 spell_Heal;
    uint32 spell_GreaterHeal;
    uint32 spell_FlashHeal;
    uint32 spell_Resurrection;
    uint32 spell_CureDisease;
    uint32 spell_DispelMagic;
    uint32 spell_DivineSpirit;
    uint32 spell_PowerWord_Fortitude;
    uint32 spell_PowerWord_Shield;
    uint32 spell_Penance;
    uint32 spell_Weakened_Soul;
    uint32 spell_Prayer_of_Healing;
    uint32 spell_Prayer_of_Spirit;
    uint32 spell_Prayer_of_Fortitude;
    uint32 spell_InnerFocus;
    uint32 spell_PowerInfusion;
    uint32 spell_PainSuppression;
    uint32 spell_DesperatePrayer;
    uint32 spell_HolyNova;
    uint32 aura_Surge_of_Light;
};
#endif
