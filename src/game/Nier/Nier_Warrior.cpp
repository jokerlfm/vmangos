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

    spellDelay_DemoralizingShout = 0;
    spellDelay_BattleShout = 0;
    spellDelay_Revenge = 0;
}

bool Nier_Warrior::Attack(Unit* pTarget)
{
    if (!Nier_Base::Attack(pTarget))
    {
        return false;
    }

    if (me->IsNonMeleeSpellCasted(false, false, true))
    {
        return true;
    }
    ChooseTarget(pTarget);
    me->Attack(pTarget, true);
    if (Chase(pTarget))
    {
        if (me->GetHealthPercent() < 20.0f)
        {
            if (spell_ShieldWall > 0)
            {
                if (CastSpell(me, spell_ShieldWall))
                {
                    return true;
                }
            }
            if (spell_LastStand > 0)
            {
                if (CastSpell(me, spell_LastStand))
                {
                    return true;
                }
            }
        }
        if (spell_Bloodrage > 0)
        {
            if (CastSpell(me, spell_Bloodrage))
            {
                return true;
            }
        }
        uint32 myRage = me->GetPower(Powers::POWER_RAGE);
        if (myRage > 100)
        {
            if (pTarget->IsNonMeleeSpellCasted(false, false, true))
            {
                if (spell_ShieldBash > 0)
                {
                    if (CastSpell(pTarget, spell_ShieldBash))
                    {
                        return true;
                    }
                }
            }
            if (spell_DemoralizingShout > 0)
            {
                if (CastSpell(pTarget, spell_DemoralizingShout, true))
                {
                    return true;
                }
            }
        }
        if (myRage > 100)
        {
            if (spell_ShieldBlock > 0)
            {
                if (CastSpell(me, spell_ShieldBlock))
                {
                    return true;
                }
            }
            if (spell_BattleShout > 0)
            {
                if (CastSpell(me, spell_BattleShout, true))
                {
                    return true;
                }
            }
            if (spell_Rend > 0)
            {
                if (CastSpell(pTarget, spell_Rend, true, true))
                {
                    return true;
                }
            }
        }
        if (myRage > 150)
        {
            if (spell_SunderArmor > 0)
            {
                if (CastSpell(pTarget, spell_SunderArmor, true, true, false, 5))
                {
                    return true;
                }
            }
        }
        if (myRage > 200)
        {
            if (spell_Disarm > 0)
            {
                if (pTarget->GetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_DISPLAY))
                {
                    if (CastSpell(pTarget, spell_Disarm))
                    {
                        return true;
                    }
                }
            }
        }
        if (myRage > 400)
        {
            if (spell_HeroicStrike > 0)
            {
                if (CastSpell(pTarget, spell_HeroicStrike))
                {
                    return true;
                }
            }
        }
    }

    return true;
}

bool Nier_Warrior::Tank(Unit* pTarget)
{
    if (!Nier_Base::Tank(pTarget))
    {
        return false;
    }

    if (me->IsNonMeleeSpellCasted(false, false, true))
    {
        return true;
    }
    ChooseTarget(pTarget);
    me->Attack(pTarget, true);
    if (Chase(pTarget))
    {
        if (me->GetHealthPercent() < 20.0f)
        {
            if (spell_ShieldWall > 0)
            {
                if (CastSpell(me, spell_ShieldWall))
                {
                    return true;
                }
            }
            if (spell_LastStand > 0)
            {
                if (CastSpell(me, spell_LastStand))
                {
                    return true;
                }
            }
        }
        if (pTarget->GetTargetGuid() != me->GetObjectGuid())
        {
            if (spell_Taunt > 0)
            {
                if (CastSpell(pTarget, spell_Taunt))
                {
                    return true;
                }
            }
        }
        if (spell_Bloodrage > 0)
        {
            if (CastSpell(me, spell_Bloodrage))
            {
                return true;
            }
        }
        uint32 myRage = me->GetPower(Powers::POWER_RAGE);
        if (myRage > 100)
        {
            if (pTarget->IsNonMeleeSpellCasted(false, false, true))
            {
                if (spell_ShieldBash > 0)
                {
                    if (CastSpell(pTarget, spell_ShieldBash))
                    {
                        return true;
                    }
                }
            }
            if (spell_DemoralizingShout > 0)
            {
                if (CastSpell(pTarget, spell_DemoralizingShout, true))
                {
                    return true;
                }
            }
        }
        if (myRage > 50)
        {
            if (spell_Revenge > 0)
            {
                if (CastSpell(pTarget, spell_Revenge))
                {
                    return true;
                }
            }
        }
        if (myRage > 100)
        {
            if (spell_ShieldBlock > 0)
            {
                if (CastSpell(me, spell_ShieldBlock))
                {
                    return true;
                }
            }
            if (spell_BattleShout > 0)
            {
                if (CastSpell(me, spell_BattleShout, true))
                {
                    return true;
                }
            }
            if (spell_Rend > 0)
            {
                if (CastSpell(pTarget, spell_Rend, true, true))
                {
                    return true;
                }
            }
        }
        if (myRage > 150)
        {
            if (spell_SunderArmor > 0)
            {
                if (CastSpell(pTarget, spell_SunderArmor, true, true, false, 5))
                {
                    return true;
                }
            }
        }
        if (myRage > 200)
        {
            if (spell_Disarm > 0)
            {
                if (pTarget->GetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_DISPLAY))
                {
                    if (CastSpell(pTarget, spell_Disarm))
                    {
                        return true;
                    }
                }
            }
        }
        if (myRage > 400)
        {
            if (spell_HeroicStrike > 0)
            {
                if (CastSpell(pTarget, spell_HeroicStrike))
                {
                    return true;
                }
            }
        }
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

    if (me->GetObjectGuid() == pTarget->GetObjectGuid())
    {
        if (spell_DefensiveStance > 0)
        {
            if (CastSpell(me, spell_DefensiveStance, true))
            {
                return true;
            }
        }
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
    me->LearnSpell(201, false);
    me->LearnSpell(2567, false);
    spell_HeroicStrike = 78;
    spell_BattleShout = 6673;
    if (myLevel >= 4)
    {
        spell_Rend = 772;
        spell_Charge = 100;
    }
    if (myLevel >= 6)
    {
        spell_ThunderClap = 6343;
    }
    if (myLevel >= 8)
    {
        spell_HeroicStrike = 284;
    }
    if (myLevel >= 10)
    {
        spell_Rend = 6546;
        spell_Bloodrage = 2687;
        me->CastSpell(me, 8121, false);
        spell_SunderArmor = 7386;
        spell_DefensiveStance = 71;
        spell_Taunt = 355;
    }
    if (myLevel >= 12)
    {
        spell_ShieldBash = 72;
        spell_BattleShout = 5242;
    }
    if (myLevel >= 14)
    {
        spell_DemoralizingShout = 1160;
        spell_Revenge = 6572;
    }
    if (myLevel >= 16)
    {
        spell_MockingBlow = 694;
        spell_ShieldBlock = 2565;
        spell_HeroicStrike = 285;
    }
    if (myLevel >= 18)
    {
        spell_Disarm = 676;
        spell_ThunderClap = 8198;
    }
    if (myLevel >= 20)
    {
        spell_Cleave = 845;
        spell_Rend = 6547;
    }
    if (myLevel >= 22)
    {
        spell_BattleShout = 6192;
    }
    if (myLevel >= 24)
    {
        spell_DemoralizingShout = 6190;
        spell_Revenge = 6574;
        spell_HeroicStrike = 1608;
        spell_LastStand = 12975;
    }
    if (myLevel >= 26)
    {
        spell_ChallengingShout = 1161;
        spell_Charge = 6178;
    }
    if (myLevel >= 28)
    {
        spell_ShieldWall = 871;
        spell_ThunderClap = 8204;
    }
    if (myLevel >= 30)
    {
        spell_Cleave = 7369;
        spell_Rend = 6548;
        me->CastSpell(me, 8616, false);
        spell_intercept = 20252;
    }
    if (myLevel >= 32)
    {
        spell_BerserkerRage = 18499;
        spell_HeroicStrike = 11564;
        spell_BattleShout = 11549;
    }
    if (myLevel >= 34)
    {
        spell_DemoralizingShout = 11554;
        spell_Revenge = 7379;
    }
    if (myLevel >= 38)
    {
        spell_ThunderClap = 8205;
    }
    if (myLevel >= 40)
    {
        spell_ShieldSlam = 23922;
        spell_Cleave = 11608;
        spell_Rend = 11572;
        spell_HeroicStrike = 11565;
    }
    if (myLevel >= 42)
    {
        spell_BattleShout = 11550;
        spell_Vigilance = 50720;
    }
    if (myLevel >= 44)
    {
        spell_DemoralizingShout = 11555;
        spell_Revenge = 11600;
    }
    if (myLevel >= 46)
    {
        spell_Charge = 11578;
    }
    if (myLevel >= 48)
    {
        spell_ShieldSlam = 23923;
        spell_ThunderClap = 11580;
        spell_HeroicStrike = 11566;
    }
    if (myLevel >= 50)
    {
        spell_Cleave = 11609;
        spell_Rend = 11573;
    }
    if (myLevel >= 51)
    {
        spell_Devastate = 20243;
    }
    if (myLevel >= 52)
    {
        spell_BattleShout = 11551;
        spell_Warbringer = 57499;
    }
    if (myLevel >= 54)
    {
        spell_DemoralizingShout = 11556;
        spell_ShieldSlam = 23924;
        spell_Revenge = 11601;
    }
    if (myLevel >= 56)
    {
        spell_HeroicStrike = 11567;
    }
    if (myLevel >= 58)
    {
        spell_ThunderClap = 11581;
    }
    if (myLevel >= 60)
    {
        spell_ShieldSlam = 23925;
        spell_Revenge = 25288;
        spell_Devastate = 30016;
        spell_Cleave = 20569;
        spell_Rend = 11574;
        spell_HeroicStrike = 25286;
        spell_BattleShout = 25289;
        spell_Shockwave = 46968;
    }
    if (myLevel >= 62)
    {
        spell_DemoralizingShout = 25202;
    }
    if (myLevel >= 63)
    {
        spell_Revenge = 25269;
    }
    if (myLevel >= 66)
    {
        spell_ShieldSlam = 25258;
        spell_HeroicStrike = 29707;
    }
    if (myLevel >= 67)
    {
        spell_ThunderClap = 25264;
    }
    if (myLevel >= 68)
    {
        spell_Cleave = 25231;
        spell_Rend = 25208;
    }
    if (myLevel >= 69)
    {
        spell_BattleShout = 2048;
    }
    if (myLevel >= 70)
    {
        spell_DemoralizingShout = 25203;
        spell_ShieldSlam = 30356;
        spell_Revenge = 30357;
        spell_Devastate = 30022;
        spell_HeroicStrike = 30324;
        spell_Intervene = 3411;
    }
    if (myLevel >= 71)
    {
        spell_Rend = 46845;
    }
    if (myLevel >= 72)
    {
        spell_Cleave = 47519;
        spell_HeroicStrike = 47449;
    }
    if (myLevel >= 73)
    {
        spell_ThunderClap = 47501;
    }
    if (myLevel >= 75)
    {
        spell_ShieldSlam = 47487;
        spell_Devastate = 47497;
    }
    if (myLevel >= 76)
    {
        spell_Rend = 47465;
        spell_HeroicStrike = 47450;
    }
    if (myLevel >= 77)
    {
        spell_Cleave = 47520;
    }
    if (myLevel >= 78)
    {
        spell_ThunderClap = 47502;
        spell_BattleShout = 47436;
    }
    if (myLevel >= 79)
    {
        spell_DemoralizingShout = 47437;
    }
    if (myLevel >= 80)
    {
        spell_ShieldSlam = 47488;
        spell_Revenge = 57823;
        spell_Devastate = 47498;
        spell_HeroicThrow = 57755;
    }
    me->UpdateSkillsToMaxSkillsForLevel();
    std::ostringstream msgStream;
    msgStream << me->GetName() << " initialized";
    sWorld.SendServerMessage(ServerMessageType::SERVER_MSG_CUSTOM, msgStream.str().c_str());

    return true;
}

bool Nier_Warrior::ResetTalentsAndSpells()
{
    if (!Nier_Base::ResetTalentsAndSpells())
    {
        return false;
    }

    // talent tab : 161 - arm, 164 - berserker, 163 - Protection
    LearnTalent(141);
    LearnTalent(1601);
    LearnTalent(138);
    LearnTalent(153);
    LearnTalent(140);
    LearnTalent(147);
    LearnTalent(146);
    LearnTalent(152);
    LearnTalent(1654);
    LearnTalent(144);
    LearnTalent(148);
    LearnTalent(1652);
    LearnTalent(1660);
    LearnTalent(1653);
    LearnTalent(142);
    LearnTalent(1666);
    LearnTalent(2236);
    LearnTalent(150);
    LearnTalent(1871);
    LearnTalent(2246);
    LearnTalent(1872);

    LearnTalent(1893);

    LearnTalent(130);

    LearnTalent(702);
    LearnTalent(149);

    LearnTalent(157);

    // warrior trainer Arias'ta Bladesinger
    TrainSpells(4087);

    return true;
}

void Nier_Warrior::EquipRandomItem(uint32 pEquipSlot)
{
    uint32 itemClass = 0;
    uint32 itemSubclassArmor = 3;
    uint32 itemSubclass = 0;

    if (me->GetLevel() >= 40)
    {
        itemSubclassArmor = 4;
    }
    uint32 inventoryType = 0;
    if (pEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_HEAD)
    {
        itemClass = 4;
        itemSubclass = itemSubclassArmor;
        inventoryType = 1;
    }
    else if (pEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_SHOULDERS)
    {
        itemClass = 4;
        itemSubclass = itemSubclassArmor;
        inventoryType = 3;
    }
    else if (pEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_WRISTS)
    {
        itemClass = 4;
        itemSubclass = itemSubclassArmor;
        inventoryType = 9;
    }
    else if (pEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_WAIST)
    {
        itemClass = 4;
        itemSubclass = itemSubclassArmor;
        inventoryType = 6;
    }
    else if (pEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_FEET)
    {
        itemClass = 4;
        itemSubclass = itemSubclassArmor;
        inventoryType = 8;
    }
    else if (pEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_HANDS)
    {
        itemClass = 4;
        itemSubclass = itemSubclassArmor;
        inventoryType = 10;
    }
    else if (pEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_CHEST)
    {
        itemClass = 4;
        itemSubclass = itemSubclassArmor;
        inventoryType = 5;
    }
    else if (pEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_LEGS)
    {
        itemClass = 4;
        itemSubclass = itemSubclassArmor;
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
        itemSubclass = 7;
        inventoryType = InventoryType::INVTYPE_WEAPON;
    }
    else if (pEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_OFFHAND)
    {
        itemClass = 4;
        itemSubclass = 6;
        inventoryType = 14;
    }
    else if (pEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_RANGED)
    {
        itemClass = 2;
        itemSubclass = 16;
        inventoryType = 25;
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
