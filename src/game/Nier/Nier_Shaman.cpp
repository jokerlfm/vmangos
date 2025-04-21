#include "Nier_Shaman.h"

Nier_Shaman::Nier_Shaman()
{
    earthTotemType = ShamanEarthTotemType::ShamanEarthTotemType_StoneskinTotem;
}

bool Nier_Shaman::Attack(Unit* pTarget)
{
    if (!Nier_Base::Attack(pTarget))
    {
        return false;
    }

    return true;
}

bool Nier_Shaman::Tank(Unit* pTarget)
{
    if (!Nier_Base::Tank(pTarget))
    {
        return false;
    }

    return true;
}

bool Nier_Shaman::Heal(Unit* pTarget)
{
    if (!Nier_Base::Heal(pTarget))
    {
        return false;
    }

    return false;
}

bool Nier_Shaman::Follow(Unit* pTarget)
{
    if (!Nier_Base::Follow(pTarget))
    {
        return false;
    }

    return true;
}

bool Nier_Shaman::Cure(Unit* pTarget)
{
    if (!Nier_Base::Cure(pTarget))
    {
        return false;
    }

    return false;
}

bool Nier_Shaman::Buff(Unit* pTarget)
{
    if (!Nier_Base::Buff(pTarget))
    {
        return false;
    }

    return false;
}

bool Nier_Shaman::Revive(Unit* pTarget)
{
    if (!Nier_Base::Revive(pTarget))
    {
        return false;
    }

    return true;
}

bool Nier_Shaman::InitializeCharacter(uint32 pTargetLevel)
{
    if (!Nier_Base::InitializeCharacter(pTargetLevel))
    {
        return false;
    }

    return true;
}

bool Nier_Shaman::ResetTalentsAndSpells()
{
    if (!Nier_Base::ResetTalentsAndSpells())
    {
        return false;
    }

    return true;
}

bool Nier_Shaman::InitializeEquipments(bool pmReset)
{
    if (!Nier_Base::InitializeEquipments(pmReset))
    {
        return false;
    }

    return true;
}
