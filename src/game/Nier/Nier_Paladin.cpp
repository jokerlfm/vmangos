#include "Nier_Paladin.h"

Nier_Paladin::Nier_Paladin() :Nier_Base()
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

void Nier_Paladin::InitializeCharacter(uint32 pmTargetLevel, uint32 pmSpecialtyTabIndex)
{
    if (!me)
    {
        return;
    }
    specialty = pmSpecialtyTabIndex;
    me->ClearInCombat();
    uint32 myLevel = me->GetLevel();
    if (myLevel != pmTargetLevel)
    {
        me->GiveLevel(pmTargetLevel);
        me->LearnDefaultSpells();
        me->LearnQuestRewardedSpells();

        ResetTalent();
        RemoveEquipments();
        myLevel = me->GetLevel();
    }

    spell_DevotionAura = 465;
    spell_SealOfRighteousness = 21084;

    if (myLevel >= 4)
    {
        spell_BlessingOfMight = 19740;
        spell_Judgement = 20271;
    }
    if (myLevel >= 6)
    {
        spell_SealOfTheCrusader = 21082;
    }
    if (myLevel >= 8)
    {
        spell_HammerOfJustice = 853;
    }
    if (myLevel >= 10)
    {
        spell_DevotionAura = 10290;
        spell_SealOfRighteousness = 20287;
        spell_LayOnHands = 633;
    }
    if (myLevel >= 12)
    {
        spell_BlessingOfMight = 19834;
        spell_SealOfTheCrusader = 20162;
        spell_Redemption = 7328;
    }
    if (myLevel >= 14)
    {
        spell_BlessingOfWisdom = 19742;
    }
    if (myLevel >= 16)
    {
        spell_RetributionAura = 7294;
        spell_RighteousFury = 25780;
    }
    if (myLevel >= 18)
    {
        spell_SealOfRighteousness = 20288;
    }
    if (myLevel >= 20)
    {
        spell_DevotionAura = 643;
        spell_Exorcism = 879;
        spell_Consecration = 26573;
    }
    if (myLevel >= 22)
    {
        spell_ConcentrationAura = 19746;
        spell_BlessingOfMight = 19835;
        spell_SealOfJustice = 20164;
        spell_SealOfTheCrusader = 20305;
    }
    if (myLevel >= 24)
    {
        spell_BlessingOfWisdom = 19850;
        spell_HammerOfJustice = 5588;
    }
    if (myLevel >= 26)
    {
        spell_RetributionAura = 10298;
        spell_BlessingOfSalvation = 1038;
        spell_SealOfRighteousness = 20289;
    }
    if (myLevel >= 28)
    {
        spell_ShadowResistanceAura = 19876;
        spell_Exorcism = 5614;
    }
    if (myLevel >= 30)
    {
        spell_DevotionAura = 10291;
        spell_LayOnHands = 2800;
        spell_DivineIntervention = 19752;
        spell_Consecration = 20116;
    }
    if (myLevel >= 32)
    {
        spell_FrostResistanceAura = 19888;
        spell_BlessingOfMight = 19836;
        spell_SealOfTheCrusader = 20306;
    }
    if (myLevel >= 34)
    {
        spell_BlessingOfWisdom = 19852;
        spell_SealOfRighteousness = 20290;
    }
    if (myLevel >= 36)
    {
        spell_RetributionAura = 10299;
        spell_FireResistanceAura = 19891;
        spell_Exorcism = 5615;
    }
    if (myLevel >= 37)
    {

    }
    if (myLevel >= 38)
    {

    }
    if (myLevel >= 40)
    {
        spell_ShadowResistanceAura = 19895;
        spell_DevotionAura = 1032;
        spell_HammerOfJustice = 5589;
        spell_Consecration = 20922;
    }
    if (myLevel >= 41)
    {
        spell_Blessing_Of_Sanctuary = 20911;
        spell_Blessing_Of_Sanctuary = 20912;
    }
    if (myLevel >= 42)
    {
        spell_BlessingOfMight = 19837;
        spell_SealOfRighteousness = 20291;
        spell_SealOfTheCrusader = 20307;
    }
    if (myLevel >= 44)
    {
        spell_FrostResistanceAura = 19897;
        spell_BlessingOfWisdom = 19853;
        spell_Exorcism = 10312;
    }
    if (myLevel >= 46)
    {
        spell_RetributionAura = 10300;
    }
    if (myLevel >= 48)
    {
        spell_FireResistanceAura = 19899;
    }
    if (myLevel >= 50)
    {
        spell_DevotionAura = 10292;
        spell_SealOfRighteousness = 20292;
        spell_LayOnHands = 10310;
        spell_Consecration = 20923;
        spell_Blessing_Of_Sanctuary = 20913;
    }
    if (myLevel >= 51)
    {
        spell_DevotionAura = 10292;
        spell_SealOfRighteousness = 20292;
        spell_LayOnHands = 10310;
        spell_Consecration = 20923;
        spell_Blessing_Of_Sanctuary = 20913;
        spell_HolyShield = 20925;
        spell_HolyShield = 20927;
    }
    if (myLevel >= 52)
    {
        spell_ShadowResistanceAura = 19896;
        spell_BlessingOfMight = 19838;
        spell_SealOfTheCrusader = 20308;
        spell_Exorcism = 10313;
    }
    if (myLevel >= 54)
    {
        spell_BlessingOfWisdom = 19854;
        spell_HammerOfJustice = 10308;
    }
    if (myLevel >= 56)
    {
        spell_FrostResistanceAura = 19898;
        spell_RetributionAura = 10301;
    }
    if (myLevel >= 58)
    {
        spell_SealOfRighteousness = 20293;
    }
    if (myLevel >= 60)
    {
        spell_FireResistanceAura = 19900;
        spell_DevotionAura = 10293;
        spell_Exorcism = 10314;
        spell_Consecration = 20924;
        spell_Blessing_Of_Sanctuary = 20914;
        spell_HolyShield = 20928;
    }

    me->UpdateSkillsToMaxSkillsForLevel();
    std::ostringstream msgStream;
    msgStream << me->GetName() << " initialized";
    sWorld.SendServerMessage(ServerMessageType::SERVER_MSG_CUSTOM, msgStream.str().c_str());
}

void Nier_Paladin::ResetTalent()
{
    if (!me)
    {
        return;
    }
    me->ResetTalents(true);

    // talent tab : 381 - retribution, 382 - holy, 383 - protection 
    // DPS
    //LearnTalent(1450);
    //LearnTalent(1407);
    //LearnTalent(1631);
    //LearnTalent(1464);
    //LearnTalent(1411);
    //LearnTalent(1634);
    //LearnTalent(1405);
    //LearnTalent(1401);
    //LearnTalent(1410);
    //LearnTalent(1402);
    //LearnTalent(1463);
    //LearnTalent(1449);
    //LearnTalent(1446);

    //LearnTalent(1481);
    //LearnTalent(1409);

    // Tank 
    LearnTalent(1449);
    LearnTalent(1463);
    LearnTalent(1435);

    LearnTalent(1422);
    LearnTalent(1421);
    LearnTalent(1501);
    LearnTalent(1629);
    LearnTalent(1424, 2);
    LearnTalent(1431);
    LearnTalent(1424);
    LearnTalent(1423);
    LearnTalent(1630);
    LearnTalent(1430);

    LearnTalent(1443);

    LearnTalent(1425);
    LearnTalent(1429);

    // paladin trainer Lord Grayson Shadowbreaker
    TrainSpells(928);
}

bool Nier_Paladin::InitializeEquipments(bool pmReset)
{
    if (!me)
    {
        return true;
    }
    if (pmReset)
    {
        for (uint8 slot = INVENTORY_SLOT_ITEM_START; slot < INVENTORY_SLOT_ITEM_END; ++slot)
        {
            if (Item* inventoryItem = me->GetItemByPos(INVENTORY_SLOT_BAG_0, slot))
            {
                me->DestroyItem(INVENTORY_SLOT_BAG_0, slot, true);
            }
        }
        for (uint32 checkEquipSlot = EquipmentSlots::EQUIPMENT_SLOT_HEAD; checkEquipSlot < EquipmentSlots::EQUIPMENT_SLOT_TABARD; checkEquipSlot++)
        {
            if (Item* currentEquip = me->GetItemByPos(INVENTORY_SLOT_BAG_0, checkEquipSlot))
            {
                me->DestroyItem(INVENTORY_SLOT_BAG_0, checkEquipSlot, true);
            }
        }
    }
    uint32 myLevel = me->GetLevel();
    uint32 minQuality = ItemQualities::ITEM_QUALITY_UNCOMMON;
    if (myLevel < 20)
    {
        minQuality = ItemQualities::ITEM_QUALITY_POOR;
    }
    for (uint32 checkEquipSlot = EquipmentSlots::EQUIPMENT_SLOT_HEAD; checkEquipSlot < EquipmentSlots::EQUIPMENT_SLOT_TABARD; checkEquipSlot++)
    {
        if (checkEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_HEAD)
        {
            if (myLevel < 30)
            {
                continue;
            }
        }
        else if (checkEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_SHOULDERS)
        {
            if (myLevel < 30)
            {
                continue;
            }
        }
        else if (checkEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_NECK)
        {
            if (myLevel < 30)
            {
                continue;
            }
        }
        else if (checkEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_FINGER1 || checkEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_FINGER2)
        {
            if (myLevel < 30)
            {
                continue;
            }
        }
        std::unordered_set<uint32> inventoryTypeSet;
        uint32 modType = ItemModType::ITEM_MOD_AGILITY;
        uint32 equipItemClass = 0;
        uint32 equipItemSubClass = 0;
        if (checkEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_HEAD)
        {
            equipItemClass = 4;
            equipItemSubClass = 3;
            if (myLevel >= 40)
            {
                equipItemSubClass = 4;
            }
        }
        else if (checkEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_SHOULDERS)
        {
            equipItemClass = 4;
            equipItemSubClass = 3;
            if (myLevel >= 40)
            {
                equipItemSubClass = 4;
            }
        }
        else if (checkEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_WRISTS)
        {
            equipItemClass = 4;
            equipItemSubClass = 3;
            if (myLevel >= 40)
            {
                equipItemSubClass = 4;
            }
        }
        else if (checkEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_WAIST)
        {
            equipItemClass = 4;
            equipItemSubClass = 3;
            if (myLevel >= 40)
            {
                equipItemSubClass = 4;
            }
        }
        else if (checkEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_FEET)
        {
            equipItemClass = 4;
            equipItemSubClass = 3;
            if (myLevel >= 40)
            {
                equipItemSubClass = 4;
            }
        }
        else if (checkEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_HANDS)
        {
            equipItemClass = 4;
            equipItemSubClass = 3;
            if (myLevel >= 40)
            {
                equipItemSubClass = 4;
            }
        }
        else if (checkEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_CHEST)
        {
            equipItemClass = 4;
            equipItemSubClass = 3;
            if (myLevel >= 40)
            {
                equipItemSubClass = 4;
            }
        }
        else if (checkEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_LEGS)
        {
            equipItemClass = 4;
            equipItemSubClass = 3;
            if (myLevel >= 40)
            {
                equipItemSubClass = 4;
            }
        }
        else if (checkEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_BACK)
        {
            equipItemClass = 4;
            equipItemSubClass = 1;
        }
        else if (checkEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_NECK)
        {
            equipItemClass = 4;
            equipItemSubClass = 0;
        }
        else if (checkEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_FINGER1)
        {
            equipItemClass = 4;
            equipItemSubClass = 0;
        }
        else if (checkEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_FINGER2)
        {
            equipItemClass = 4;
            equipItemSubClass = 0;
        }
        else if (checkEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_MAINHAND)
        {
            equipItemClass = 2;
            equipItemSubClass = 4;
            inventoryTypeSet.insert(InventoryType::INVTYPE_WEAPON);
            inventoryTypeSet.insert(InventoryType::INVTYPE_WEAPONMAINHAND);
        }
        else if (checkEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_OFFHAND)
        {
            equipItemClass = 4;
            equipItemSubClass = 6;
            inventoryTypeSet.insert(InventoryType::INVTYPE_SHIELD);
        }
        else
        {
            continue;
        }
        if (Item* currentEquip = me->GetItemByPos(INVENTORY_SLOT_BAG_0, checkEquipSlot))
        {
            if (const ItemPrototype* checkIT = currentEquip->GetProto())
            {
                if (checkIT->Quality >= minQuality)
                {
                    continue;
                }
                else
                {
                    me->DestroyItem(INVENTORY_SLOT_BAG_0, checkEquipSlot, true);
                }
            }
        }
        EquipRandomItem(checkEquipSlot, equipItemClass, equipItemSubClass, minQuality, modType, inventoryTypeSet);
    }

    return true;
}

void Nier_Paladin::Prepare()
{
    Nier_Base::Prepare();
    if (!me)
    {
        return;
    }
    else if (!me->IsAlive())
    {
        return;
    }

    me->Say("Prepared", Language::LANG_UNIVERSAL);
}

void Nier_Paladin::Update(uint32 pmDiff)
{
    if (sealDelay > 0)
    {
        sealDelay -= pmDiff;
    }
    if (judgementDelay > 0)
    {
        judgementDelay -= pmDiff;
    }
    if (hammerOfJusticeDelay > 0)
    {
        hammerOfJusticeDelay -= pmDiff;
    }
    if (consecrationDelay > 0)
    {
        consecrationDelay -= pmDiff;
    }

    Nier_Base::Update(pmDiff);
}

bool Nier_Paladin::Tank(Unit* pmTarget, bool aoe)
{
    if (!me)
    {
        return false;
    }
    else if (!me->IsAlive())
    {
        return false;
    }
    if (me->IsNonMeleeSpellCasted(false, false, true))
    {
        return true;
    }
    if (!pmTarget)
    {
        return false;
    }
    else if (!pmTarget->IsAlive())
    {
        if (me->GetTargetGuid() == pmTarget->GetObjectGuid())
        {
            ClearTarget();
        }
        return false;
    }
    else if (!me->IsValidAttackTarget(pmTarget))
    {
        if (me->GetTargetGuid() == pmTarget->GetObjectGuid())
        {
            ClearTarget();
        }
        return false;
    }
    if (!nm->Tank(pmTarget))
    {
        if (me->GetTargetGuid() == pmTarget->GetObjectGuid())
        {
            ClearTarget();
        }
        return false;
    }
    ChooseTarget(pmTarget);
    me->Attack(pmTarget, true);
    float targetDistance = me->GetDistance(pmTarget);
    float myHealthPCT = me->GetHealthPercent();
    if (myHealthPCT < 20.0f)
    {
        if (spell_LayOnHands > 0)
        {
            if (CastSpell(me, spell_LayOnHands))
            {
                return true;
            }
        }
    }
    if (myHealthPCT < 10.0f)
    {
        if (spell_DivineIntervention > 0)
        {
            if (NierStrategy_Base* ns = me->nierStrategyMap[me->activeStrategyIndex])
            {
                if (Group* myGroup = me->GetGroup())
                {
                    for (GroupReference* groupRef = myGroup->GetFirstMember(); groupRef != nullptr; groupRef = groupRef->next())
                    {
                        if (Player* member = groupRef->getSource())
                        {
                            if (member->GetObjectGuid() == me->GetObjectGuid())
                            {
                                continue;
                            }
                            if (member->groupRole == GroupRole::GroupRole_Healer)
                            {
                                if (me->IsWithinDistInMap(member, NIER_FAR_DISTANCE))
                                {
                                    if (me->IsWithinLOSInMap(member))
                                    {
                                        if (CastSpell(member, spell_DivineIntervention))
                                        {
                                            return true;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    if (me->GetHealthPercent() < 30.0f)
    {
        HealthPotion();
    }
    if (aoe)
    {
        if (spell_Consecration > 0)
        {
            if (consecrationDelay <= 0)
            {
                if (targetDistance < NIER_NEAR_DISTANCE)
                {
                    if (CastSpell(pmTarget, spell_Consecration))
                    {
                        consecrationDelay = 8000;
                        return true;
                    }
                }
            }
        }
    }
    if (spell_Consecration > 0)
    {
        if (consecrationDelay <= 0)
        {
            if (targetDistance < NIER_NEAR_DISTANCE)
            {
                if (!pmTarget->GetTargetGuid().IsEmpty())
                {
                    if (pmTarget->GetTargetGuid() != me->GetObjectGuid())
                    {
                        if (CastSpell(pmTarget, spell_Consecration))
                        {
                            consecrationDelay = 8000;
                            return true;
                        }
                    }
                }
            }
        }
    }
    if (spell_SealOfRighteousness > 0)
    {
        if (!me->HasAura(spell_SealOfRighteousness))
        {
            if (CastSpell(me, spell_SealOfRighteousness))
            {
                sealDelay = 25000;
                return true;
            }
        }
        else if (sealDelay < 0)
        {
            if (CastSpell(me, spell_SealOfRighteousness))
            {
                sealDelay = 25000;
                return true;
            }
        }
    }

    if (exorcismDelay <= 0)
    {
        if (pmTarget->GetCreatureType() == CREATURE_TYPE_UNDEAD || pmTarget->GetCreatureType() == CreatureType::CREATURE_TYPE_DEMON)
        {
            if (targetDistance < NIER_NEAR_DISTANCE)
            {
                if (CastSpell(pmTarget, spell_Exorcism))
                {
                    exorcismDelay = 15000;
                    return true;
                }
            }
        }
    }

    bool canMelee = me->CanReachWithMeleeAutoAttack(pmTarget);
    if (canMelee)
    {
        if (spell_HammerOfJustice > 0)
        {
            if (hammerOfJusticeDelay <= 0)
            {
                if (pmTarget->IsNonMeleeSpellCasted(false, false, true))
                {
                    if (CastSpell(pmTarget, spell_HammerOfJustice))
                    {
                        hammerOfJusticeDelay = 60000;
                        return true;
                    }
                }
            }
        }
        if (spell_Judgement > 0)
        {
            if (judgementDelay <= 0)
            {
                if (CastSpell(pmTarget, spell_Judgement))
                {
                    judgementDelay = 8000;
                    return true;
                }
            }
        }
        if (spell_HolyShield > 0)
        {
            if (holyShieldDelay <= 0)
            {
                if (CastSpell(me, spell_HolyShield))
                {
                    holyShieldDelay = 8000;
                    return true;
                }
            }
        }
    }

    return true;
}

bool Nier_Paladin::Attack(Unit* pmTarget)
{
    if (!me)
    {
        return false;
    }
    else if (!me->IsAlive())
    {
        return false;
    }
    if (me->IsNonMeleeSpellCasted(false, false, true))
    {
        return true;
    }
    if (!pmTarget)
    {
        return false;
    }
    else if (!pmTarget->IsAlive())
    {
        if (me->GetTargetGuid() == pmTarget->GetObjectGuid())
        {
            ClearTarget();
        }
        return false;
    }
    else if (!me->IsValidAttackTarget(pmTarget))
    {
        if (me->GetTargetGuid() == pmTarget->GetObjectGuid())
        {
            ClearTarget();
        }
        return false;
    }
    else if (pmTarget->IsImmuneToDamage(SpellSchoolMask::SPELL_SCHOOL_MASK_NORMAL))
    {
        if (me->GetTargetGuid() == pmTarget->GetObjectGuid())
        {
            ClearTarget();
        }
        return false;
    }
    if (!pmTarget->CanSeeInWorld(me))
    {
        if (me->GetTargetGuid() == pmTarget->GetObjectGuid())
        {
            ClearTarget();
        }
        return false;
    }
    if (!nm->Chase(pmTarget, MELEE_RANGE, 0.5f))
    {
        if (me->GetTargetGuid() == pmTarget->GetObjectGuid())
        {
            ClearTarget();
        }
        return false;
    }
    ChooseTarget(pmTarget);
    me->Attack(pmTarget, true);
    float targetDistance = me->GetDistance(pmTarget);
    if (targetDistance < NIER_NORMAL_DISTANCE)
    {
        switch (sealType)
        {
        case PaladinSealType_Righteousness:
        {
            if (spell_SealOfRighteousness > 0)
            {
                if (!me->HasAura(spell_SealOfRighteousness))
                {
                    if (CastSpell(me, spell_SealOfRighteousness))
                    {
                        sealDelay = 25000;
                        return true;
                    }
                }
                else if (sealDelay < 0)
                {
                    if (CastSpell(me, spell_SealOfRighteousness))
                    {
                        sealDelay = 25000;
                        return true;
                    }
                }
            }
            break;
        }
        case PaladinSealType_Justice:
        {
            if (spell_SealOfJustice > 0)
            {
                if (!me->HasAura(spell_SealOfJustice))
                {
                    if (CastSpell(me, spell_SealOfJustice))
                    {
                        sealDelay = 25000;
                        return true;
                    }
                }
                else if (sealDelay < 0)
                {
                    if (CastSpell(me, spell_SealOfJustice))
                    {
                        sealDelay = 25000;
                        return true;
                    }
                }
            }
            break;
        }
        case PaladinSealType_Crusader:
        {
            if (spell_SealOfTheCrusader > 0)
            {
                if (!me->HasAura(spell_SealOfTheCrusader))
                {
                    if (CastSpell(me, spell_SealOfTheCrusader))
                    {
                        sealDelay = 25000;
                        return true;
                    }
                }
                else if (sealDelay < 0)
                {
                    if (CastSpell(me, spell_SealOfTheCrusader))
                    {
                        sealDelay = 25000;
                        return true;
                    }
                }
            }
            break;
        }
        default:
        {
            break;
        }
        }
    }
    bool canMelee = me->CanReachWithMeleeAutoAttack(pmTarget);
    if (canMelee)
    {
        if (me->GetHealthPercent() < 30.0f)
        {
            HealthPotion();
        }
        if (spell_HammerOfJustice > 0)
        {
            if (hammerOfJusticeDelay <= 0)
            {
                if (pmTarget->IsNonMeleeSpellCasted(false, false, true))
                {
                    if (CastSpell(pmTarget, spell_HammerOfJustice))
                    {
                        hammerOfJusticeDelay = 60000;
                        return true;
                    }
                }
            }
        }
        if (spell_Judgement > 0)
        {
            if (judgementDelay <= 0)
            {
                if (CastSpell(pmTarget, spell_Judgement))
                {
                    judgementDelay = 8000;
                    return true;
                }
            }
        }
        if (spell_Exorcism > 0)
        {
            if (exorcismDelay <= 0)
            {
                if (pmTarget->GetCreatureType() == CREATURE_TYPE_UNDEAD || pmTarget->GetCreatureType() == CreatureType::CREATURE_TYPE_DEMON)
                {
                    if (CastSpell(pmTarget, spell_Exorcism))
                    {
                        exorcismDelay = 15000;
                        return true;
                    }
                }
            }
        }
    }

    return true;
}

bool Nier_Paladin::Interrupt(Unit* pmTarget)
{
    if (me->CanReachWithMeleeAutoAttack(pmTarget))
    {
        if (hammerOfJusticeDelay <= 0)
        {
            if (CastSpell(pmTarget, spell_HammerOfJustice))
            {
                hammerOfJusticeDelay = 60000;
                return true;
            }
        }
    }
    return false;
}

bool Nier_Paladin::DPS(Unit* pmTarget, bool pmRushing, bool pmChasing, float pmDistanceMax, float pmDistanceMin)
{
    if (!me)
    {
        return false;
    }
    else if (!me->IsAlive())
    {
        return false;
    }
    if (me->IsNonMeleeSpellCasted(false, false, true))
    {
        return true;
    }
    if (!pmTarget)
    {
        return false;
    }
    else if (!pmTarget->IsAlive())
    {
        if (me->GetTargetGuid() == pmTarget->GetObjectGuid())
        {
            ClearTarget();
        }
        return false;
    }
    else if (!me->IsValidAttackTarget(pmTarget))
    {
        if (me->GetTargetGuid() == pmTarget->GetObjectGuid())
        {
            ClearTarget();
        }
        return false;
    }
    else if (pmTarget->IsImmuneToDamage(SpellSchoolMask::SPELL_SCHOOL_MASK_NORMAL))
    {
        if (me->GetTargetGuid() == pmTarget->GetObjectGuid())
        {
            ClearTarget();
        }
        return false;
    }
    if (!pmTarget->CanSeeInWorld(me))
    {
        if (me->GetTargetGuid() == pmTarget->GetObjectGuid())
        {
            ClearTarget();
        }
        return false;
    }
    if (pmChasing)
    {
        if (!nm->Chase(pmTarget, pmDistanceMax, pmDistanceMin))
        {
            if (me->GetTargetGuid() == pmTarget->GetObjectGuid())
            {
                ClearTarget();
            }
            return false;
        }
    }
    ChooseTarget(pmTarget);
    me->Attack(pmTarget, true);
    float targetDistance = me->GetDistance(pmTarget);
    if (targetDistance < NIER_NORMAL_DISTANCE)
    {
        switch (sealType)
        {
        case PaladinSealType_Righteousness:
        {
            if (spell_SealOfRighteousness > 0)
            {
                if (!me->HasAura(spell_SealOfRighteousness))
                {
                    if (CastSpell(me, spell_SealOfRighteousness))
                    {
                        sealDelay = 25000;
                        return true;
                    }
                }
                else if (sealDelay < 0)
                {
                    if (CastSpell(me, spell_SealOfRighteousness))
                    {
                        sealDelay = 25000;
                        return true;
                    }
                }
            }
            break;
        }
        case PaladinSealType_Justice:
        {
            if (spell_SealOfJustice > 0)
            {
                if (!me->HasAura(spell_SealOfJustice))
                {
                    if (CastSpell(me, spell_SealOfJustice))
                    {
                        sealDelay = 25000;
                        return true;
                    }
                }
                else if (sealDelay < 0)
                {
                    if (CastSpell(me, spell_SealOfJustice))
                    {
                        sealDelay = 25000;
                        return true;
                    }
                }
            }
            break;
        }
        case PaladinSealType_Crusader:
        {
            if (spell_SealOfTheCrusader > 0)
            {
                if (!me->HasAura(spell_SealOfTheCrusader))
                {
                    if (CastSpell(me, spell_SealOfTheCrusader))
                    {
                        sealDelay = 25000;
                        return true;
                    }
                }
                else if (sealDelay < 0)
                {
                    if (CastSpell(me, spell_SealOfTheCrusader))
                    {
                        sealDelay = 25000;
                        return true;
                    }
                }
            }
            break;
        }
        default:
        {
            break;
        }
        }
    }
    bool canMelee = me->CanReachWithMeleeAutoAttack(pmTarget);
    if (canMelee)
    {
        if (me->GetHealthPercent() < 30.0f)
        {
            HealthPotion();
        }
        if (spell_Judgement > 0)
        {
            if (judgementDelay <= 0)
            {
                if (CastSpell(pmTarget, spell_Judgement))
                {
                    judgementDelay = 8000;
                    return true;
                }
            }
        }
        if (spell_Exorcism > 0)
        {
            if (exorcismDelay <= 0)
            {
                if (pmTarget->GetCreatureType() == CREATURE_TYPE_UNDEAD || pmTarget->GetCreatureType() == CreatureType::CREATURE_TYPE_DEMON)
                {
                    if (CastSpell(pmTarget, spell_Exorcism))
                    {
                        exorcismDelay = 15000;
                        return true;
                    }
                }
            }
        }
    }

    return true;
}

bool Nier_Paladin::Buff(Unit* pmTarget)
{
    if (!me)
    {
        return false;
    }
    else if (!me->IsAlive())
    {
        return false;
    }
    if (!pmTarget)
    {
        return false;
    }

    if (me->GetObjectGuid() == pmTarget->GetObjectGuid())
    {
        if (spell_SealOfRighteousness > 0)
        {
            if (!me->HasAura(spell_SealOfRighteousness))
            {
                if (CastSpell(me, spell_SealOfRighteousness))
                {
                    sealDelay = 25000;
                    return true;
                }
            }
            else if (sealDelay < 0)
            {
                if (CastSpell(me, spell_SealOfRighteousness))
                {
                    sealDelay = 25000;
                    return true;
                }
            }
        }
        if (me->groupRole == GroupRole::GroupRole_Tank)
        {
            if (spell_RighteousFury > 0)
            {
                if (!me->HasAura(spell_RighteousFury))
                {
                    if (CastSpell(me, spell_RighteousFury))
                    {
                        return true;
                    }
                }
            }
            if (spell_DevotionAura > 0)
            {
                if (!me->HasAura(spell_DevotionAura))
                {
                    if (CastSpell(me, spell_DevotionAura))
                    {
                        return true;
                    }
                }
            }
        }
        else
        {
            switch (auraType)
            {
            case PaladinAuraType_Concentration:
            {
                if (spell_ConcentrationAura > 0)
                {
                    if (!me->HasAura(spell_ConcentrationAura))
                    {
                        if (CastSpell(me, spell_ConcentrationAura))
                        {
                            return true;
                        }
                    }
                }
                break;
            }
            case PaladinAuraType_Devotion:
            {
                if (spell_DevotionAura > 0)
                {
                    if (!me->HasAura(spell_DevotionAura))
                    {
                        if (CastSpell(me, spell_DevotionAura))
                        {
                            return true;
                        }
                    }
                }
                break;
            }
            case PaladinAuraType_Retribution:
            {
                if (spell_RetributionAura > 0)
                {
                    if (!me->HasAura(spell_RetributionAura))
                    {
                        if (CastSpell(me, spell_RetributionAura))
                        {
                            return true;
                        }
                    }
                }
                break;
            }
            case PaladinAuraType_FireResistant:
            {
                if (spell_FireResistanceAura > 0)
                {
                    if (!me->HasAura(spell_FireResistanceAura))
                    {
                        if (CastSpell(me, spell_FireResistanceAura))
                        {
                            return true;
                        }
                    }
                }
                break;
            }
            case PaladinAuraType_FrostResistant:
            {
                if (spell_FrostResistanceAura > 0)
                {
                    if (!me->HasAura(spell_FrostResistanceAura))
                    {
                        if (CastSpell(me, spell_FrostResistanceAura))
                        {
                            return true;
                        }
                    }
                }
                break;
            }
            case PaladinAuraType_ShadowResistant:
            {
                if (spell_ShadowResistanceAura > 0)
                {
                    if (!me->HasAura(spell_ShadowResistanceAura))
                    {
                        if (CastSpell(me, spell_ShadowResistanceAura))
                        {
                            return true;
                        }
                    }
                }
                break;
            }
            default:
            {
                break;
            }
            }
        }
    }

    if (me->IsInRange(pmTarget, 0.0f, NIER_FAR_DISTANCE))
    {
        if (me->IsWithinLOSInMap(pmTarget))
        {
            if (spell_BlessingOfSalvation > 0)
            {
                if (Player* targetPlayer = pmTarget->ToPlayer())
                {
                    if (targetPlayer->groupRole == GroupRole::GroupRole_DPS)
                    {
                        if (!targetPlayer->HasAura(spell_BlessingOfSalvation))
                        {
                            if (CastSpell(targetPlayer, spell_BlessingOfSalvation))
                            {
                                return true;
                            }
                        }
                    }
                }
            }
            if (spell_BlessingOfWisdom > 0)
            {
                if (Player* targetPlayer = pmTarget->ToPlayer())
                {
                    if (targetPlayer->groupRole == GroupRole::GroupRole_Healer)
                    {
                        if (!targetPlayer->HasAura(spell_BlessingOfWisdom))
                        {
                            if (CastSpell(targetPlayer, spell_BlessingOfWisdom))
                            {
                                return true;
                            }
                        }
                    }
                }
            }
            if (Player* targetPlayer = pmTarget->ToPlayer())
            {
                if (targetPlayer->groupRole == GroupRole::GroupRole_Tank)
                {
                    if (spell_Blessing_Of_Sanctuary > 0)
                    {
                        if (!me->HasAura(spell_Blessing_Of_Sanctuary))
                        {
                            if (CastSpell(me, spell_Blessing_Of_Sanctuary))
                            {
                                return true;
                            }
                        }
                    }
                    else if (spell_BlessingOfMight > 0)
                    {
                        if (!targetPlayer->HasAura(spell_BlessingOfMight))
                        {
                            if (CastSpell(targetPlayer, spell_BlessingOfMight))
                            {
                                return true;
                            }
                        }
                    }
                }
            }
        }
    }

    return false;
}

uint32 Nier_Paladin::Caution()
{
    uint32 result = Nier_Base::Caution();

    return result;
}

bool Nier_Paladin::Revive(Player* pmTarget)
{
    if (!me)
    {
        return false;
    }
    else if (!me->IsAlive())
    {
        return false;
    }
    if (!pmTarget)
    {
        return false;
    }
    else if (pmTarget->IsAlive())
    {
        return false;
    }
    float targetDistance = me->GetDistance(pmTarget);
    if (targetDistance > NIER_MAX_DISTANCE)
    {
        return false;
    }

    if (spell_Redemption > 0)
    {
        if (CastSpell(pmTarget, spell_Redemption))
        {
            return true;
        }
    }

    return false;
}
