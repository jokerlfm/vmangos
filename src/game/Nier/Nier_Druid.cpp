//#include "Nier_Druid.h"
//#include "World.h"
//
//Nier_Druid::Nier_Druid() :Nier_Base()
//{
//    spell_InsectSwarm = 0;
//    spell_MoonkinForm = 0;
//    spell_Typhoon = 0;
//    spell_Starfall = 0;
//    spell_Wrath = 0;
//    spell_Rebirth = 0;
//    spell_Innervate = 0;
//    spell_RemoveCurse = 0;
//    spell_Thorns = 0;
//    spell_FaerieFire = 0;
//    spell_EntanglingRoots = 0;
//    spell_Hurricane = 0;
//    spell_Revive = 0;
//    spell_Barkskin = 0;
//    spell_Starfire = 0;
//    spell_Hibernate = 0;
//    spell_Gift_Of_The_Wild = 0;
//    spell_Mark_Of_The_Wild = 0;
//    spell_Moonfire = 0;
//    spell_Force_Of_Nature = 0;
//    spell_CurePoison = 0;
//
//    aura_Eclipse_Solar = 0;
//    aura_Eclipse_Lunar = 0;
//
//    ogThornTarget = ObjectGuid();
//}
//
//void Nier_Druid::InitializeCharacter(uint32 pmTargetLevel, uint32 pmSpecialtyTabIndex)
//{
//    if (!me)
//    {
//        return;
//    }
//    specialty = pmSpecialtyTabIndex;
//    me->ClearInCombat();
//    uint32 myLevel = me->GetLevel();
//    if (myLevel != pmTargetLevel)
//    {
//        me->GiveLevel(pmTargetLevel);
//        me->LearnDefaultSpells();
//        me->LearnQuestRewardedSpells();
//
//        ResetTalent();
//        RemoveEquipments();
//        myLevel = me->GetLevel();
//    }
//    spell_Wrath = 5176;
//    spell_Mark_Of_The_Wild = 1126;
//    aura_Eclipse_Solar = 48517;
//    aura_Eclipse_Lunar = 48518;
//
//    if (myLevel >= 4)
//    {
//        spell_Moonfire = 8921;
//    }
//    if (myLevel >= 6)
//    {
//        spell_Wrath = 5177;
//        spell_Thorns = 467;
//    }
//    if (myLevel >= 8)
//    {
//        spell_EntanglingRoots = 339;
//    }
//    if (myLevel >= 10)
//    {
//        spell_Mark_Of_The_Wild = 5232;
//        spell_Moonfire = 8924;
//    }
//    if (myLevel >= 12)
//    {
//        spell_Revive = 50769;
//    }
//    if (myLevel >= 14)
//    {
//        spell_Wrath = 5178;
//        spell_Thorns = 782;
//        me->CastSpell(me, 8947, false);
//        spell_CurePoison = 8946;
//    }
//    if (myLevel >= 16)
//    {
//        spell_Moonfire = 8925;
//    }
//    if (myLevel >= 18)
//    {
//        spell_RemoveCurse = 475;
//        spell_FaerieFire = 770;
//        spell_EntanglingRoots = 1062;
//        spell_Hibernate = 2637;
//    }
//    if (myLevel >= 20)
//    {
//        spell_Rebirth = 20484;
//        spell_Starfire = 2912;
//        spell_Mark_Of_The_Wild = 6756;
//    }
//    if (myLevel >= 22)
//    {
//        spell_Wrath = 5179;
//        spell_Moonfire = 8926;
//    }
//    if (myLevel >= 24)
//    {
//        spell_RemoveCurse = 2782;
//        spell_Thorns = 1075;
//        spell_Revive = 50768;
//    }
//    if (myLevel >= 26)
//    {
//        spell_Starfire = 8949;
//    }
//    if (myLevel >= 28)
//    {
//        spell_EntanglingRoots = 5195;
//        spell_Moonfire = 8927;
//    }
//    if (myLevel >= 30)
//    {
//        spell_InsectSwarm = 5570;
//        spell_InsectSwarm = 24974;
//        spell_Wrath = 5180;
//        spell_Rebirth = 20739;
//        spell_Mark_Of_The_Wild = 5234;
//    }
//    if (myLevel >= 34)
//    {
//        spell_Thorns = 8914;
//        spell_Starfire = 8950;
//        spell_Moonfire = 8928;
//    }
//    if (myLevel >= 36)
//    {
//        spell_Revive = 50767;
//    }
//    if (myLevel >= 37)
//    {
//
//    }
//    if (myLevel >= 38)
//    {
//        spell_Wrath = 6780;
//        spell_EntanglingRoots = 5196;
//        spell_Hibernate = 18657;
//    }
//    if (myLevel >= 40)
//    {
//        spell_InsectSwarm = 24975;
//        spell_MoonkinForm = 24858;
//        spell_Rebirth = 20742;
//        spell_Innervate = 29166;
//        spell_Hurricane = 16914;
//        spell_Mark_Of_The_Wild = 8907;
//        spell_Moonfire = 8929;
//    }
//    if (myLevel >= 41)
//    {
//
//    }
//    if (myLevel >= 42)
//    {
//        spell_Starfire = 8951;
//    }
//    if (myLevel >= 44)
//    {
//        spell_Thorns = 9756;
//        spell_Barkskin = 22812;
//    }
//    if (myLevel >= 46)
//    {
//        spell_Wrath = 8905;
//        spell_Moonfire = 9833;
//    }
//    if (myLevel >= 48)
//    {
//        spell_EntanglingRoots = 9852;
//        spell_Revive = 50766;
//    }
//    if (myLevel >= 50)
//    {
//        spell_InsectSwarm = 24976;
//        spell_Typhoon = 50516;
//        spell_Rebirth = 20747;
//        spell_Hurricane = 17401;
//        spell_Starfire = 9875;
//        spell_Gift_Of_The_Wild = 21849;
//        spell_Mark_Of_The_Wild = 9884;
//    }
//    if (myLevel >= 51)
//    {
//        spell_Force_Of_Nature = 33831;
//    }
//    if (myLevel >= 52)
//    {
//        spell_Moonfire = 9834;
//    }
//    if (myLevel >= 54)
//    {
//        spell_Wrath = 9912;
//        spell_Thorns = 9910;
//    }
//    if (myLevel >= 58)
//    {
//        spell_EntanglingRoots = 9853;
//        spell_Starfire = 9876;
//        spell_Hibernate = 18658;
//        spell_Moonfire = 9835;
//    }
//    if (myLevel >= 60)
//    {
//        spell_InsectSwarm = 24977;
//        spell_Typhoon = 53223;
//        spell_Starfall = 48505;
//        spell_Rebirth = 20748;
//        spell_Hurricane = 17402;
//        spell_Revive = 50765;
//        spell_Starfire = 25298;
//        spell_Gift_Of_The_Wild = 21850;
//        spell_Mark_Of_The_Wild = 9885;
//    }
//    if (myLevel >= 61)
//    {
//        spell_Wrath = 26984;
//    }
//    if (myLevel >= 63)
//    {
//        spell_Moonfire = 26987;
//    }
//    if (myLevel >= 64)
//    {
//        spell_Thorns = 26992;
//    }
//    if (myLevel >= 65)
//    {
//
//    }
//    if (myLevel >= 66)
//    {
//
//    }
//    if (myLevel >= 67)
//    {
//        spell_Starfire = 26986;
//    }
//    if (myLevel >= 68)
//    {
//        spell_EntanglingRoots = 26989;
//    }
//    if (myLevel >= 69)
//    {
//        spell_Wrath = 26985;
//        spell_Rebirth = 26994;
//        spell_Revive = 50764;
//    }
//    if (myLevel >= 70)
//    {
//        spell_Typhoon = 53225;
//        spell_Starfall = 53199;
//        spell_Hurricane = 27012;
//        spell_Gift_Of_The_Wild = 26991;
//        spell_Mark_Of_The_Wild = 26990;
//        spell_Moonfire = 26988;
//    }
//    if (myLevel >= 71)
//    {
//
//    }
//    if (myLevel >= 72)
//    {
//        spell_Starfire = 48464;
//    }
//    if (myLevel >= 73)
//    {
//
//    }
//    if (myLevel >= 74)
//    {
//        spell_Wrath = 48459;
//        spell_Thorns = 53307;
//    }
//    if (myLevel >= 75)
//    {
//        spell_Typhoon = 53226;
//        spell_Starfall = 53200;
//        spell_Moonfire = 48462;
//    }
//    if (myLevel >= 76)
//    {
//
//    }
//    if (myLevel >= 77)
//    {
//
//    }
//    if (myLevel >= 78)
//    {
//        spell_EntanglingRoots = 53308;
//        spell_Starfire = 48465;
//    }
//    if (myLevel >= 79)
//    {
//        spell_Wrath = 48461;
//        spell_Rebirth = 48477;
//    }
//    if (myLevel >= 80)
//    {
//        spell_InsectSwarm = 48468;
//        spell_Typhoon = 61384;
//        spell_Starfall = 53201;
//        spell_Hurricane = 48467;
//        spell_Revive = 50763;
//        spell_Gift_Of_The_Wild = 48470;
//        spell_Mark_Of_The_Wild = 48469;
//        spell_Moonfire = 48463;
//    }
//    me->UpdateSkillsToMaxSkillsForLevel();
//    std::ostringstream msgStream;
//    msgStream << me->GetName() << " initialized";
//    sWorld.SendServerMessage(ServerMessageType::SERVER_MSG_CUSTOM, msgStream.str().c_str());
//}
//
//void Nier_Druid::ResetTalent()
//{
//    if (!me)
//    {
//        return;
//    }
//    me->ResetTalents(true);
//
//    // talent tab : 283 - balance 301 - feral 302 - restoration
//    LearnTalent(762);
//    LearnTalent(783);
//    LearnTalent(1822);
//    LearnTalent(789);
//    LearnTalent(764);
//    LearnTalent(792);
//    LearnTalent(788);
//    LearnTalent(2239);
//    LearnTalent(1782);
//    LearnTalent(1784);
//    LearnTalent(793);
//    LearnTalent(1912);
//    LearnTalent(1783);
//    LearnTalent(1785);
//    LearnTalent(2240);
//    LearnTalent(1923);
//    LearnTalent(1787);
//    LearnTalent(1925);
//    LearnTalent(790);
//    LearnTalent(1928);
//    LearnTalent(1926);
//
//    LearnTalent(1284);
//
//    LearnTalent(1924);
//    LearnTalent(1786);
//    LearnTalent(2238);
//    LearnTalent(763);
//    LearnTalent(784);
//
//    // druid trainer Denatharion
//    TrainSpells(4218);
//}
//
//bool Nier_Druid::InitializeEquipments(bool pmReset)
//{
//    if (!me)
//    {
//        return true;
//    }
//    if (pmReset)
//    {
//        for (uint8 slot = INVENTORY_SLOT_ITEM_START; slot < INVENTORY_SLOT_ITEM_END; ++slot)
//        {
//            if (Item* inventoryItem = me->GetItemByPos(INVENTORY_SLOT_BAG_0, slot))
//            {
//                me->DestroyItem(INVENTORY_SLOT_BAG_0, slot, true);
//            }
//        }
//        for (uint32 checkEquipSlot = EquipmentSlots::EQUIPMENT_SLOT_HEAD; checkEquipSlot < EquipmentSlots::EQUIPMENT_SLOT_TABARD; checkEquipSlot++)
//        {
//            if (Item* currentEquip = me->GetItemByPos(INVENTORY_SLOT_BAG_0, checkEquipSlot))
//            {
//                me->DestroyItem(INVENTORY_SLOT_BAG_0, checkEquipSlot, true);
//            }
//        }
//    }
//    uint32 myLevel = me->GetLevel();
//    uint32 minQuality = ItemQualities::ITEM_QUALITY_UNCOMMON;
//    if (myLevel < 20)
//    {
//        minQuality = ItemQualities::ITEM_QUALITY_POOR;
//    }
//    for (uint32 checkEquipSlot = EquipmentSlots::EQUIPMENT_SLOT_HEAD; checkEquipSlot < EquipmentSlots::EQUIPMENT_SLOT_TABARD; checkEquipSlot++)
//    {
//        if (checkEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_HEAD)
//        {
//            if (myLevel < 30)
//            {
//                continue;
//            }
//        }
//        else if (checkEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_SHOULDERS)
//        {
//            if (myLevel < 30)
//            {
//                continue;
//            }
//        }
//        else if (checkEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_NECK)
//        {
//            if (myLevel < 30)
//            {
//                continue;
//            }
//        }
//        else if (checkEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_FINGER1 || checkEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_FINGER2)
//        {
//            if (myLevel < 30)
//            {
//                continue;
//            }
//        }
//        std::unordered_set<uint32> inventoryTypeSet;
//        uint32 modType = ItemModType::ITEM_MOD_INTELLECT;
//        uint32 equipItemClass = 0;
//        uint32 equipItemSubClass = 0;
//        if (checkEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_HEAD)
//        {
//            equipItemClass = 4;
//            equipItemSubClass = 2;
//        }
//        else if (checkEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_SHOULDERS)
//        {
//            equipItemClass = 4;
//            equipItemSubClass = 2;
//        }
//        else if (checkEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_WRISTS)
//        {
//            equipItemClass = 4;
//            equipItemSubClass = 2;
//        }
//        else if (checkEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_WAIST)
//        {
//            equipItemClass = 4;
//            equipItemSubClass = 2;
//        }
//        else if (checkEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_FEET)
//        {
//            equipItemClass = 4;
//            equipItemSubClass = 2;
//        }
//        else if (checkEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_HANDS)
//        {
//            equipItemClass = 4;
//            equipItemSubClass = 2;
//        }
//        else if (checkEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_CHEST)
//        {
//            equipItemClass = 4;
//            equipItemSubClass = 2;
//        }
//        else if (checkEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_LEGS)
//        {
//            equipItemClass = 4;
//            equipItemSubClass = 2;
//        }
//        else if (checkEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_BACK)
//        {
//            equipItemClass = 4;
//            equipItemSubClass = 1;
//        }
//        else if (checkEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_NECK)
//        {
//            equipItemClass = 4;
//            equipItemSubClass = 0;
//        }
//        else if (checkEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_FINGER1)
//        {
//            equipItemClass = 4;
//            equipItemSubClass = 0;
//        }
//        else if (checkEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_FINGER2)
//        {
//            equipItemClass = 4;
//            equipItemSubClass = 0;
//        }
//        else if (checkEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_MAINHAND)
//        {
//            equipItemClass = 2;
//            equipItemSubClass = 10;
//        }
//        else if (checkEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_RANGED)
//        {
//            continue;
//        }
//        else
//        {
//            continue;
//        }
//        if (Item* currentEquip = me->GetItemByPos(INVENTORY_SLOT_BAG_0, checkEquipSlot))
//        {
//            if (const ItemPrototype* checkIT = currentEquip->GetProto())
//            {
//                if (checkIT->Quality >= minQuality)
//                {
//                    continue;
//                }
//                else
//                {
//                    me->DestroyItem(INVENTORY_SLOT_BAG_0, checkEquipSlot, true);
//                }
//            }
//        }
//        EquipRandomItem(checkEquipSlot, equipItemClass, equipItemSubClass, minQuality, modType, inventoryTypeSet);
//    }
//
//    return true;
//}
//
//void Nier_Druid::Prepare()
//{
//    Nier_Base::Prepare();
//    if (!me)
//    {
//        return;
//    }
//    else if (!me->IsAlive())
//    {
//        return;
//    }
//
//    me->Say("Prepared", Language::LANG_UNIVERSAL);
//}
//
//bool Nier_Druid::DPS(Unit* pmTarget, bool pmRushing, float pmDistanceMax, float pmDistanceMin, bool pmHolding, bool pmInstantOnly, bool pmChasing)
//{
//    if (!me)
//    {
//        return false;
//    }
//    else if (!me->IsAlive())
//    {
//        return false;
//    }
//    if (me->IsNonMeleeSpellCasted(false, false, true))
//    {
//        return true;
//    }
//    if (!pmTarget)
//    {
//        return false;
//    }
//    else if (!pmTarget->IsAlive())
//    {
//        if (me->GetTargetGuid() == pmTarget->GetObjectGuid())
//        {
//            ClearTarget();
//        }
//        return false;
//    }
//    else if (!me->IsValidAttackTarget(pmTarget))
//    {
//        if (me->GetTargetGuid() == pmTarget->GetObjectGuid())
//        {
//            ClearTarget();
//        }
//        return false;
//    }
//    else if (pmTarget->IsImmuneToDamage(SpellSchoolMask::SPELL_SCHOOL_MASK_NORMAL))
//    {
//        if (me->GetTargetGuid() == pmTarget->GetObjectGuid())
//        {
//            ClearTarget();
//        }
//        return false;
//    }
//    if (!pmTarget->CanSeeInWorld(me))
//    {
//        if (me->GetTargetGuid() == pmTarget->GetObjectGuid())
//        {
//            ClearTarget();
//        }
//        return false;
//    }
//    if (pmChasing)
//    {
//        if (!nm->Chase(pmTarget, pmDistanceMax, pmDistanceMin))
//        {
//            if (me->GetTargetGuid() == pmTarget->GetObjectGuid())
//            {
//                ClearTarget();
//            }
//            return false;
//        }
//    }
//    ChooseTarget(pmTarget);
//    float targetDistance = me->GetDistance(pmTarget);
//    if (targetDistance > NIER_FAR_DISTANCE)
//    {
//        return true;
//    }
//    if (me->GetPowerPercent(Powers::POWER_MANA) < 30.0f)
//    {
//        ManaPotion();
//    }
//    if (spell_MoonkinForm > 0)
//    {
//        CastSpell(me, spell_MoonkinForm, true);
//    }
//    if (pmRushing)
//    {
//        if (spell_Force_Of_Nature > 0)
//        {
//            if (CastSpell(me, spell_Force_Of_Nature))
//            {
//                return true;
//            }
//        }
//        if (spell_Starfall > 0)
//        {
//            if (CastSpell(me, spell_Starfall))
//            {
//                return true;
//            }
//        }
//    }
//    if (spell_FaerieFire > 0)
//    {
//        if (CastSpell(pmTarget, spell_FaerieFire, true))
//        {
//            return true;
//        }
//    }
//    if (spell_Moonfire > 0)
//    {
//        if (CastSpell(pmTarget, spell_Moonfire, true, true))
//        {
//            return true;
//        }
//    }
//    if (spell_InsectSwarm > 0)
//    {
//        if (CastSpell(pmTarget, spell_InsectSwarm, true, true))
//        {
//            return true;
//        }
//    }
//    if (targetDistance < NIER_NORMAL_DISTANCE)
//    {
//        if (spell_Typhoon > 0)
//        {
//            if (CastSpell(pmTarget, spell_Typhoon))
//            {
//                return true;
//            }
//        }
//        if (spell_Barkskin > 0)
//        {
//            if (pmTarget->GetTargetGuid() == me->GetObjectGuid())
//            {
//                if (CastSpell(me, spell_Barkskin))
//                {
//                    return true;
//                }
//            }
//        }
//    }
//    if (!pmInstantOnly)
//    {
//        if (spell_Starfire > 0)
//        {
//            if (me->HasAura(aura_Eclipse_Lunar))
//            {
//                if (CastSpell(pmTarget, spell_Starfire))
//                {
//                    return true;
//                }
//            }
//        }
//        if (me->HasAura(aura_Eclipse_Solar))
//        {
//            if (CastSpell(pmTarget, spell_Wrath))
//            {
//                return true;
//            }
//        }
//        if (spell_Starfire > 0)
//        {
//            if (CastSpell(pmTarget, spell_Starfire))
//            {
//                return true;
//            }
//        }
//        if (CastSpell(pmTarget, spell_Wrath))
//        {
//            return true;
//        }
//    }
//
//    return true;
//}
//
//bool Nier_Druid::AOE(Unit* pmTarget, bool pmRushing, float pmDistanceMax, float pmDistanceMin, bool pmHolding, bool pmInstantOnly, bool pmChasing)
//{
//    if (!me)
//    {
//        return false;
//    }
//    else if (!me->IsAlive())
//    {
//        return false;
//    }
//    if (me->IsNonMeleeSpellCasted(false, false, true))
//    {
//        return true;
//    }
//    if (!pmTarget)
//    {
//        return false;
//    }
//    else if (!pmTarget->IsAlive())
//    {
//        if (me->GetTargetGuid() == pmTarget->GetObjectGuid())
//        {
//            ClearTarget();
//        }
//        return false;
//    }
//    else if (!me->IsValidAttackTarget(pmTarget))
//    {
//        if (me->GetTargetGuid() == pmTarget->GetObjectGuid())
//        {
//            ClearTarget();
//        }
//        return false;
//    }
//    else if (pmTarget->IsImmuneToDamage(SpellSchoolMask::SPELL_SCHOOL_MASK_NORMAL))
//    {
//        if (me->GetTargetGuid() == pmTarget->GetObjectGuid())
//        {
//            ClearTarget();
//        }
//        return false;
//    }
//    if (!pmTarget->CanSeeInWorld(me))
//    {
//        if (me->GetTargetGuid() == pmTarget->GetObjectGuid())
//        {
//            ClearTarget();
//        }
//        return false;
//    }
//    if (pmChasing)
//    {
//        if (!nm->Chase(pmTarget, pmDistanceMax, pmDistanceMin))
//        {
//            if (me->GetTargetGuid() == pmTarget->GetObjectGuid())
//            {
//                ClearTarget();
//            }
//            return false;
//        }
//    }
//    ChooseTarget(pmTarget);
//    float targetDistance = me->GetDistance(pmTarget);
//    if (targetDistance > NIER_MAX_DISTANCE)
//    {
//        return true;
//    }
//    if (me->GetPowerPercent(Powers::POWER_MANA) < 30.0f)
//    {
//        ManaPotion();
//    }
//    if (spell_MoonkinForm > 0)
//    {
//        CastSpell(me, spell_MoonkinForm, true);
//    }
//    if (!pmInstantOnly)
//    {
//        if (spell_Hurricane > 0)
//        {
//            if (CastSpell(pmTarget, spell_Hurricane))
//            {
//                return true;
//            }
//        }
//    }
//
//    return false;
//}
//
//bool Nier_Druid::Cure(Unit* pmTarget)
//{
//    if (!me)
//    {
//        return false;
//    }
//    else if (!me->IsAlive())
//    {
//        return false;
//    }
//    if (!pmTarget)
//    {
//        return false;
//    }
//    else if (!pmTarget->IsAlive())
//    {
//        return false;
//    }
//    float targetDistance = me->GetDistance(pmTarget);
//    if (targetDistance > NIER_MAX_DISTANCE)
//    {
//        return false;
//    }
//
//    std::multimap< uint32, SpellAuraHolder*> sahMap = pmTarget->GetSpellAuraHolderMap();
//    for (std::multimap< uint32, SpellAuraHolder*>::iterator sahIT = sahMap.begin(); sahIT != sahMap.end(); sahIT++)
//    {
//        if (SpellAuraHolder* eachSAH = sahIT->second)
//        {
//            if (const SpellEntry* pS = eachSAH->GetSpellProto())
//            {
//                if (!pS->IsPositiveSpell())
//                {
//                    if (pS->Dispel == DispelType::DISPEL_POISON)
//                    {
//                        if (CastSpell(pmTarget, spell_CurePoison))
//                        {
//                            return true;
//                        }
//                    }
//                    else
//                    {
//                        if (pS->Dispel == DispelType::DISPEL_CURSE)
//                        {
//                            if (CastSpell(pmTarget, spell_RemoveCurse))
//                            {
//                                return true;
//                            }
//                        }
//                    }
//                }
//            }
//        }
//    }
//
//    return false;
//}
//
//bool Nier_Druid::Buff(Unit* pmTarget)
//{
//    if (!me)
//    {
//        return false;
//    }
//    else if (!me->IsAlive())
//    {
//        return false;
//    }
//    if (!pmTarget)
//    {
//        return false;
//    }
//    else if (!pmTarget->IsAlive())
//    {
//        return false;
//    }
//    if (me->GetObjectGuid() == pmTarget->GetObjectGuid())
//    {
//        if (spell_MoonkinForm > 0)
//        {
//            CastSpell(me, spell_MoonkinForm, true);
//        }
//    }
//    if (spell_Thorns > 0)
//    {
//        if (ogThornTarget.IsEmpty())
//        {
//            if (Group* myGroup = me->GetGroup())
//            {
//                for (GroupReference* groupRef = myGroup->GetFirstMember(); groupRef != nullptr; groupRef = groupRef->next())
//                {
//                    if (Player* member = groupRef->getSource())
//                    {
//                        if (member->GetObjectGuid() != me->GetObjectGuid())
//                        {
//                            if (member->groupRole == GroupRole::GroupRole_Tank)
//                            {
//                                ogThornTarget = member->GetObjectGuid();
//                                break;
//                            }
//                        }
//                    }
//                }
//            }
//        }
//        if (Player* tank = ObjectAccessor::FindPlayer(ogThornTarget))
//        {
//            if (tank->IsInWorld())
//            {
//                if (tank->IsInSameGroupWith(me))
//                {
//                    if (CastSpell(tank, spell_Thorns, true))
//                    {
//                        return true;
//                    }
//                }
//                else
//                {
//                    ogThornTarget = ObjectGuid();
//                }
//            }
//            else
//            {
//                ogThornTarget = ObjectGuid();
//            }
//        }
//        else
//        {
//            ogThornTarget = ObjectGuid();
//        }
//    }
//    float targetDistance = me->GetDistance(pmTarget);
//    if (targetDistance > NIER_MAX_DISTANCE)
//    {
//        return false;
//    }
//
//    bool doBuff = true;
//    if (spell_Mark_Of_The_Wild > 0 || spell_Gift_Of_The_Wild > 0)
//    {
//        if (!pmTarget->HasAura(spell_Mark_Of_The_Wild) && !pmTarget->HasAura(spell_Gift_Of_The_Wild))
//        {
//            if (spell_Gift_Of_The_Wild > 0)
//            {
//                if (CastSpell(pmTarget, spell_Gift_Of_The_Wild))
//                {
//                    return true;
//                }
//            }
//            else if (spell_Mark_Of_The_Wild > 0)
//            {
//                if (CastSpell(pmTarget, spell_Mark_Of_The_Wild))
//                {
//                    return true;
//                }
//            }
//        }
//    }
//
//    return false;
//}
//
//bool Nier_Druid::Revive(Player* pmTarget)
//{
//    if (!me)
//    {
//        return false;
//    }
//    else if (!me->IsAlive())
//    {
//        return false;
//    }
//    if (!pmTarget)
//    {
//        return false;
//    }
//    else if (pmTarget->IsAlive())
//    {
//        return false;
//    }
//    float targetDistance = me->GetDistance(pmTarget);
//    if (targetDistance > NIER_MAX_DISTANCE)
//    {
//        return false;
//    }
//
//    if (me->IsInCombat())
//    {
//        if (spell_Rebirth > 0)
//        {
//            if (CastSpell(pmTarget, spell_Rebirth, false, false, true))
//            {
//                return true;
//            }
//        }
//    }
//    else
//    {
//        if (spell_Revive > 0)
//        {
//            if (CastSpell(pmTarget, spell_Revive, false, false, true))
//            {
//                return true;
//            }
//        }
//    }
//
//    return false;
//}
//
//bool Nier_Druid::Mark(Unit* pmTarget, int pmRTI)
//{
//    if (pmRTI >= 0)
//    {
//        if (spell_EntanglingRoots > 0)
//        {
//            if (me)
//            {
//                if (pmTarget)
//                {
//                    if (Group* myGroup = me->GetGroup())
//                    {
//                        if (myGroup->GetTargetIconByGuid(pmTarget->GetObjectGuid()) < 0)
//                        {
//                            if (Creature* targetC = (Creature*)pmTarget)
//                            {
//                                if (const CreatureInfo* ci = targetC->GetCreatureInfo())
//                                {
//                                    if (const SpellEntry* pS = sSpellMgr.GetSpellEntry(spell_EntanglingRoots))
//                                    {
//                                        if (!targetC->IsImmuneToSpell(pS, false))
//                                        {
//                                            if (me->IsValidAttackTarget(targetC))
//                                            {
//                                                myGroup->SetTargetIcon(pmRTI, pmTarget->GetObjectGuid());
//                                                return true;
//                                            }
//                                        }
//                                    }
//                                }
//                            }
//                        }
//                    }
//                }
//            }
//        }
//        if (spell_Hibernate > 0)
//        {
//            if (me)
//            {
//                if (pmTarget)
//                {
//                    if (Group* myGroup = me->GetGroup())
//                    {
//                        if (myGroup->GetTargetIconByGuid(pmTarget->GetObjectGuid()) < 0)
//                        {
//                            if (Creature* targetC = (Creature*)pmTarget)
//                            {
//                                if (const CreatureInfo* ci = targetC->GetCreatureInfo())
//                                {
//                                    if (ci->type == CreatureType::CREATURE_TYPE_DRAGONKIN || ci->type == CreatureType::CREATURE_TYPE_BEAST)
//                                    {
//                                        if (const SpellEntry* pS = sSpellMgr.GetSpellEntry(spell_Hibernate))
//                                        {
//                                            if (!targetC->IsImmuneToSpell(pS, false))
//                                            {
//                                                if (me->IsValidAttackTarget(targetC))
//                                                {
//                                                    myGroup->SetTargetIcon(pmRTI, pmTarget->GetObjectGuid());
//                                                    return true;
//                                                }
//                                            }
//                                        }
//                                    }
//                                }
//                            }
//                        }
//                    }
//                }
//            }
//        }
//    }
//
//    return false;
//}
//
//bool Nier_Druid::Assist(int pmRTI)
//{
//    if (pmRTI >= 0)
//    {
//        if (spell_Hibernate > 0)
//        {
//            if (me)
//            {
//                if (me->IsAlive())
//                {
//                    if (Group* myGroup = me->GetGroup())
//                    {
//                        ObjectGuid ogRTI = myGroup->GetGuidByTargetIcon(pmRTI);
//                        if (!ogRTI.IsEmpty())
//                        {
//                            if (Unit* rtiTarget = ObjectAccessor::GetUnit(*me, ogRTI))
//                            {
//                                if (Creature* targetC = (Creature*)rtiTarget)
//                                {
//                                    if (const CreatureInfo* ci = targetC->GetCreatureInfo())
//                                    {
//                                        bool canAssist = false;
//                                        if (ci->type == CreatureType::CREATURE_TYPE_DRAGONKIN || ci->type == CreatureType::CREATURE_TYPE_BEAST)
//                                        {
//                                            if (const SpellEntry* pS = sSpellMgr.GetSpellEntry(spell_Hibernate))
//                                            {
//                                                if (!targetC->IsImmuneToSpell(pS, false))
//                                                {
//                                                    if (me->IsValidAttackTarget(targetC))
//                                                    {
//                                                        canAssist = true;
//                                                        if (me->GetDistance(targetC) < NIER_FAR_DISTANCE)
//                                                        {
//                                                            int duration = 0;
//                                                            if (Aura* activeAura = targetC->GetAura(spell_Hibernate, SpellEffectIndex::EFFECT_INDEX_0))
//                                                            {
//                                                                duration = activeAura->GetAuraDuration();
//                                                            }
//                                                            if (duration < 2000)
//                                                            {
//                                                                if (CastSpell(rtiTarget, spell_Hibernate))
//                                                                {
//                                                                    return true;
//                                                                }
//                                                            }
//                                                        }
//                                                    }
//                                                }
//                                                else
//                                                {
//                                                    me->Say("Target is immune to hibernate.", Language::LANG_UNIVERSAL);
//                                                }
//                                            }
//                                        }
//                                        if (!canAssist)
//                                        {
//                                            if (spell_EntanglingRoots > 0)
//                                            {
//                                                if (const SpellEntry* pS = sSpellMgr.GetSpellEntry(spell_EntanglingRoots))
//                                                {
//                                                    if (!targetC->IsImmuneToSpell(pS, false))
//                                                    {
//                                                        if (me->IsValidAttackTarget(targetC))
//                                                        {
//                                                            canAssist = true;
//                                                            if (me->GetDistance(targetC) < NIER_FAR_DISTANCE)
//                                                            {
//                                                                int duration = 0;
//                                                                if (Aura* activeAura = targetC->GetAura(spell_EntanglingRoots, SpellEffectIndex::EFFECT_INDEX_0))
//                                                                {
//                                                                    duration = activeAura->GetAuraDuration();
//                                                                }
//                                                                if (duration < 2000)
//                                                                {
//                                                                    if (CastSpell(rtiTarget, spell_EntanglingRoots))
//                                                                    {
//                                                                        return true;
//                                                                    }
//                                                                }
//                                                            }
//                                                        }
//                                                    }
//                                                    else
//                                                    {
//                                                        me->Say("Target is immune to entangling roots.", Language::LANG_UNIVERSAL);
//                                                    }
//                                                }
//                                            }
//                                            if (!canAssist)
//                                            {
//                                                myGroup->SetTargetIcon(pmRTI, ObjectGuid());
//                                            }
//                                        }
//                                    }
//                                }
//                            }
//                        }
//                    }
//                }
//            }
//        }
//    }
//
//    return false;
//}
