#include "Nier_Rogue.h"

Nier_Rogue::Nier_Rogue()
{
    spell_Dismantle = 0;
    spell_Backstab = 0;
    spell_Eviscerate = 0;
    spell_FanofKnives = 0;
    spell_BladeFlurry = 0;
    spell_Sprint = 0;
    spell_TricksoftheTrade = 0;
    spell_Kick = 0;
    spell_Sap = 0;
    spell_Stealth = 0;
    spell_SliceandDice = 0;
    spell_Evasion = 0;
    spell_KidneyShot = 0;
    spell_CheapShot = 0;
    spell_Vanish = 0;
    spell_Feint = 0;
    spell_SinisterStrike = 0;
    spell_DeadlyThrow = 0;

    spell_AdrenalineRush = 0;
    spell_Riposte = 0;

    item_InstantPoison = 0;
    item_SlowPoison = 0;

    riposteDelay = 0;
}

bool Nier_Rogue::Attack(Unit* pTarget)
{
    if (!Nier_Base::Attack(pTarget))
    {
        return false;
    }

    return true;
}

bool Nier_Rogue::Tank(Unit* pTarget)
{
    if (!Nier_Base::Tank(pTarget))
    {
        return false;
    }

    return true;
}

bool Nier_Rogue::Heal(Unit* pTarget)
{
    if (!Nier_Base::Heal(pTarget))
    {
        return false;
    }

    return false;
}

bool Nier_Rogue::Follow(Unit* pTarget)
{
    if (!Nier_Base::Follow(pTarget))
    {
        return false;
    }

    return true;
}

bool Nier_Rogue::Cure(Unit* pTarget)
{
    if (!Nier_Base::Cure(pTarget))
    {
        return false;
    }

    return false;
}

bool Nier_Rogue::Buff(Unit* pTarget)
{
    if (!Nier_Base::Buff(pTarget))
    {
        return false;
    }

    return false;
}

bool Nier_Rogue::Revive(Unit* pTarget)
{
    if (!Nier_Base::Revive(pTarget))
    {
        return false;
    }

    return true;
}

bool Nier_Rogue::InitializeCharacter(uint32 pTargetLevel)
{
    if (!Nier_Base::InitializeCharacter(pTargetLevel))
    {
        return false;
    }

    return true;
}

bool Nier_Rogue::ResetTalentsAndSpells()
{
    if (!Nier_Base::ResetTalentsAndSpells())
    {
        return false;
    }

    return true;
}

bool Nier_Rogue::InitializeEquipments(bool pmReset)
{
    if (!Nier_Base::InitializeEquipments(pmReset))
    {
        return false;
    }

    return true;
}
