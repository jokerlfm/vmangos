#include "Nier_Warlock.h"

Nier_Warlock::Nier_Warlock()
{
    spell_Shoot = 0;
    spell_Immolate = 0;
    spell_ShadowBolt = 0;
    spell_SummonImp = 0;
    spell_Nightfall = 0;
    spell_Corruption = 0;
    spell_CurseOfWeakness = 0;
    spell_LifeTap = 0;
    spell_DrainLife = 0;

    spell_AmplifyCurse = 0;
    spell_DemonArmor = 0;

    petSpellBooksItemIdSet.clear();
    petSpellBooksItemIdSet.insert(16302);
    petSpellBooksItemIdSet.insert(16316);
    petSpellBooksItemIdSet.insert(16317);
    petSpellBooksItemIdSet.insert(16318);
    petSpellBooksItemIdSet.insert(16319);
    petSpellBooksItemIdSet.insert(16320);
    petSpellBooksItemIdSet.insert(16321);
    petSpellBooksItemIdSet.insert(16322);
    petSpellBooksItemIdSet.insert(16323);
    petSpellBooksItemIdSet.insert(16324);
    petSpellBooksItemIdSet.insert(16325);
    petSpellBooksItemIdSet.insert(16326);
    petSpellBooksItemIdSet.insert(16327);
    petSpellBooksItemIdSet.insert(16328);
    petSpellBooksItemIdSet.insert(16329);
    petSpellBooksItemIdSet.insert(16330);
    petSpellBooksItemIdSet.insert(16331);
    petSpellBooksItemIdSet.insert(16346);
    petSpellBooksItemIdSet.insert(16347);
    petSpellBooksItemIdSet.insert(16348);
    petSpellBooksItemIdSet.insert(16349);
    petSpellBooksItemIdSet.insert(16350);
    petSpellBooksItemIdSet.insert(16351);
    petSpellBooksItemIdSet.insert(16352);
    petSpellBooksItemIdSet.insert(16353);
    petSpellBooksItemIdSet.insert(16354);
    petSpellBooksItemIdSet.insert(16355);
    petSpellBooksItemIdSet.insert(16356);
    petSpellBooksItemIdSet.insert(16357);
    petSpellBooksItemIdSet.insert(16358);
    petSpellBooksItemIdSet.insert(16359);
    petSpellBooksItemIdSet.insert(16360);
    petSpellBooksItemIdSet.insert(16361);
    petSpellBooksItemIdSet.insert(16362);
    petSpellBooksItemIdSet.insert(16363);
    petSpellBooksItemIdSet.insert(16364);
    petSpellBooksItemIdSet.insert(16365);
    petSpellBooksItemIdSet.insert(16366);

}

bool Nier_Warlock::Prepare()
{
    if (!Nier_Base::Prepare())
    {
        return false;
    }

    if (Pet* mePet = me->GetPet())
    {
        //if (mePet->GetReactState() != ReactStates::REACT_DEFENSIVE)
        //{
        //    mePet->SetReactState(ReactStates::REACT_DEFENSIVE);
        //}
        //if (mePet->GetCharmInfo()->GetReactState() != ReactStates::REACT_DEFENSIVE)
        //{
        //    mePet->GetCharmInfo()->SetReactState(ReactStates::REACT_DEFENSIVE);
        //}
        for (PetSpellMap::iterator itr = mePet->m_petSpells.begin(); itr != mePet->m_petSpells.end(); itr++)
        {
            mePet->ToggleAutocast(itr->first, true);
        }
    }

    uint32 meLevel = me->GetLevel();
    for (std::unordered_set<uint32>::iterator bookIT = petSpellBooksItemIdSet.begin(); bookIT != petSpellBooksItemIdSet.end(); bookIT++)
    {
        uint32 bookEntry = *bookIT;
        if (ItemPrototype const* bookProto = sObjectMgr.GetItemPrototype(bookEntry))
        {
            if (bookProto->RequiredLevel > meLevel)
            {
                continue;
            }
            // item spells casted at use
            uint32 validBooksNumber = 0;
            for (const _ItemSpell& spellData : bookProto->Spells)
            {
                uint32 eachSpellId = spellData.SpellId;
                if (eachSpellId > 0)
                {
                    me->CastSpell(me, eachSpellId, true);
                    validBooksNumber++;
                }
            }
            std::ostringstream msgStream;
            msgStream << "books learned : " << validBooksNumber;
            me->Say(msgStream.str().c_str(), Language::LANG_UNIVERSAL);
        }
    }
}

bool Nier_Warlock::Attack(Unit* pTarget)
{
    if (!Nier_Base::Attack(pTarget))
    {
        return false;
    }

    if (me->IsNonMeleeSpellCasted(false, false, true))
    {
        return true;
    }
    float targetDistance = me->GetDistance(pTarget);
    if (targetDistance > VISIBILITY_DISTANCE_NORMAL)
    {
        return false;
    }

    ChooseTarget(pTarget);
    if (Chase(pTarget, VISIBILITY_DISTANCE_TINY))
    {
        if (Pet* mePet = me->GetPet())
        {
            mePet->HandlePetCommand(CommandStates::COMMAND_ATTACK, pTarget);
        }
        if (spell_Immolate > 0)
        {
            if (CastSpell(pTarget, spell_Immolate, true, true))
            {
                return true;
            }
        }
        if (spell_Corruption > 0)
        {
            if (CastSpell(pTarget, spell_Corruption, true, true))
            {
                return true;
            }
        }
        if (spell_CurseOfWeakness > 0)
        {
            if (spell_AmplifyCurse > 0)
            {
                uint32 healthGaps = pTarget->GetMaxHealth() / me->GetMaxHealth();
                if (healthGaps > 4)
                {
                    if (CastSpell(me, spell_AmplifyCurse))
                    {
                        return true;
                    }
                }
            }
            if (CastSpell(pTarget, spell_CurseOfWeakness, true))
            {
                return true;
            }
        }
        if (me->HasAura(spell_Nightfall))
        {
            if (CastSpell(pTarget, spell_ShadowBolt))
            {
                return true;
            }
        }
        if (spell_LifeTap > 0)
        {
            if (me->GetPowerPercent(Powers::POWER_MANA) < 50.0f)
            {
                if (me->GetHealthPercent() > 30.0f)
                {
                    if (CastSpell(me, spell_LifeTap))
                    {
                        return true;
                    }
                }
            }
        }
        if (spell_DrainLife > 0)
        {
            if (CastSpell(pTarget, spell_DrainLife))
            {
                return true;
            }
        }
    }

    return true;
}

bool Nier_Warlock::Tank(Unit* pTarget)
{
    if (!Nier_Base::Tank(pTarget))
    {
        return false;
    }

    return true;
}

bool Nier_Warlock::Heal(Unit* pTarget)
{
    if (!Nier_Base::Heal(pTarget))
    {
        return false;
    }

    return false;
}

bool Nier_Warlock::Cure(Unit* pTarget)
{
    if (!Nier_Base::Cure(pTarget))
    {
        return false;
    }

    return false;
}

bool Nier_Warlock::Buff(Unit* pTarget)
{
    if (!Nier_Base::Buff(pTarget))
    {
        return false;
    }

    if (me->GetObjectGuid() == pTarget->GetObjectGuid())
    {
        if (spell_DemonArmor > 0)
        {
            if (CastSpell(me, spell_DemonArmor, true))
            {
                return true;
            }
        }

        if (Pet* mePet = me->GetPet())
        {
            //if (mePet->GetReactState() != ReactStates::REACT_DEFENSIVE)
            //{
            //    mePet->SetReactState(ReactStates::REACT_DEFENSIVE);
            //}
            //if (mePet->GetCharmInfo()->GetReactState() != ReactStates::REACT_DEFENSIVE)
            //{
            //    mePet->GetCharmInfo()->SetReactState(ReactStates::REACT_DEFENSIVE);
            //}
            for (PetSpellMap::iterator itr = mePet->m_petSpells.begin(); itr != mePet->m_petSpells.end(); itr++)
            {
                mePet->ToggleAutocast(itr->first, true);
            }
        }
        else
        {
            if (spell_SummonImp > 0)
            {
                if (CastSpell(me, spell_SummonImp))
                {
                    return true;
                }
            }
        }
    }

    return false;
}

bool Nier_Warlock::Revive(Unit* pTarget)
{
    if (!Nier_Base::Revive(pTarget))
    {
        return false;
    }

    return true;
}

bool Nier_Warlock::InitializeCharacter(uint32 pTargetLevel)
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
    // stave 
    me->LearnSpell(227, true);
    // wand
    me->LearnSpell(5009, true);
    spell_Shoot = 5019;
    spell_ShadowBolt = 686;
    spell_Immolate = 707;
    spell_SummonImp = 688;
    spell_DemonArmor = 687;

    if (myLevel >= 4)
    {
        spell_Corruption = 172;
        spell_CurseOfWeakness = 702;
    }
    if (myLevel >= 6)
    {
        spell_ShadowBolt = 695;
        spell_LifeTap = 1454;
    }
    if (myLevel >= 8)
    {

    }
    if (myLevel >= 10)
    {
        spell_Immolate = 707;
        spell_DemonArmor = 696;
    }
    if (myLevel >= 12)
    {
        spell_ShadowBolt = 705;
        spell_CurseOfWeakness = 1108;
    }
    if (myLevel >= 14)
    {
        spell_Corruption = 6222;
        spell_DrainLife = 689;
    }
    if (myLevel >= 16)
    {
        spell_LifeTap = 1455;
    }
    if (myLevel >= 20)
    {
        spell_ShadowBolt = 1088;
        spell_Immolate = 1094;
        spell_DemonArmor = 706;
    }
    if (myLevel >= 22)
    {
        spell_CurseOfWeakness = 6205;
        spell_DrainLife = 699;
    }
    if (myLevel >= 24)
    {
        spell_Corruption = 6223;
    }
    if (myLevel >= 25)
    {
        spell_Nightfall = 18094;
    }
    if (myLevel >= 26)
    {
        spell_Nightfall = 18095;
        spell_LifeTap = 1456;
    }
    if (myLevel >= 27)
    {
        spell_AmplifyCurse = 18288;
    }
    if (myLevel >= 28)
    {
        spell_ShadowBolt = 1106;
    }
    if (myLevel >= 30)
    {
        spell_Immolate = 2941;
        spell_DrainLife = 709;
        spell_DemonArmor = 1086;
    }
    if (myLevel >= 32)
    {
        spell_CurseOfWeakness = 7646;
    }
    if (myLevel >= 34)
    {
        spell_Corruption = 7648;
    }
    if (myLevel >= 36)
    {
        spell_ShadowBolt = 7641;
        spell_LifeTap = 11687;
    }
    if (myLevel >= 38)
    {
        spell_DrainLife = 7651;
    }
    if (myLevel >= 40)
    {
        spell_Immolate = 11665;
        spell_DemonArmor = 11733;
    }
    if (myLevel >= 42)
    {
        spell_CurseOfWeakness = 11707;
    }
    if (myLevel >= 44)
    {
        spell_ShadowBolt = 11659;
        spell_Corruption = 11671;
    }
    if (myLevel >= 46)
    {
        spell_LifeTap = 11688;
        spell_DrainLife = 11699;
    }
    if (myLevel >= 50)
    {
        spell_Immolate = 11667;
        spell_DemonArmor = 11734;
    }
    if (myLevel >= 52)
    {
        spell_ShadowBolt = 11660;
        spell_CurseOfWeakness = 11708;
    }
    if (myLevel >= 54)
    {
        spell_Corruption = 11672;
        spell_DrainLife = 11700;
    }
    if (myLevel >= 56)
    {
        spell_LifeTap = 11689;
    }
    if (myLevel >= 58)
    {

    }
    if (myLevel >= 60)
    {
        spell_ShadowBolt = 11661;
        spell_ShadowBolt = 25307;
        spell_Immolate = 11668;
        spell_Immolate = 25309;
        spell_Corruption = 25311;
        spell_DemonArmor = 11735;
    }

    me->UpdateSkillsToMaxSkillsForLevel();
    std::ostringstream msgStream;
    msgStream << me->GetName() << " initialized";
    sWorld.SendServerMessage(ServerMessageType::SERVER_MSG_CUSTOM, msgStream.str().c_str());

    return true;
}

bool Nier_Warlock::ResetTalentsAndSpells()
{
    if (!Nier_Base::ResetTalentsAndSpells())
    {
        return false;
    }

    // talent tab : 302 - Affliction, 303 - Demonology, 301 - Destruction 

    // Affliction
    LearnTalent(1003);
    LearnTalent(1005);
    LearnTalent(1004);
    LearnTalent(1002);
    LearnTalent(1061);
    LearnTalent(1006);
    LearnTalent(1007);
    LearnTalent(1041);
    LearnTalent(1021);
    LearnTalent(1042);

    // Demonology
    LearnTalent(1222);

    // Destruction
    LearnTalent(944);
    LearnTalent(983);
    LearnTalent(981);

    // Warlock Trainer Alexander Calder
    TrainSpells(5173);

    return true;
}

void Nier_Warlock::EquipRandomItem(uint32 pEquipSlot)
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
