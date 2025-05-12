#include "Nier_Warlock.h"

Nier_Warlock::Nier_Warlock()
{
    curseType = WarlockCurseType::WarlockCurseType_Weakness;
    curseDelay = 0;
    manaCheckDelay = 0;
    soulstoneDelay = 0;
    soulLinkDelay = 0;
    felArmorDelay = 0;
    wardDelay = 0;
    summonDelay = 0;
    soulHarvestDelay = 0;
    soulburnDelay = 0;
    soulFireDelay = 0;
    soulshatterDelay = 0;
    shadowfuryDelay = 0;
    conflagrateDelay = 0;
    immolateDelay = 0;
    shadowburnDelay = 0;
    chaosBoltDelay = 0;
    baneOfHavocDelay = 0;
    empoweredImpDelay = 0;
}

bool Nier_Warlock::Attack(Unit* pTarget)
{
    if (!Nier_Base::Attack(pTarget))
    {
        return false;
    }

    return true;
}

bool Nier_Warlock::Tank(Unit* pTarget)
{
    if (!Nier_Base::Tank(pTarget))
    {
        return false;
    }

    return true;
}

bool Nier_Warlock::Heal(Unit* pTarget)
{
    if (!Nier_Base::Heal(pTarget))
    {
        return false;
    }

    return false;
}

bool Nier_Warlock::Cure(Unit* pTarget)
{
    if (!Nier_Base::Cure(pTarget))
    {
        return false;
    }

    return false;
}

bool Nier_Warlock::Buff(Unit* pTarget)
{
    if (!Nier_Base::Buff(pTarget))
    {
        return false;
    }

    return false;
}

bool Nier_Warlock::Revive(Unit* pTarget)
{
    if (!Nier_Base::Revive(pTarget))
    {
        return false;
    }

    return true;
}

bool Nier_Warlock::InitializeCharacter(uint32 pTargetLevel)
{
    if (!Nier_Base::InitializeCharacter(pTargetLevel))
    {
        return false;
    }

    return true;
}

bool Nier_Warlock::ResetTalentsAndSpells()
{
    if (!Nier_Base::ResetTalentsAndSpells())
    {
        return false;
    }

    return true;
}

void Nier_Warlock::EquipRandomItem(uint32 pEquipSlot)
{

}
