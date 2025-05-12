#include "Nier_Paladin.h"

Nier_Paladin::Nier_Paladin()
{
    spell_ConcentrationAura = 0;
    spell_FrostResistanceAura = 0;
    spell_RetributionAura = 0;
    spell_ShadowResistanceAura = 0;
    spell_FireResistanceAura = 0;
    spell_DevotionAura = 0;
    spell_BlessingOfWisdom = 0;
    spell_BlessingOfSalvation = 0;
    spell_BlessingOfMight = 0;
    spell_SealOfJustice = 0;
    spell_SealOfRighteousness = 0;
    spell_SealOfTheCrusader = 0;
    spell_Judgement = 0;
    spell_HammerOfJustice = 0;
    spell_Exorcism = 0;
    spell_LayOnHands = 0;
    spell_DivineIntervention = 0;
    spell_Consecration = 0;
    spell_Blessing_Of_Sanctuary = 0;
    spell_HolyShield = 0;
    spell_RighteousFury = 0;
    spell_Redemption = 0;

    blessingType = PaladinBlessingType::PaladinBlessingType_Might;
    auraType = PaladinAuraType::PaladinAuraType_Devotion;
    sealType = PaladinSealType::PaladinSealType_Righteousness;

    judgementDelay = 0;
    hammerOfJusticeDelay = 0;
    sealDelay = 0;
    exorcismDelay = 0;
    layOnHandsDelay = 0;
    interventionDelay = 0;
    consecrationDelay = 0;
    holyShieldDelay = 0;
}

bool Nier_Paladin::Attack(Unit* pTarget)
{
    if (!Nier_Base::Attack(pTarget))
    {
        return false;
    }

    return true;
}

bool Nier_Paladin::Tank(Unit* pTarget)
{
    if (!Nier_Base::Tank(pTarget))
    {
        return false;
    }

    return true;
}

bool Nier_Paladin::Heal(Unit* pTarget)
{
    if (!Nier_Base::Heal(pTarget))
    {
        return false;
    }

    return false;
}

bool Nier_Paladin::Cure(Unit* pTarget)
{
    if (!Nier_Base::Cure(pTarget))
    {
        return false;
    }

    return false;
}

bool Nier_Paladin::Buff(Unit* pTarget)
{
    if (!Nier_Base::Buff(pTarget))
    {
        return false;
    }

    return false;
}

bool Nier_Paladin::Revive(Unit* pTarget)
{
    if (!Nier_Base::Revive(pTarget))
    {
        return false;
    }

    return true;
}

bool Nier_Paladin::InitializeCharacter(uint32 pTargetLevel)
{
    if (!Nier_Base::InitializeCharacter(pTargetLevel))
    {
        return false;
    }

    return true;
}

bool Nier_Paladin::ResetTalentsAndSpells()
{
    if (!Nier_Base::ResetTalentsAndSpells())
    {
        return false;
    }

    return true;
}

void Nier_Paladin::EquipRandomItem(uint32 pEquipSlot)
{

}
