#include "Nier_Mage.h"

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
    spell_Portal_Exodar = 0;
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

bool Nier_Mage::Attack(Unit* pTarget)
{
    if (!Nier_Base::Attack(pTarget))
    {
        return false;
    }

    float targetDistance = me->GetDistance(pTarget);
    if (targetDistance > VISIBILITY_DISTANCE_NORMAL)
    {
        return false;
    }

    ChooseTarget(pTarget);
    if (Chase(pTarget, VISIBILITY_DISTANCE_TINY))
    {
        if (spell_Frostbolt > 0)
        {
            if (CastSpell(pTarget, spell_Frostbolt))
            {
                return true;
            }
        }
    }

    return true;
}

bool Nier_Mage::Tank(Unit* pTarget)
{
    if (!Nier_Base::Tank(pTarget))
    {
        return false;
    }

    return true;
}

bool Nier_Mage::Heal(Unit* pTarget)
{
    if (!Nier_Base::Heal(pTarget))
    {
        return false;
    }

    return false;
}

bool Nier_Mage::Cure(Unit* pTarget)
{
    if (!Nier_Base::Cure(pTarget))
    {
        return false;
    }

    return false;
}

bool Nier_Mage::Buff(Unit* pTarget)
{
    if (!Nier_Base::Buff(pTarget))
    {
        return false;
    }

    float targetDistance = me->GetDistance(pTarget);
    if (targetDistance > VISIBILITY_DISTANCE_TINY)
    {
        return false;
    }

    bool doBuff = true;
    if (spell_ArcaneBrilliance > 0 || spell_ArcaneIntellect > 0)
    {
        if (!pTarget->HasAura(spell_ArcaneBrilliance) && !pTarget->HasAura(spell_ArcaneIntellect))
        {
            if (spell_ArcaneBrilliance > 0)
            {
                if (CastSpell(pTarget, spell_ArcaneBrilliance))
                {
                    return true;
                }
            }
            else if (spell_ArcaneIntellect > 0)
            {
                if (CastSpell(pTarget, spell_ArcaneIntellect))
                {
                    return true;
                }
            }
        }
    }

    return false;
}

bool Nier_Mage::Revive(Unit* pTarget)
{
    if (!Nier_Base::Revive(pTarget))
    {
        return false;
    }

    return true;
}

bool Nier_Mage::InitializeCharacter(uint32 pTargetLevel)
{
    if (!Nier_Base::InitializeCharacter(pTargetLevel))
    {
        return false;
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

    return true;
}

bool Nier_Mage::ResetTalentsAndSpells()
{
    if (!Nier_Base::ResetTalentsAndSpells())
    {
        return false;
    }

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

    return true;
}

void Nier_Mage::EquipRandomItem(uint32 pEquipSlot)
{
    uint32 itemClass = 0;
    uint32 itemSubclass = 0;
    uint32 inventoryType = 0;
    if (pEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_HEAD)
    {
        itemClass = 4;
        itemSubclass = 1;
        inventoryType = 1;
    }
    else if (pEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_SHOULDERS)
    {
        itemClass = 4;
        itemSubclass = 1;
        inventoryType = 3;
    }
    else if (pEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_WRISTS)
    {
        itemClass = 4;
        itemSubclass = 1;
        inventoryType = 9;
    }
    else if (pEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_WAIST)
    {
        itemClass = 4;
        itemSubclass = 1;
        inventoryType = 6;
    }
    else if (pEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_FEET)
    {
        itemClass = 4;
        itemSubclass = 1;
        inventoryType = 8;
    }
    else if (pEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_HANDS)
    {
        itemClass = 4;
        itemSubclass = 1;
        inventoryType = 10;
    }
    else if (pEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_CHEST)
    {
        itemClass = 4;
        itemSubclass = 1;
        inventoryType = 5;
    }
    else if (pEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_LEGS)
    {
        itemClass = 4;
        itemSubclass = 1;
        inventoryType = 7;
    }
    else if (pEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_BACK)
    {
        itemClass = 4;
        itemSubclass = 1;
        inventoryType = 16;
    }
    else if (pEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_NECK)
    {
        itemClass = 4;
        itemSubclass = 0;
        inventoryType = 2;
    }
    else if (pEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_FINGER1)
    {
        itemClass = 4;
        itemSubclass = 0;
        inventoryType = 11;
    }
    else if (pEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_FINGER2)
    {
        itemClass = 4;
        itemSubclass = 0;
        inventoryType = 11;
    }
    else if (pEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_MAINHAND)
    {
        itemClass = 2;
        itemSubclass = 10;
        inventoryType = InventoryType::INVTYPE_2HWEAPON;
    }
    else if (pEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_OFFHAND)
    {
        inventoryType = 0;
    }
    else if (pEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_RANGED)
    {
        itemClass = 2;
        itemSubclass = 19;
        inventoryType = InventoryType::INVTYPE_RANGEDRIGHT;
    }
    else
    {
        return;
    }
    if (inventoryType == 0)
    {
        return;
    }
    int maxReqLevel = me->GetLevel();
    int minReqLevel = maxReqLevel - 10;
    if (minReqLevel < 0)
    {
        minReqLevel = 0;
    }

    if (Item* currentEquip = me->GetItemByPos(INVENTORY_SLOT_BAG_0, pEquipSlot))
    {
        if (currentEquip->GetProto()->RequiredLevel < minReqLevel)
        {
            me->DestroyItem(INVENTORY_SLOT_BAG_0, pEquipSlot, true);
        }
    }

    EquipOne(pEquipSlot, itemClass, itemSubclass, inventoryType, minReqLevel, maxReqLevel);
}
