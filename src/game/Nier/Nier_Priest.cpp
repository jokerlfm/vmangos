//#include "Nier_Priest.h"
//#include "Player.h"
//#include "Group.h"
//#include "Spell.h"
//#include "World.h"
//
//Nier_Priest::Nier_Priest() :Nier_Base()
//{
//    spell_Renew = 0;
//    spell_LesserHeal = 0;
//    spell_Heal = 0;
//    spell_GreaterHeal = 0;
//    spell_FlashHeal = 0;
//    spell_Resurrection = 0;
//    spell_CureDisease = 0;
//    spell_DispelMagic = 0;
//    spell_DivineSpirit = 0;
//    spell_PowerWord_Fortitude = 0;
//    spell_PowerWord_Shield = 0;
//    spell_Penance = 0;
//    spell_Weakened_Soul = 6788;
//    spell_Prayer_of_Healing = 0;
//    spell_Prayer_of_Spirit = 0;
//    spell_Prayer_of_Fortitude = 0;
//    spell_InnerFocus = 0;
//    spell_PowerInfusion = 0;
//    spell_PainSuppression = 0;
//    spell_DesperatePrayer = 0;
//    spell_HolyNova = 0;
//    aura_Surge_of_Light = 0;
//}
//
//void Nier_Priest::InitializeCharacter(uint32 pmTargetLevel, uint32 pmSpecialtyTabIndex)
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
//    if (myLevel >= 1)
//    {
//        spell_LesserHeal = 2050;
//        spell_PowerWord_Fortitude = 1243;
//    }
//    if (myLevel >= 4)
//    {
//        spell_LesserHeal = 2052;
//    }
//    if (myLevel >= 6)
//    {
//        spell_PowerWord_Shield = 17;
//    }
//    if (myLevel >= 8)
//    {
//        spell_Renew = 139;
//    }
//    if (myLevel >= 10)
//    {
//        spell_LesserHeal = 2053;
//        spell_Resurrection = 2006;
//    }
//    if (myLevel >= 12)
//    {
//        spell_PowerWord_Fortitude = 1244;
//        spell_PowerWord_Shield = 592;
//    }
//    if (myLevel >= 14)
//    {
//        spell_Renew = 6074;
//        spell_CureDisease = 528;
//    }
//    if (myLevel >= 16)
//    {
//        spell_Heal = 2054;
//    }
//    if (myLevel >= 18)
//    {
//        spell_DispelMagic = 527;
//        spell_PowerWord_Shield = 600;
//    }
//    if (myLevel >= 20)
//    {
//        if (specialty == 1)
//        {
//            spell_InnerFocus = 14751;
//        }
//        spell_Renew = 6075;
//        spell_FlashHeal = 2061;
//        spell_HolyNova = 15237;
//    }
//    if (myLevel >= 22)
//    {
//        spell_Heal = 2055;
//        spell_Resurrection = 2010;
//    }
//    if (myLevel >= 24)
//    {
//        spell_PowerWord_Fortitude = 1245;
//        spell_PowerWord_Shield = 3747;
//    }
//    if (myLevel >= 26)
//    {
//        spell_Renew = 6076;
//        spell_FlashHeal = 9472;
//    }
//    if (myLevel >= 28)
//    {
//        spell_Heal = 6063;
//        spell_HolyNova = 15430;
//    }
//    if (myLevel >= 30)
//    {
//        spell_DivineSpirit = 14752;
//        spell_PowerWord_Shield = 6065;
//        spell_Prayer_of_Healing = 596;
//    }
//    if (myLevel >= 32)
//    {
//        spell_Renew = 6077;
//        spell_FlashHeal = 9473;
//    }
//    if (myLevel >= 34)
//    {
//        spell_Heal = 6064;
//        spell_Resurrection = 10880;
//    }
//    if (myLevel >= 36)
//    {
//        spell_PowerWord_Fortitude = 2791;
//        spell_PowerWord_Shield = 6066;
//        aura_Surge_of_Light = 33151;
//        spell_HolyNova = 15431;
//    }
//    if (myLevel >= 38)
//    {
//        spell_Renew = 6078;
//        spell_FlashHeal = 9474;
//    }
//    if (myLevel >= 40)
//    {
//        spell_GreaterHeal = 2060;
//        spell_DivineSpirit = 14818;
//        spell_Prayer_of_Healing = 996;
//        spell_PowerInfusion = 10060;
//    }
//    if (myLevel >= 42)
//    {
//        spell_PowerWord_Shield = 10898;
//    }
//    if (myLevel >= 44)
//    {
//        spell_Renew = 10927;
//        spell_FlashHeal = 10915;
//        spell_HolyNova = 27799;
//    }
//    if (myLevel >= 46)
//    {
//        spell_GreaterHeal = 10963;
//        spell_Resurrection = 10881;
//    }
//    if (myLevel >= 48)
//    {
//        spell_PowerWord_Fortitude = 10937;
//        spell_PowerWord_Shield = 10899;
//        spell_Prayer_of_Fortitude = 21562;
//    }
//    if (myLevel >= 50)
//    {
//        spell_Renew = 10928;
//        spell_FlashHeal = 10916;
//        spell_DivineSpirit = 14819;
//        spell_Prayer_of_Healing = 10960;
//        spell_PainSuppression = 33206;
//    }
//    if (myLevel >= 52)
//    {
//        spell_GreaterHeal = 10964;
//        spell_HolyNova = 27800;
//    }
//    if (myLevel >= 54)
//    {
//        spell_PowerWord_Shield = 10900;
//    }
//    if (myLevel >= 56)
//    {
//        spell_Renew = 10929;
//        spell_FlashHeal = 10917;
//    }
//    if (myLevel >= 58)
//    {
//        spell_GreaterHeal = 10965;
//        spell_Resurrection = 20770;
//    }
//    if (myLevel >= 60)
//    {
//        spell_Renew = 25315;
//        spell_GreaterHeal = 25314;
//        spell_DivineSpirit = 27841;
//        spell_PowerWord_Fortitude = 10938;
//        spell_Penance = 47540;
//        spell_PowerWord_Shield = 10901;
//        spell_Prayer_of_Spirit = 27681;
//        spell_Prayer_of_Fortitude = 21564;
//        spell_Prayer_of_Healing = 10961;
//        spell_HolyNova = 27801;
//    }
//    if (myLevel >= 61)
//    {
//        spell_FlashHeal = 25233;
//    }
//    if (myLevel >= 63)
//    {
//        spell_GreaterHeal = 25210;
//    }
//    if (myLevel >= 65)
//    {
//        spell_Renew = 25221;
//        spell_PowerWord_Shield = 25217;
//    }
//    if (myLevel >= 67)
//    {
//        spell_FlashHeal = 25235;
//    }
//    if (myLevel >= 68)
//    {
//        spell_GreaterHeal = 25213;
//        spell_Resurrection = 25435;
//        spell_Prayer_of_Healing = 25308;
//        spell_HolyNova = 25331;
//    }
//    if (myLevel >= 70)
//    {
//        spell_Renew = 25222;
//        spell_DivineSpirit = 25312;
//        spell_PowerWord_Fortitude = 25389;
//        spell_Penance = 53005;
//        spell_PowerWord_Shield = 25218;
//        spell_Prayer_of_Spirit = 32999;
//        spell_Prayer_of_Fortitude = 25392;
//    }
//    if (myLevel >= 73)
//    {
//        spell_GreaterHeal = 48062;
//        spell_FlashHeal = 48070;
//    }
//    if (myLevel >= 74)
//    {
//        if (specialty == 1)
//        {
//            spell_InnerFocus = 14751;
//        }
//    }
//    if (myLevel >= 75)
//    {
//        spell_Renew = 48067;
//        spell_Penance = 53006;
//        spell_PowerWord_Shield = 48065;
//        spell_HolyNova = 48007;
//    }
//    if (myLevel >= 76)
//    {
//        spell_Prayer_of_Healing = 48072;
//    }
//    if (myLevel >= 78)
//    {
//        spell_GreaterHeal = 48063;
//        spell_Resurrection = 48171;
//    }
//    if (myLevel >= 79)
//    {
//        spell_FlashHeal = 48071;
//    }
//    if (myLevel >= 80)
//    {
//        spell_Renew = 48068;
//        spell_DivineSpirit = 48073;
//        spell_PowerWord_Fortitude = 48161;
//        spell_Penance = 53007;
//        spell_PowerWord_Shield = 48066;
//        spell_Prayer_of_Spirit = 48074;
//        spell_Prayer_of_Fortitude = 48162;
//        if (specialty == 0)
//        {
//            spell_DesperatePrayer = 19236;
//        }
//        spell_HolyNova = 48078;
//    }
//    me->UpdateSkillsToMaxSkillsForLevel();
//    std::ostringstream msgStream;
//    msgStream << me->GetName() << " initialized";
//    sWorld.SendServerMessage(ServerMessageType::SERVER_MSG_CUSTOM, msgStream.str().c_str());
//}
//
//void Nier_Priest::ResetTalent()
//{
//    if (!me)
//    {
//        return;
//    }
//    me->ResetTalents(true);
//
//    // talent tab : 201 - discipline, 202 - holy, 203 - shadow
//
//    // holy
//    LearnTalent(406);
//    LearnTalent(401);
//    LearnTalent(1181);
//    LearnTalent(361);
//    LearnTalent(408);
//    LearnTalent(442);
//    LearnTalent(1561);
//    LearnTalent(402);
//    LearnTalent(404);
//    LearnTalent(410);
//    LearnTalent(342);
//    LearnTalent(343);
//    LearnTalent(344);
//    LearnTalent(348);
//    LearnTalent(347);
//    LearnTalent(352);
//
//    // priest trainer Brother Joshua
//    TrainSpells(5489);
//}
//
//bool Nier_Priest::InitializeEquipments(bool pmReset)
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
//            equipItemSubClass = 1;
//        }
//        else if (checkEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_SHOULDERS)
//        {
//            equipItemClass = 4;
//            equipItemSubClass = 1;
//        }
//        else if (checkEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_WRISTS)
//        {
//            equipItemClass = 4;
//            equipItemSubClass = 1;
//        }
//        else if (checkEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_WAIST)
//        {
//            equipItemClass = 4;
//            equipItemSubClass = 1;
//        }
//        else if (checkEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_FEET)
//        {
//            equipItemClass = 4;
//            equipItemSubClass = 1;
//        }
//        else if (checkEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_HANDS)
//        {
//            equipItemClass = 4;
//            equipItemSubClass = 1;
//        }
//        else if (checkEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_CHEST)
//        {
//            equipItemClass = 4;
//            equipItemSubClass = 1;
//        }
//        else if (checkEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_LEGS)
//        {
//            equipItemClass = 4;
//            equipItemSubClass = 1;
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
//            equipItemClass = 2;
//            equipItemSubClass = 19;
//            inventoryTypeSet.insert(InventoryType::INVTYPE_RANGEDRIGHT);
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
//void Nier_Priest::Prepare()
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
//bool Nier_Priest::Heal(Unit* pmTarget, bool pmInstantOnly)
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
//        return false;
//    }
//    float targetDistance = me->GetDistance(pmTarget);
//    if (targetDistance > NIER_MAX_DISTANCE)
//    {
//        return false;
//    }
//    if (me->GetPowerPercent(Powers::POWER_MANA) < 30.0f)
//    {
//        ManaPotion();
//    }
//    switch (specialty)
//    {
//    case 0:
//    {
//        return Heal_Discipline(pmTarget, pmInstantOnly);
//    }
//    case 1:
//    {
//        return Heal_Holy(pmTarget, pmInstantOnly);
//    }
//    default:
//    {
//        break;
//    }
//    }
//
//    return false;
//}
//
//bool Nier_Priest::Heal_Discipline(Unit* pmTarget, bool pmInstantOnly)
//{
//    return Heal_Holy(pmTarget, pmInstantOnly);
//}
//
//bool Nier_Priest::Heal_Holy(Unit* pmTarget, bool pmInstantOnly)
//{
//    float targetHealthPct = pmTarget->GetHealthPercent();
//    if (targetHealthPct < 90.0f)
//    {
//        if (aura_Surge_of_Light > 0)
//        {
//            if (me->HasAura(aura_Surge_of_Light))
//            {
//                if (CastSpell(pmTarget, spell_FlashHeal))
//                {
//                    return true;
//                }
//            }
//        }
//        if (targetHealthPct < 30.0f)
//        {
//            if (spell_PowerWord_Shield > 0)
//            {
//                if (!pmTarget->HasAura(spell_Weakened_Soul))
//                {
//                    if (CastSpell(pmTarget, spell_PowerWord_Shield))
//                    {
//                        return true;
//                    }
//                }
//            }
//            if (!pmInstantOnly)
//            {
//                if (spell_FlashHeal > 0)
//                {
//                    if (CastSpell(pmTarget, spell_FlashHeal))
//                    {
//                        return true;
//                    }
//                }
//            }
//        }
//        if (spell_Renew > 0)
//        {
//            if (CastSpell(pmTarget, spell_Renew, true, true))
//            {
//                return true;
//            }
//        }
//        if (targetHealthPct < 70.0f)
//        {
//            if (spell_PowerWord_Shield > 0)
//            {
//                if (!pmTarget->HasAura(spell_Weakened_Soul))
//                {
//                    if (CastSpell(pmTarget, spell_PowerWord_Shield))
//                    {
//                        return true;
//                    }
//                }
//            }
//            if (!pmInstantOnly)
//            {
//                if (spell_GreaterHeal > 0)
//                {
//                    if (spell_InnerFocus > 0)
//                    {
//                        CastSpell(me, spell_InnerFocus);
//                    }
//                    if (CastSpell(pmTarget, spell_GreaterHeal))
//                    {
//                        return true;
//                    }
//                }
//                if (spell_Heal > 0)
//                {
//                    if (CastSpell(pmTarget, spell_Heal))
//                    {
//                        return true;
//                    }
//                }
//                if (spell_LesserHeal > 0)
//                {
//                    if (CastSpell(pmTarget, spell_LesserHeal))
//                    {
//                        return true;
//                    }
//                }
//            }
//        }
//    }
//
//    return false;
//}
//
//bool Nier_Priest::ReadyTank(Unit* pmTarget)
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
//        return false;
//    }
//    float targetDistance = me->GetDistance(pmTarget);
//    if (targetDistance > NIER_MAX_DISTANCE)
//    {
//        return false;
//    }
//
//    if (spell_PowerWord_Shield > 0)
//    {
//        if (!pmTarget->HasAura(spell_Weakened_Soul))
//        {
//            if (CastSpell(pmTarget, spell_PowerWord_Shield))
//            {
//                return true;
//            }
//        }
//    }
//
//    return false;
//}
//
//bool Nier_Priest::GroupHeal(Unit* pmTarget, bool pmInstantOnly)
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
//    float targetHealthPct = pmTarget->GetHealthPercent();
//    if (targetHealthPct < 60.0f)
//    {
//        if (spell_Renew > 0)
//        {
//            if (CastSpell(pmTarget, spell_Renew, true, true))
//            {
//                return true;
//            }
//        }
//        if (pmInstantOnly)
//        {
//            if (me->GetDistance(pmTarget) < 10.0f)
//            {
//                if (spell_HolyNova > 0)
//                {
//                    if (CastSpell(me, spell_HolyNova))
//                    {
//                        return true;
//                    }
//                }
//            }
//        }
//        else
//        {
//            if (spell_Prayer_of_Healing > 0)
//            {
//                if (CastSpell(pmTarget, spell_Prayer_of_Healing))
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
//bool Nier_Priest::SimpleHeal(Unit* pmTarget, bool pmInstantOnly)
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
//    float targetHealthPct = pmTarget->GetHealthPercent();
//    if (targetHealthPct < 60.0f)
//    {
//        if (spell_Renew > 0)
//        {
//            if (CastSpell(pmTarget, spell_Renew, true, true))
//            {
//                return true;
//            }
//        }
//        if (!pmInstantOnly)
//        {
//            if (spell_GreaterHeal > 0)
//            {
//                if (CastSpell(pmTarget, spell_GreaterHeal))
//                {
//                    return true;
//                }
//            }
//            if (spell_Heal > 0)
//            {
//                if (CastSpell(pmTarget, spell_Heal))
//                {
//                    return true;
//                }
//            }
//            if (spell_LesserHeal > 0)
//            {
//                if (CastSpell(pmTarget, spell_LesserHeal))
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
//bool Nier_Priest::Cure(Unit* pmTarget)
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
//                    if (eachSAH->GetAuraDuration() > 60000)
//                    {
//                        if (pS->Dispel == DispelType::DISPEL_MAGIC)
//                        {
//                            if (CastSpell(pmTarget, spell_DispelMagic))
//                            {
//                                return true;
//                            }
//                        }
//                        else
//                        {
//                            if (pS->Dispel == DispelType::DISPEL_DISEASE)
//                            {
//                                if (CastSpell(pmTarget, spell_CureDisease))
//                                {
//                                    return true;
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
//bool Nier_Priest::Buff(Unit* pmTarget)
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
//    bool doBuff = true;
//    if (spell_Prayer_of_Spirit > 0)
//    {
//        if (pmTarget->HasAura(spell_Prayer_of_Spirit))
//        {
//            doBuff = false;
//        }
//    }
//    if (doBuff)
//    {
//        if (spell_DivineSpirit > 0)
//        {
//            if (pmTarget->HasAura(spell_DivineSpirit))
//            {
//                doBuff = false;
//            }
//        }
//    }
//    if (doBuff)
//    {
//        if (spell_Prayer_of_Spirit > 0)
//        {
//            if (CastSpell(pmTarget, spell_Prayer_of_Spirit))
//            {
//                return true;
//            }
//        }
//        else if (spell_DivineSpirit > 0)
//        {
//            if (CastSpell(pmTarget, spell_DivineSpirit))
//            {
//                return true;
//            }
//        }
//    }
//    doBuff = true;
//    if (spell_Prayer_of_Fortitude > 0)
//    {
//        if (pmTarget->HasAura(spell_Prayer_of_Fortitude))
//        {
//            doBuff = false;
//        }
//    }
//    if (doBuff)
//    {
//        if (spell_PowerWord_Fortitude > 0)
//        {
//            if (pmTarget->HasAura(spell_PowerWord_Fortitude))
//            {
//                doBuff = false;
//            }
//        }
//    }
//    if (doBuff)
//    {
//        if (spell_Prayer_of_Fortitude > 0)
//        {
//            if (CastSpell(pmTarget, spell_Prayer_of_Fortitude))
//            {
//                return true;
//            }
//        }
//        else if (spell_PowerWord_Fortitude > 0)
//        {
//            if (CastSpell(pmTarget, spell_PowerWord_Fortitude))
//            {
//                return true;
//            }
//        }
//    }
//
//    return false;
//}
//
//bool Nier_Priest::Revive(Player* pmTarget)
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
//    if (spell_Resurrection > 0)
//    {
//        if (CastSpell(pmTarget, spell_Resurrection))
//        {
//            return true;
//        }
//    }
//
//    return false;
//}
