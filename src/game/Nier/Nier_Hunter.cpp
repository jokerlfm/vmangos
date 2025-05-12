#include "Nier_Hunter.h"
#include "Pet.h"

Nier_Hunter::Nier_Hunter()
{
    specialty = 0;

    aspectType = HunterAspectType::HunterAspectType_Hawk;

    spell_ArcaneShot = 0;
    spell_SerpentSting = 0;
    spell_RapidFire = 0;
    spell_HuntersMark = 0;
    spell_Volley = 0;
    spell_AspectOfTheHawk = 0;
    spell_CallPet = 0;
    spell_DismissPet = 0;
    spell_RevivePet = 0;
    spell_ConcussiveShot = 0;
    spell_AutoShot = 0;

    spell_TrueshotAura = 0;

    ammoEntry = 0;
}

bool Nier_Hunter::Attack(Unit* pTarget)
{
    if (!Nier_Base::Attack(pTarget))
    {
        return false;
    }

    return true;
}

bool Nier_Hunter::Tank(Unit* pTarget)
{
    if (!Nier_Base::Tank(pTarget))
    {
        return false;
    }

    return true;
}

bool Nier_Hunter::Heal(Unit* pTarget)
{
    if (!Nier_Base::Heal(pTarget))
    {
        return false;
    }

    return false;
}

bool Nier_Hunter::Cure(Unit* pTarget)
{
    if (!Nier_Base::Cure(pTarget))
    {
        return false;
    }

    return false;
}

bool Nier_Hunter::Buff(Unit* pTarget)
{
    if (!Nier_Base::Buff(pTarget))
    {
        return false;
    }

    return false;
}

bool Nier_Hunter::Revive(Unit* pTarget)
{
    if (!Nier_Base::Revive(pTarget))
    {
        return false;
    }

    return true;
}

bool Nier_Hunter::InitializeCharacter(uint32 pTargetLevel)
{
    if (!Nier_Base::InitializeCharacter(pTargetLevel))
    {
        return false;
    }

    return true;
}

bool Nier_Hunter::ResetTalentsAndSpells()
{
    if (!Nier_Base::ResetTalentsAndSpells())
    {
        return false;
    }

    return true;
}

void Nier_Hunter::EquipRandomItem(uint32 pEquipSlot)
{

}
