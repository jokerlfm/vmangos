#include "Nier_Mage.h"
#include "World.h"

Nier_Mage::Nier_Mage() :Nier_Base()
{
    spell_IcyVeins = 0;
    spell_ColdSnap = 0;
    spell_DeepFreeze = 0;
    spell_ArcaneIntellect = 0;
    spell_ArcaneBrilliance = 0;
    spell_Blizzard = 0;
    spell_Polymorph = 0;
    spell_IceArmor = 0;
    spell_IceLance = 0;
    spell_FrostNova = 0;
    spell_Cone_Of_Cold = 0;
    spell_MageArmor = 0;
    spell_Frostbolt = 0;
    spell_IceBlock = 0;
    spell_Evocation = 0;
    spell_Fireball = 0;
    spell_RemoveCurse = 0;
    spell_MirrorImage = 0;
    spell_SummonWaterElemental = 0;
    spell_Blink = 0;
    spell_FrostfireBolt = 0;
    spell_ConjureManaGem = 0;
    aura_Frostbite = 0;
    aura_Fingers_Of_Frost = 0;
    aura_Fireball = 0;
    item_ManaGem = 0;
    spell_Portal_Exodar;
    spell_Portal_Dalaran = 0;
    spell_Portal_Orgrimmar = 0;
    spell_Portal_Stormwind = 0;
    spell_Portal_Darnassus = 0;
    spell_Portal_ThunderBluff = 0;
    spell_Portal_Shattrath_A = 0;
    spell_Portal_Shattrath_H = 0;
    spell_Portal_Ironforge = 0;
    spell_Portal_Silvermoon = 0;
    spell_Portal_Undercity = 0;
}

void Nier_Mage::InitializeCharacter(uint32 pTargetLevel)
{
    if (!me)
    {
        return;
    }
    specialty = 0;
    me->ClearInCombat();
    uint32 myLevel = me->GetLevel();
    if (myLevel != pTargetLevel)
    {
        me->GiveLevel(pTargetLevel);
        me->LearnDefaultSpells();
        me->LearnQuestRewardedSpells();

        ResetTalentsAndSpells();
        RemoveEquipments();
        myLevel = me->GetLevel();
    }
    spell_ArcaneIntellect = 1459;
    spell_Fireball = 133;
    aura_Frostbite = 12494;
    aura_Fingers_Of_Frost = 44544;
    aura_Fireball = 57761;

    if (myLevel >= 4)
    {
        spell_Frostbolt = 116;
    }
    if (myLevel >= 6)
    {
        spell_Fireball = 143;
    }
    if (myLevel >= 8)
    {
        spell_Polymorph = 118;
        spell_Frostbolt = 205;
    }
    if (myLevel >= 10)
    {
        spell_FrostNova = 122;
    }
    if (myLevel >= 12)
    {
        spell_Fireball = 145;
    }
    if (myLevel >= 14)
    {
        spell_ArcaneIntellect = 1460;
        spell_Frostbolt = 837;
    }
    if (myLevel >= 16)
    {

    }
    if (myLevel >= 18)
    {
        spell_RemoveCurse = 475;
        spell_Fireball = 3140;
    }
    if (myLevel >= 20)
    {
        spell_IcyVeins = 12472;
        spell_Blizzard = 10;
        spell_Polymorph = 12824;
        spell_Frostbolt = 7322;
        spell_Evocation = 12051;
        spell_Blink = 1953;
    }
    if (myLevel >= 24)
    {
        spell_Fireball = 8400;
    }
    if (myLevel >= 26)
    {
        spell_FrostNova = 865;
        spell_Cone_Of_Cold = 120;
        spell_Frostbolt = 8406;
    }
    if (myLevel >= 28)
    {
        spell_ArcaneIntellect = 1461;
        spell_Blizzard = 6141;
        spell_ConjureManaGem = 759;
        item_ManaGem = 5514;
    }
    if (myLevel >= 30)
    {
        spell_ColdSnap = 11958;
        spell_IceArmor = 7302;
        spell_IceBlock = 45438;
        spell_Fireball = 8401;
    }
    if (myLevel >= 32)
    {
        spell_Frostbolt = 8407;
    }
    if (myLevel >= 34)
    {
        spell_Cone_Of_Cold = 8492;
        spell_MageArmor = 6117;
    }
    if (myLevel >= 36)
    {
        spell_Blizzard = 8427;
        spell_Fireball = 8402;
    }
    if (myLevel >= 37)
    {

    }
    if (myLevel >= 38)
    {
        spell_Frostbolt = 8408;
        spell_ConjureManaGem = 3552;
        item_ManaGem = 5513;
    }
    if (myLevel >= 40)
    {
        spell_Polymorph = 12825;
        spell_IceArmor = 7320;
        spell_FrostNova = 6131;
        spell_Portal_Exodar = 32266;
        spell_Portal_Orgrimmar = 11417;
        spell_Portal_Stormwind = 10059;
        spell_Portal_Darnassus = 11419;
        spell_Portal_ThunderBluff = 11420;
        spell_Portal_Ironforge = 11416;
        spell_Portal_Silvermoon = 32267;
        spell_Portal_Undercity = 11418;
    }
    if (myLevel >= 41)
    {

    }
    if (myLevel >= 42)
    {
        spell_ArcaneIntellect = 10156;
        spell_Cone_Of_Cold = 10159;
        spell_Fireball = 10148;
    }
    if (myLevel >= 44)
    {
        spell_Blizzard = 10185;
        spell_Frostbolt = 10179;
    }
    if (myLevel >= 46)
    {
        spell_MageArmor = 22782;
    }
    if (myLevel >= 48)
    {
        spell_ConjureManaGem = 10053;
        item_ManaGem = 8007;
        spell_Fireball = 10149;
    }
    if (myLevel >= 50)
    {
        spell_IceArmor = 10219;
        spell_Cone_Of_Cold = 10160;
        spell_Frostbolt = 10180;
        spell_SummonWaterElemental = 31687;
    }
    if (myLevel >= 52)
    {
        spell_Blizzard = 10186;
    }
    if (myLevel >= 54)
    {
        spell_FrostNova = 10230;
        spell_Fireball = 10150;
    }
    if (myLevel >= 56)
    {
        spell_ArcaneIntellect = 10157;
        spell_ArcaneBrilliance = 23028;
        spell_Frostbolt = 10181;
    }
    if (myLevel >= 58)
    {
        spell_Cone_Of_Cold = 10161;
        spell_MageArmor = 22783;
        spell_ConjureManaGem = 10054;
        item_ManaGem = 8008;
    }
    if (myLevel >= 60)
    {
        spell_DeepFreeze = 44572;
        spell_Blizzard = 10187;
        spell_Polymorph = 12826;
        spell_IceArmor = 10220;
        spell_Frostbolt = 25304;
        spell_Fireball = 10151;
    }
    if (myLevel >= 61)
    {

    }
    if (myLevel >= 62)
    {
        spell_Fireball = 25306;
    }
    if (myLevel >= 63)
    {
        spell_Frostbolt = 27071;
    }
    if (myLevel >= 65)
    {
        spell_Cone_Of_Cold = 27087;
        spell_Portal_Shattrath_A = 33691;
        spell_Portal_Shattrath_H = 35717;
    }
    if (myLevel >= 66)
    {
        spell_IceLance = 30455;
        spell_Fireball = 27070;
    }
    if (myLevel >= 67)
    {
        spell_FrostNova = 27088;
    }
    if (myLevel >= 68)
    {
        spell_Blizzard = 27085;
        spell_ConjureManaGem = 27101;
        item_ManaGem = 22044;
    }
    if (myLevel >= 69)
    {
        spell_IceArmor = 27124;
        spell_MageArmor = 27125;
        spell_Frostbolt = 27072;
    }
    if (myLevel >= 70)
    {
        spell_ArcaneIntellect = 27126;
        spell_ArcaneBrilliance = 27127;
        spell_Frostbolt = 38697;
        spell_Fireball = 38692;
    }
    if (myLevel >= 71)
    {
        spell_MageArmor = 43023;
    }
    if (myLevel >= 72)
    {
        spell_IceLance = 42913;
        spell_Cone_Of_Cold = 42930;
    }
    if (myLevel >= 73)
    {

    }
    if (myLevel >= 74)
    {
        spell_Blizzard = 42939;
        spell_Fireball = 42832;
        spell_Portal_Dalaran = 53142;
    }
    if (myLevel >= 75)
    {
        spell_FrostNova = 42917;
        spell_Frostbolt = 42841;
        spell_FrostfireBolt = 44614;
    }
    if (myLevel >= 76)
    {

    }
    if (myLevel >= 77)
    {
        spell_ConjureManaGem = 42985;
        item_ManaGem = 33312;
    }
    if (myLevel >= 78)
    {
        spell_IceLance = 42914;
        spell_Fireball = 42833;
    }
    if (myLevel >= 79)
    {
        spell_IceArmor = 43008;
        spell_Cone_Of_Cold = 42931;
        spell_MageArmor = 43024;
        spell_Frostbolt = 42842;
    }
    if (myLevel >= 80)
    {
        spell_ArcaneIntellect = 42995;
        spell_ArcaneBrilliance = 43002;
        spell_Blizzard = 42940;
        spell_MirrorImage = 55342;
        spell_FrostfireBolt = 47610;
    }
    me->UpdateSkillsToMaxSkillsForLevel();
    std::ostringstream msgStream;
    msgStream << me->GetName() << " initialized";
    sWorld.SendServerMessage(ServerMessageType::SERVER_MSG_CUSTOM, msgStream.str().c_str());
}

void Nier_Mage::ResetTalentsAndSpells()
{
    if (!me)
    {
        return;
    }
    me->ResetTalents(true);

    // talent tab : 61 - frost 
    LearnTalent(37);
    LearnTalent(1649);
    LearnTalent(73, 2);
    LearnTalent(69);
    LearnTalent(73);
    LearnTalent(63);
    LearnTalent(66);
    LearnTalent(38);
    LearnTalent(72);
    LearnTalent(61);
    LearnTalent(1737);
    LearnTalent(68);
    LearnTalent(1738);
    LearnTalent(1740);
    LearnTalent(1853);
    LearnTalent(67, 1);
    LearnTalent(1741);
    LearnTalent(1855);
    LearnTalent(67, 2);
    LearnTalent(1856);
    LearnTalent(1857);
    LearnTalent(1854);
    LearnTalent(67);
    LearnTalent(65);
    LearnTalent(62);
    LearnTalent(741);

    // mage trainer Elsharin
    TrainSpells(5498);

    // portals
    TrainSpells(2485);
    TrainSpells(2489);
    TrainSpells(2492);
    TrainSpells(4165);
    TrainSpells(5957);
    TrainSpells(5958);
    TrainSpells(16654);
    TrainSpells(16755);
    TrainSpells(19340);
    TrainSpells(20791);
    TrainSpells(27703);
    TrainSpells(27705);
    TrainSpells(29156);
}

bool Nier_Mage::InitializeEquipments(bool pmReset)
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
        uint32 modType = ItemModType::ITEM_MOD_INTELLECT;
        uint32 equipItemClass = 0;
        uint32 equipItemSubClass = 0;
        if (checkEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_HEAD)
        {
            equipItemClass = 4;
            equipItemSubClass = 1;
        }
        else if (checkEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_SHOULDERS)
        {
            equipItemClass = 4;
            equipItemSubClass = 1;
        }
        else if (checkEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_WRISTS)
        {
            equipItemClass = 4;
            equipItemSubClass = 1;
        }
        else if (checkEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_WAIST)
        {
            equipItemClass = 4;
            equipItemSubClass = 1;
        }
        else if (checkEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_FEET)
        {
            equipItemClass = 4;
            equipItemSubClass = 1;
        }
        else if (checkEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_HANDS)
        {
            equipItemClass = 4;
            equipItemSubClass = 1;
        }
        else if (checkEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_CHEST)
        {
            equipItemClass = 4;
            equipItemSubClass = 1;
        }
        else if (checkEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_LEGS)
        {
            equipItemClass = 4;
            equipItemSubClass = 1;
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
            equipItemSubClass = 10;
        }
        else if (checkEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_RANGED)
        {
            equipItemClass = 2;
            equipItemSubClass = 19;
            inventoryTypeSet.insert(InventoryType::INVTYPE_RANGEDRIGHT);
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

void Nier_Mage::Prepare()
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

bool Nier_Mage::DPS(Unit* pmTarget, bool pmRushing, float pmDistanceMax, float pmDistanceMin, bool pmHolding, bool pmInstantOnly, bool pmChasing)
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
    float targetDistance = me->GetDistance(pmTarget);
    if (targetDistance > NIER_MAX_DISTANCE)
    {
        return true;
    }
    if (me->GetPowerPercent(Powers::POWER_MANA) < 30.0f)
    {
        //if (me->HasItemCount(item_ManaGem, 1))
        //{
        //	Item* pGem = GetItemInInventory(item_ManaGem);
        //	if (pGem && !pGem->IsInTrade())
        //	{
        //		if (UseItem(pGem, me))
        //		{
        //			return true;
        //		}
        //	}
        //}
        if (spell_Evocation > 0)
        {
            if (CastSpell(me, spell_ColdSnap))
            {
                return true;
            }
        }
        ManaPotion();
    }
    if (pmRushing)
    {
        if (spell_IcyVeins > 0)
        {
            if (!me->HasAura(spell_IcyVeins))
            {
                if (!me->HasSpellCooldown(spell_IcyVeins))
                {
                    CastSpell(me, spell_IcyVeins);
                }
                else
                {
                    if (spell_ColdSnap > 0)
                    {
                        CastSpell(me, spell_ColdSnap);
                    }
                }
            }
        }
        if (spell_MirrorImage > 0)
        {
            if (!me->HasSpellCooldown(spell_MirrorImage))
            {
                if (CastSpell(me, spell_MirrorImage))
                {
                    return true;
                }
            }
        }
        if (spell_SummonWaterElemental > 0)
        {
            if (!me->HasSpellCooldown(spell_SummonWaterElemental))
            {
                if (CastSpell(me, spell_SummonWaterElemental))
                {
                    return true;
                }
            }
        }
    }
    if (me->HasAura(aura_Fireball))
    {
        if (spell_FrostfireBolt > 0)
        {
            if (CastSpell(pmTarget, spell_FrostfireBolt))
            {
                return true;
            }
        }
        if (CastSpell(pmTarget, spell_Fireball))
        {
            return true;
        }
    }
    bool canFreeze = false;
    if (spell_FrostNova > 0)
    {
        if (pmTarget->HasAura(spell_FrostNova))
        {
            canFreeze = true;
        }
        else if (pmTarget->HasAura(aura_Frostbite))
        {
            canFreeze = true;
        }
        else if (me->HasAura(aura_Fingers_Of_Frost))
        {
            canFreeze = true;
        }
    }
    if (canFreeze)
    {
        if (spell_DeepFreeze > 0)
        {
            if (CastSpell(pmTarget, spell_DeepFreeze))
            {
                return true;
            }
        }
        if (spell_IceLance > 0)
        {
            if (CastSpell(pmTarget, spell_IceLance))
            {
                return true;
            }
        }
    }
    if (targetDistance < INTERACTION_DISTANCE)
    {
        if (spell_FrostNova > 0)
        {
            if (spell_IceBlock > 0)
            {
                if (pmTarget->GetTargetGuid() == me->GetObjectGuid())
                {
                    if (me->HasSpellCooldown(spell_FrostNova))
                    {
                        if (CastSpell(me, spell_IceBlock))
                        {
                            return true;
                        }
                    }
                }
            }
            if (CastSpell(me, spell_FrostNova))
            {
                return true;
            }
        }
    }
    if (targetDistance < NIER_NORMAL_DISTANCE)
    {
        if (spell_Cone_Of_Cold > 0)
        {
            if (CastSpell(me, spell_Cone_Of_Cold))
            {
                return true;
            }
        }
        if (spell_FrostNova > 0)
        {
            if (CastSpell(me, spell_FrostNova))
            {
                return true;
            }
        }
    }
    if (pmInstantOnly)
    {
        if (spell_IceLance > 0)
        {
            if (CastSpell(pmTarget, spell_IceLance))
            {
                return true;
            }
        }
    }
    else
    {
        if (spell_Frostbolt > 0)
        {
            if (CastSpell(pmTarget, spell_Frostbolt))
            {
                return true;
            }
        }
    }

    return true;
}

bool Nier_Mage::AOE(Unit* pmTarget, bool pmRushing, float pmDistanceMax, float pmDistanceMin, bool pmHolding, bool pmInstantOnly, bool pmChasing)
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
    float targetDistance = me->GetDistance(pmTarget);
    if (targetDistance > NIER_FAR_DISTANCE)
    {
        return true;
    }
    if (me->GetPowerPercent(Powers::POWER_MANA) < 30.0f)
    {
        ManaPotion();
    }
    if (!pmInstantOnly)
    {
        if (spell_Blizzard > 0)
        {
            if (CastSpell(pmTarget, spell_Blizzard))
            {
                return true;
            }
        }
    }

    return false;
}

bool Nier_Mage::Cure(Unit* pmTarget)
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
    else if (!pmTarget->IsAlive())
    {
        return false;
    }
    float targetDistance = me->GetDistance(pmTarget);
    if (targetDistance > NIER_MAX_DISTANCE)
    {
        return false;
    }

    std::multimap< uint32, SpellAuraHolder*> sahMap = pmTarget->GetSpellAuraHolderMap();
    for (std::multimap< uint32, SpellAuraHolder*>::iterator sahIT = sahMap.begin(); sahIT != sahMap.end(); sahIT++)
    {
        if (SpellAuraHolder* eachSAH = sahIT->second)
        {
            if (const SpellEntry* pS = eachSAH->GetSpellProto())
            {
                if (!pS->IsPositiveSpell())
                {
                    if (pS->Dispel == DispelType::DISPEL_CURSE)
                    {
                        if (CastSpell(pmTarget, spell_RemoveCurse))
                        {
                            return true;
                        }
                    }
                }
            }
        }
    }

    return false;
}

bool Nier_Mage::Buff(Unit* pmTarget)
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
    else if (!pmTarget->IsAlive())
    {
        return false;
    }
    if (me->GetObjectGuid() == pmTarget->GetObjectGuid())
    {
        if (spell_ConjureManaGem > 0)
        {
            if (!me->HasItemCount(item_ManaGem, 1))
            {
                CastSpell(me, spell_ConjureManaGem);
            }
        }
        if (spell_MageArmor > 0)
        {
            CastSpell(me, spell_MageArmor, true);
        }
    }
    float targetDistance = me->GetDistance(pmTarget);
    if (targetDistance > NIER_MAX_DISTANCE)
    {
        return false;
    }

    bool doBuff = true;
    if (spell_ArcaneBrilliance > 0 || spell_ArcaneIntellect > 0)
    {
        if (!pmTarget->HasAura(spell_ArcaneBrilliance) && !pmTarget->HasAura(spell_ArcaneIntellect))
        {
            if (spell_ArcaneBrilliance > 0)
            {
                if (CastSpell(pmTarget, spell_ArcaneBrilliance))
                {
                    return true;
                }
            }
            else if (spell_ArcaneIntellect > 0)
            {
                if (CastSpell(pmTarget, spell_ArcaneIntellect))
                {
                    return true;
                }
            }
        }
    }

    return false;
}

bool Nier_Mage::Mark(Unit* pmTarget, int pmRTI)
{
    if (pmRTI >= 0)
    {
        if (spell_Polymorph > 0)
        {
            if (me)
            {
                if (pmTarget)
                {
                    if (Group* myGroup = me->GetGroup())
                    {
                        if (myGroup->GetTargetIconByGuid(pmTarget->GetObjectGuid()) < 0)
                        {
                            if (Creature* targetC = (Creature*)pmTarget)
                            {
                                if (const CreatureInfo* ci = targetC->GetCreatureInfo())
                                {
                                    if (ci->type == CreatureType::CREATURE_TYPE_HUMANOID || ci->type == CreatureType::CREATURE_TYPE_BEAST)
                                    {
                                        if (const SpellEntry* pS = sSpellMgr.GetSpellEntry(spell_Polymorph))
                                        {
                                            if (!targetC->IsImmuneToSpell(pS, false))
                                            {
                                                if (me->IsValidAttackTarget(targetC))
                                                {
                                                    myGroup->SetTargetIcon(pmRTI, pmTarget->GetObjectGuid());
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
        }
    }

    return false;
}

bool Nier_Mage::Assist(int pmRTI)
{
    if (pmRTI >= 0)
    {
        if (spell_Polymorph > 0)
        {
            if (me)
            {
                if (me->IsAlive())
                {
                    if (Group* myGroup = me->GetGroup())
                    {
                        ObjectGuid ogRTI = myGroup->GetGuidByTargetIcon(pmRTI);
                        if (!ogRTI.IsEmpty())
                        {
                            if (Unit* rtiTarget = ObjectAccessor::GetUnit(*me, ogRTI))
                            {
                                bool canAssist = false;
                                if (Creature* targetC = (Creature*)rtiTarget)
                                {
                                    if (const CreatureInfo* ci = targetC->GetCreatureInfo())
                                    {
                                        if (ci->type == CreatureType::CREATURE_TYPE_HUMANOID || ci->type == CreatureType::CREATURE_TYPE_BEAST)
                                        {
                                            if (const SpellEntry* pS = sSpellMgr.GetSpellEntry(spell_Polymorph))
                                            {
                                                if (!targetC->IsImmuneToSpell(pS, false))
                                                {
                                                    if (me->IsValidAttackTarget(targetC))
                                                    {
                                                        canAssist = true;
                                                        if (me->GetDistance(targetC) < NIER_FAR_DISTANCE)
                                                        {
                                                            int duration = 0;
                                                            if (Aura* activeAura = targetC->GetAura(spell_Polymorph, SpellEffectIndex::EFFECT_INDEX_0))
                                                            {
                                                                duration = activeAura->GetAuraDuration();
                                                            }
                                                            if (duration < 2000)
                                                            {
                                                                if (CastSpell(rtiTarget, spell_Polymorph))
                                                                {
                                                                    return true;
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                                else
                                                {
                                                    me->Say("Target is immune to polymorph.", Language::LANG_UNIVERSAL);
                                                }
                                            }
                                        }
                                    }
                                }
                                if (!canAssist)
                                {
                                    myGroup->SetTargetIcon(pmRTI, ObjectGuid());
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    return false;
}

uint32 Nier_Mage::Caution()
{
    if (me)
    {
        if (me->IsAlive())
        {
            if (spell_Blink > 0)
            {
                if (CastSpell(me, spell_Blink))
                {
                    return 500;
                }
            }
            float startAngle = me->GetOrientation() + M_PI / 4;
            float angleGap = 0.0f;
            Position pos;
            while (angleGap < M_PI * 2)
            {
                me->GetNearPoint(me, pos.x, pos.y, pos.z, 0.0f, NIER_NORMAL_DISTANCE + MELEE_RANGE, startAngle + angleGap);
                if (me->GetDistance(pos.x, pos.y, pos.z) > NIER_NORMAL_DISTANCE - CONTACT_DISTANCE)
                {
                    me->InterruptNonMeleeSpells(false);
                    me->GetMotionMaster()->Clear();
                    me->GetMotionMaster()->MovePoint(0, pos.x, pos.y, pos.z);
                    return 2000;
                }
            }
        }
    }

    return 0;
}
