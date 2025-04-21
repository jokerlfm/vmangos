#include "Nier_Warrior.h"

Nier_Warrior::Nier_Warrior()
{
    specialty = 0;

    spell_SunderArmor = 0;
    spell_DefensiveStance = 0;
    spell_Taunt = 0;
    spell_MockingBlow = 0;
    spell_PiercingHowl = 0;
    spell_DemoralizingShout = 0;
    spell_ShieldBash = 0;
    spell_ShieldBlock = 0;
    spell_ShieldSlam = 0;
    spell_ShieldWall = 0;
    spell_Revenge = 0;
    spell_Devastate = 0;
    spell_Disarm = 0;
    spell_Vigilance = 0;
    spell_BerserkerRage = 0;
    spell_ThunderClap = 0;
    spell_LastStand = 0;
    spell_SunderArmor = 0;
    spell_Bloodthirst = 0;
    spell_Cleave = 0;
    spell_Rend = 0;
    spell_Bloodrage = 0;
    spell_HeroicStrike = 0;
    spell_HeroicThrow = 0;
    spell_intercept = 0;
    spell_Intervene = 0;
    spell_BattleShout = 0;
    spell_Shockwave = 0;
    spell_ConcussionBlow = 0;
    spell_ChallengingShout = 0;
    spell_Warbringer = 0;
    spell_Charge = 0;

    spellDelay_DemoralizingShout = DEFAULT_WARRIOR_SPELL_DELAY;
    spellDelay_BattleShout = DEFAULT_WARRIOR_SPELL_DELAY;
    spellDelay_Revenge = 0;
}

bool Nier_Warrior::Attack(Unit* pTarget)
{
    if (!Nier_Base::Attack(pTarget))
    {
        return false;
    }

    return true;
}

bool Nier_Warrior::Tank(Unit* pTarget)
{
    if (!Nier_Base::Tank(pTarget))
    {
        return false;
    }

    return true;
}

bool Nier_Warrior::Heal(Unit* pTarget)
{
    if (!Nier_Base::Heal(pTarget))
    {
        return false;
    }

    return false;
}

bool Nier_Warrior::Follow(Unit* pTarget)
{
    if (!Nier_Base::Follow(pTarget))
    {
        return false;
    }

    return true;
}

bool Nier_Warrior::Cure(Unit* pTarget)
{
    if (!Nier_Base::Cure(pTarget))
    {
        return false;
    }

    return false;
}

bool Nier_Warrior::Buff(Unit* pTarget)
{
    if (!Nier_Base::Buff(pTarget))
    {
        return false;
    }

    return false;
}

bool Nier_Warrior::Revive(Unit* pTarget)
{
    if (!Nier_Base::Revive(pTarget))
    {
        return false;
    }

    return true;
}

bool Nier_Warrior::InitializeCharacter(uint32 pTargetLevel)
{
    if (!Nier_Base::InitializeCharacter(pTargetLevel))
    {
        return false;
    }

    return true;
}

bool Nier_Warrior::ResetTalentsAndSpells()
{
    if (!Nier_Base::ResetTalentsAndSpells())
    {
        return false;
    }

    return true;
}

bool Nier_Warrior::InitializeEquipments(bool pmReset)
{
    if (!Nier_Base::InitializeEquipments(pmReset))
    {
        return false;
    }

    return true;
}
