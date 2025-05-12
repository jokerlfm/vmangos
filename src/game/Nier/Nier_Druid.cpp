#include "Nier_Druid.h"

Nier_Druid::Nier_Druid()
{
    spell_InsectSwarm = 0;
    spell_MoonkinForm = 0;
    spell_Typhoon = 0;
    spell_Starfall = 0;
    spell_Wrath = 0;
    spell_Rebirth = 0;
    spell_Innervate = 0;
    spell_RemoveCurse = 0;
    spell_Thorns = 0;
    spell_FaerieFire = 0;
    spell_EntanglingRoots = 0;
    spell_Hurricane = 0;
    spell_Revive = 0;
    spell_Barkskin = 0;
    spell_Starfire = 0;
    spell_Hibernate = 0;
    spell_Gift_Of_The_Wild = 0;
    spell_Mark_Of_The_Wild = 0;
    spell_Moonfire = 0;
    spell_Force_Of_Nature = 0;
    spell_CurePoison = 0;

    aura_Eclipse_Solar = 0;
    aura_Eclipse_Lunar = 0;

    ogThornTarget = ObjectGuid();
}

bool Nier_Druid::Attack(Unit* pTarget)
{
    if (!Nier_Base::Attack(pTarget))
    {
        return false;
    }

    return true;
}

bool Nier_Druid::Tank(Unit* pTarget)
{
    if (!Nier_Base::Tank(pTarget))
    {
        return false;
    }

    return true;
}

bool Nier_Druid::Heal(Unit* pTarget)
{
    if (!Nier_Base::Heal(pTarget))
    {
        return false;
    }

    return false;
}

bool Nier_Druid::Cure(Unit* pTarget)
{
    if (!Nier_Base::Cure(pTarget))
    {
        return false;
    }

    return false;
}

bool Nier_Druid::Buff(Unit* pTarget)
{
    if (!Nier_Base::Buff(pTarget))
    {
        return false;
    }

    return false;
}

bool Nier_Druid::Revive(Unit* pTarget)
{
    if (!Nier_Base::Revive(pTarget))
    {
        return false;
    }

    return true;
}

bool Nier_Druid::InitializeCharacter(uint32 pTargetLevel)
{
    if (!Nier_Base::InitializeCharacter(pTargetLevel))
    {
        return false;
    }

    return true;
}

bool Nier_Druid::ResetTalentsAndSpells()
{
    if (!Nier_Base::ResetTalentsAndSpells())
    {
        return false;
    }

    return true;
}

void Nier_Druid::EquipRandomItem(uint32 pEquipSlot)
{

}
