#include "Nier_Hunter.h"
#include "World.h"
#include "Pet.h"

Nier_Hunter::Nier_Hunter() :Nier_Base()
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

void Nier_Hunter::InitializeCharacter(uint32 pmTargetLevel, uint32 pmSpecialtyTabIndex)
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
    spell_AutoShot = 75;
    me->LearnSpell(197, true);
    me->LearnSpell(264, true);
    ammoEntry = 2512;
    if (myLevel >= 4)
    {
        spell_SerpentSting = 1978;
    }
    if (myLevel >= 6)
    {
        spell_ArcaneShot = 3044;
        spell_HuntersMark = 1130;
    }
    if (myLevel >= 8)
    {
        spell_ConcussiveShot = 5116;
    }
    if (myLevel >= 10)
    {
        ammoEntry = 2515;
        spell_SerpentSting = 13549;
        spell_AspectOfTheHawk = 13165;
        me->CastSpell(me, 23356, false);
        me->CastSpell(me, 23357, false);
        spell_CallPet = 883;
        spell_DismissPet = 2641;
        spell_RevivePet = 982;
    }
    if (myLevel >= 12)
    {
        spell_ArcaneShot = 14281;
    }
    if (myLevel >= 18)
    {
        spell_SerpentSting = 13550;
        spell_AspectOfTheHawk = 14318;
    }
    if (myLevel >= 20)
    {
        spell_ArcaneShot = 14282;
        me->LearnSpell(200, true);
    }
    if (myLevel >= 22)
    {
        spell_HuntersMark = 14323;
    }
    if (myLevel >= 26)
    {
        ammoEntry = 3030;
    }
    if (myLevel >= 26)
    {
        spell_SerpentSting = 13551;
        spell_RapidFire = 3045;
    }
    if (myLevel >= 28)
    {
        spell_ArcaneShot = 14283;
        spell_AspectOfTheHawk = 14319;
    }
    if (myLevel >= 30)
    {
    }
    if (myLevel >= 34)
    {
        spell_SerpentSting = 13552;
    }
    if (myLevel >= 36)
    {
        spell_ArcaneShot = 14284;
    }
    if (myLevel >= 37)
    {
    }
    if (myLevel >= 38)
    {
        spell_AspectOfTheHawk = 14320;
    }
    if (myLevel >= 40)
    {
        ammoEntry = 11285;
        spell_HuntersMark = 14324;
        spell_Volley = 1510;
    }
    if (myLevel >= 41)
    {
        spell_TrueshotAura = 19506;
    }
    if (myLevel >= 42)
    {
        spell_SerpentSting = 13553;
    }
    if (myLevel >= 44)
    {
        spell_ArcaneShot = 14285;
    }
    if (myLevel >= 48)
    {
        spell_AspectOfTheHawk = 14321;
    }
    if (myLevel >= 50)
    {
        spell_SerpentSting = 13554;
        spell_Volley = 14294;
    }
    if (myLevel >= 52)
    {
        spell_ArcaneShot = 14286;
    }
    if (myLevel >= 55)
    {
        ammoEntry = 28053;
    }
    if (myLevel >= 58)
    {
        spell_SerpentSting = 13555;
        spell_HuntersMark = 14325;
        spell_Volley = 14295;
        spell_AspectOfTheHawk = 14322;
    }
    if (myLevel >= 60)
    {
        spell_ArcaneShot = 14287;
        spell_SerpentSting = 25295;
        spell_AspectOfTheHawk = 25296;
    }

    me->UpdateSkillsToMaxSkillsForLevel();
    std::ostringstream msgStream;
    msgStream << me->GetName() << " initialized";
    sWorld.SendServerMessage(ServerMessageType::SERVER_MSG_CUSTOM, msgStream.str().c_str());
}

void Nier_Hunter::ResetTalent()
{
    if (!me)
    {
        return;
    }
    me->ResetTalents(true);

    // talent tab : 361 - Beast Mastery, 363 - Marksmanship
    LearnTalent(2197);
    LearnTalent(1344);
    LearnTalent(1349);
    LearnTalent(1343);
    LearnTalent(1346);
    LearnTalent(1348);
    LearnTalent(1342);
    LearnTalent(1353);
    LearnTalent(1362);
    LearnTalent(1361);
    LearnTalent(1804);
    LearnTalent(1806);
    LearnTalent(1807);
    LearnTalent(1808);
    LearnTalent(2132);
    LearnTalent(2134);
    LearnTalent(2135);
    LearnTalent(2132, 3);
    LearnTalent(2130);
    LearnTalent(2133);
    LearnTalent(1818);

    LearnTalent(1382);
    LearnTalent(1624);
    LearnTalent(1395);
    LearnTalent(2138);

    // hunter trainer Nightrunner
    TrainSpells(4138);
}

bool Nier_Hunter::InitializeEquipments(bool pmReset)
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
    bool allEquiped = true;
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
        uint32 modType = ItemModType::ITEM_MOD_AGILITY;
        uint32 equipItemClass = 0;
        uint32 equipItemSubClass = 0;
        if (checkEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_HEAD)
        {
            equipItemClass = 4;
            if (myLevel < 40)
            {
                equipItemSubClass = 2;
            }
            else
            {
                equipItemSubClass = 3;
            }
        }
        else if (checkEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_SHOULDERS)
        {
            equipItemClass = 4;
            if (myLevel < 40)
            {
                equipItemSubClass = 2;
            }
            else
            {
                equipItemSubClass = 3;
            }
        }
        else if (checkEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_WRISTS)
        {
            equipItemClass = 4;
            if (myLevel < 40)
            {
                equipItemSubClass = 2;
            }
            else
            {
                equipItemSubClass = 3;
            }
        }
        else if (checkEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_WAIST)
        {
            equipItemClass = 4;
            if (myLevel < 40)
            {
                equipItemSubClass = 2;
            }
            else
            {
                equipItemSubClass = 3;
            }
        }
        else if (checkEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_FEET)
        {
            equipItemClass = 4;
            if (myLevel < 40)
            {
                equipItemSubClass = 2;
            }
            else
            {
                equipItemSubClass = 3;
            }
        }
        else if (checkEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_HANDS)
        {
            equipItemClass = 4;
            if (myLevel < 40)
            {
                equipItemSubClass = 2;
            }
            else
            {
                equipItemSubClass = 3;
            }
        }
        else if (checkEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_CHEST)
        {
            equipItemClass = 4;
            if (myLevel < 40)
            {
                equipItemSubClass = 2;
            }
            else
            {
                equipItemSubClass = 3;
            }
        }
        else if (checkEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_LEGS)
        {
            equipItemClass = 4;
            if (myLevel < 40)
            {
                equipItemSubClass = 2;
            }
            else
            {
                equipItemSubClass = 3;
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
            if (myLevel < 20)
            {
                equipItemSubClass = 1;
            }
            else
            {
                equipItemSubClass = 6;
            }
            modType = -1;
        }
        else if (checkEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_RANGED)
        {
            equipItemClass = 2;
            equipItemSubClass = 2;
            modType = -1;
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
        EquipRandomItem(checkEquipSlot, equipItemClass, equipItemSubClass, minQuality, modType);
        allEquiped = false;
        //break;
    }

    return allEquiped;
}

void Nier_Hunter::Prepare()
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
    if (!me->HasItemCount(ammoEntry, 1000))
    {
        me->StoreNewItemInBestSlots(ammoEntry, 1000);
    }
    me->SetAmmo(ammoEntry);

    if (Pet* myPet = me->GetPet())
    {
        if (myPet->GetReactState() != ReactStates::REACT_DEFENSIVE)
        {
            myPet->SetReactState(ReactStates::REACT_DEFENSIVE);
        }
        for (uint32 petSpellIndex = 0; petSpellIndex < 4; petSpellIndex++)
        {
            if (const SpellEntry* pS = sSpellMgr.GetSpellEntry(myPet->m_spells[petSpellIndex]))
            {
                myPet->ToggleAutocast(myPet->m_spells[petSpellIndex], true);
            }
        }
        myPet->SetLoyaltyLevel(LoyaltyLevel::BEST_FRIEND);
        myPet->SetPower(Powers::POWER_HAPPINESS, HAPPINESS_LEVEL_SIZE * 2);
    }

    me->Say("Prepared", Language::LANG_UNIVERSAL);
}

bool Nier_Hunter::DPS(Unit* pmTarget, bool pmRushing, float pmDistanceMax, float pmDistanceMin, bool pmHolding, bool pmInstantOnly, bool pmChasing)
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
    if (CastSpell(pmTarget, spell_HuntersMark, true))
    {
        return true;
    }
    float targetDistance = me->GetDistance(pmTarget);
    if (targetDistance > NIER_MAX_DISTANCE)
    {
        return true;
    }
    bool shooting = false;
    if (Spell* spell = me->GetCurrentSpell(CURRENT_AUTOREPEAT_SPELL))
    {
        if (spell->m_spellInfo->Id == spell_AutoShot)
        {
            if (spell->m_targets.getUnitTargetGuid() == pmTarget->GetObjectGuid())
            {
                shooting = true;
            }
            else
            {
                me->InterruptSpell(CURRENT_AUTOREPEAT_SPELL, true);
            }
        }
        else
        {
            me->InterruptSpell(CURRENT_AUTOREPEAT_SPELL, true);
        }
    }
    if (!shooting)
    {
        CastSpell(pmTarget, spell_AutoShot);
    }
    PetAttack(pmTarget);
    if (me->GetHealthPercent() < 30.0f)
    {
        HealthPotion();
    }
    if (pmTarget->IsMoving())
    {
        if (CastSpell(pmTarget, spell_ConcussiveShot, true))
        {
            return true;
        }
    }
    if (CastSpell(pmTarget, spell_SerpentSting, true, true))
    {
        return true;
    }
    if (pmRushing)
    {
        if (CastSpell(me, spell_RapidFire, true))
        {
            return true;
        }
        if (CastSpell(pmTarget, spell_ArcaneShot))
        {
            return true;
        }
    }

    return true;
}

bool Nier_Hunter::AOE(Unit* pmTarget, bool pmRushing, float pmDistanceMax, float pmDistanceMin, bool pmHolding, bool pmInstantOnly, bool pmChasing)
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
        if (spell_Volley > 0)
        {
            if (CastSpell(pmTarget, spell_Volley))
            {
                return true;
            }
        }
    }

    return false;
}

bool Nier_Hunter::Buff(Unit* pmTarget)
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
        if (spell_TrueshotAura > 0)
        {
            if (CastSpell(me, spell_TrueshotAura, true))
            {
                return true;
            }
        }
        if (spell_AspectOfTheHawk > 0)
        {
            if (CastSpell(me, spell_AspectOfTheHawk, true))
            {
                return true;
            }
        }
    }

    return false;
}

bool Nier_Hunter::Petting(bool pmSummon, bool pmReset)
{
    if (!me)
    {
        return false;
    }
    else if (!me->IsAlive())
    {
        return false;
    }
    if (spell_CallPet > 0)
    {
        if (pmReset)
        {
            if (Pet* myPet = me->GetPet())
            {
                me->RemovePet(PET_SAVE_AS_DELETED);
                me->SaveToDB(false, false);
                return true;
            }
            return false;
        }
    }

    return false;
}
