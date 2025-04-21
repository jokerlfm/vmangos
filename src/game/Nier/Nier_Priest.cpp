#include "Nier_Priest.h"

Nier_Priest::Nier_Priest()
{
    spell_Renew = 0;
    spell_LesserHeal = 0;
    spell_Heal = 0;
    spell_GreaterHeal = 0;
    spell_FlashHeal = 0;
    spell_Resurrection = 0;
    spell_CureDisease = 0;
    spell_DispelMagic = 0;
    spell_DivineSpirit = 0;
    spell_PowerWord_Fortitude = 0;
    spell_PowerWord_Shield = 0;
    spell_Penance = 0;
    spell_Weakened_Soul = 6788;
    spell_Prayer_of_Healing = 0;
    spell_Prayer_of_Spirit = 0;
    spell_Prayer_of_Fortitude = 0;
    spell_InnerFocus = 0;
    spell_PowerInfusion = 0;
    spell_PainSuppression = 0;
    spell_DesperatePrayer = 0;
    spell_HolyNova = 0;
    aura_Surge_of_Light = 0;
}

bool Nier_Priest::Attack(Unit* pTarget)
{
    if (!Nier_Base::Attack(pTarget))
    {
        return false;
    }

    return true;
}

bool Nier_Priest::Tank(Unit* pTarget)
{
    if (!Nier_Base::Tank(pTarget))
    {
        return false;
    }

    return true;
}

bool Nier_Priest::Heal(Unit* pTarget)
{
    if (!Nier_Base::Heal(pTarget))
    {
        return false;
    }

    return false;
}

bool Nier_Priest::Follow(Unit* pTarget)
{
    if (!Nier_Base::Follow(pTarget))
    {
        return false;
    }

    return true;
}

bool Nier_Priest::Cure(Unit* pTarget)
{
    if (!Nier_Base::Cure(pTarget))
    {
        return false;
    }

    return false;
}

bool Nier_Priest::Buff(Unit* pTarget)
{
    if (!Nier_Base::Buff(pTarget))
    {
        return false;
    }

    return false;
}

bool Nier_Priest::Revive(Unit* pTarget)
{
    if (!Nier_Base::Revive(pTarget))
    {
        return false;
    }

    return true;
}

bool Nier_Priest::InitializeCharacter(uint32 pTargetLevel)
{
    if (!Nier_Base::InitializeCharacter(pTargetLevel))
    {
        return false;
    }

    return true;
}

bool Nier_Priest::ResetTalentsAndSpells()
{
    if (!Nier_Base::ResetTalentsAndSpells())
    {
        return false;
    }

    return true;
}

bool Nier_Priest::InitializeEquipments(bool pmReset)
{
    if (!Nier_Base::InitializeEquipments(pmReset))
    {
        return false;
    }

    return true;
}
