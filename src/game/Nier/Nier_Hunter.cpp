#include "Nier_Hunter.h"
#include "Pet.h"
#include "Spell.h"

Nier_Hunter::Nier_Hunter()
{
    specialty = 0;

    spell_ArcaneShot = 0;
    spell_SerpentSting = 0;
    spell_RapidFire = 0;
    spell_HuntersMark = 0;
    spell_Volley = 0;
    spell_AspectOfTheHawk = 0;
    spell_TameBeast = 0;
    spell_CallPet = 0;
    spell_DismissPet = 0;
    spell_RevivePet = 0;
    spell_ConcussiveShot = 0;
    spell_AutoShot = 0;

    spell_RaptorStrike = 0;

    spell_TrueshotAura = 0;

    ammoEntry = 0;

    petNumber = 0;
}

bool Nier_Hunter::Prepare()
{
    if (!Nier_Base::Prepare())
    {
        return false;
    }

    if (!me->HasItemCount(ammoEntry, 1000))
    {
        me->StoreNewItemInBestSlots(ammoEntry, 1000);
    }
    me->SetAmmo(ammoEntry);

    followDistance = frand(15.0f, 35.0f);

    if (spell_CallPet > 0)
    {
        if (Pet* mePet = me->GetPet())
        {
            if (!mePet->IsAlive())
            {
                if (CastSpell(me, spell_RevivePet))
                {
                    return true;
                }
            }
        }
        else
        {
            Pet* dbPet = new Pet;
            if (dbPet->LoadPetFromDB(me, 0))
            {
                petNumber = dbPet->GetCharmInfo()->GetPetNumber();
                if (CastSpell(me, spell_CallPet))
                {
                    return true;
                }
            }
            else
            {
                delete dbPet;

                std::unique_ptr<QueryResult> creatureQR = WorldDatabase.Query("SELECT entry FROM creature_template where type = 1 and pet_family > 0 order by rand() limit 5");
                if (creatureQR)
                {
                    Field* fields = creatureQR->Fetch();
                    uint32 cEntry = fields[0].GetUInt32();

                    if (const CreatureInfo* ci = sObjectMgr.GetCreatureTemplate(cEntry))
                    {
                        Pet* newPet = new Pet(HUNTER_PET);
                        if (newPet->CreateBaseAtCreatureInfo(ci, me->GetMap(), me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), me->GetOrientation()))
                        {
                            newPet->SetOwnerGuid(me->GetObjectGuid());
                            newPet->SetCreatorGuid(me->GetObjectGuid());
                            newPet->SetFactionTemplateId(me->GetFactionTemplateId());
                            newPet->SetUInt32Value(UNIT_CREATED_BY_SPELL, spell_TameBeast);
                            if (newPet->InitStatsForLevel(me->GetLevel()))
                            {
                                newPet->GetCharmInfo()->SetPetNumber(newPet->GetObjectGuid().GetEntry(), true);
                                newPet->GetCharmInfo()->SetReactState(REACT_DEFENSIVE);
                                newPet->InitializeDefaultName();
                                newPet->AIM_Initialize();
                                newPet->InitPetCreateSpells();
                                newPet->SetHealth(newPet->GetMaxHealth());
                                newPet->SetUInt32Value(UNIT_FIELD_LEVEL, me->GetLevel() - 1);
                                newPet->SetLoyaltyLevel(LoyaltyLevel::BEST_FRIEND);
                                newPet->SetPvP(true);
                                newPet->GetMap()->Add((Creature*)newPet);
                                newPet->SetUInt32Value(UNIT_FIELD_LEVEL, me->GetLevel());
                                me->SetPet(newPet);
                                newPet->SavePetToDB(PET_SAVE_AS_CURRENT);
                                petNumber = newPet->GetCharmInfo()->GetPetNumber();
                                me->PetSpellInitialize();
                                me->SaveToDB();

                                if (CastSpell(me, spell_DismissPet))
                                {
                                    return true;
                                }
                            }
                            else
                            {
                                delete newPet;
                            }
                        }
                        else
                        {
                            delete newPet;
                        }
                    }
                }
            }
        }
    }

    return true;
}

bool Nier_Hunter::Attack(Unit* pTarget)
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
    if (targetDistance > NIER_DISTANCE_SIGHT)
    {
        return false;
    }

    ChooseTarget(pTarget);
    if (Chase(pTarget, 35.0f))
    {
        if (me->GetHealthPercent() < 30.0f)
        {
            HealthPotion();
        }
        if (me->GetPowerPercent(Powers::POWER_MANA) < 30.0f)
        {
            ManaPotion();
        }
        if (Pet* mePet = me->GetPet())
        {
            mePet->HandlePetCommand(CommandStates::COMMAND_ATTACK, pTarget);
        }
        if (pTarget->IsMoving())
        {
            if (CastSpell(pTarget, spell_ConcussiveShot, true))
            {
                return true;
            }
        }
        if (spell_HuntersMark > 0)
        {
            if (CastSpell(pTarget, spell_HuntersMark, true))
            {
                return true;
            }
        }
        float targetDistance = me->GetDistance(pTarget);
        if (targetDistance > NIER_DISTANCE_FOLLOW)
        {
            bool shooting = false;
            if (Spell* spell = me->GetCurrentSpell(CURRENT_AUTOREPEAT_SPELL))
            {
                if (spell->m_spellInfo->Id == spell_AutoShot)
                {
                    if (spell->m_targets.getUnitTargetGuid() == pTarget->GetObjectGuid())
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
                CastSpell(pTarget, spell_AutoShot);
            }
            if (spell_RapidFire > 0)
            {
                uint32 healthGaps = pTarget->GetMaxHealth() / me->GetMaxHealth();
                if (healthGaps > 4)
                {
                    if (CastSpell(me, spell_RapidFire, true))
                    {
                        return true;
                    }
                }
            }
            if (spell_SerpentSting > 0)
            {
                if (CastSpell(pTarget, spell_SerpentSting, true, true))
                {
                    return true;
                }
            }
            if (spell_ArcaneShot > 0)
            {
                if (CastSpell(pTarget, spell_ArcaneShot))
                {
                    return true;
                }
            }
        }
        else
        {
            if (Chase(pTarget))
            {
                me->Attack(pTarget, true);
                if (spell_RaptorStrike > 0)
                {
                    if (CastSpell(pTarget, spell_RaptorStrike))
                    {
                        return true;
                    }
                }
            }
        }
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

    if (me->GetObjectGuid() == pTarget->GetObjectGuid())
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

        if (spell_CallPet > 0)
        {
            if (Pet* mePet = me->GetPet())
            {
                if (!mePet->IsAlive())
                {
                    if (CastSpell(me, spell_RevivePet))
                    {
                        return true;
                    }
                }
                mePet->SetPower(Powers::POWER_HAPPINESS, HAPPINESS_LEVEL_SIZE * 2);
            }
            else
            {
                Pet* dbPet = new Pet;
                if (dbPet->LoadPetFromDB(me, 0))
                    //if (dbPet->LoadPetFromDB(me, 0, petNumber))
                {
                    if (CastSpell(me, spell_CallPet))
                    {
                        return true;
                    }
                }
                else
                {
                    delete dbPet;
                }
            }
        }
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

    spell_AutoShot = 75;
    spell_RaptorStrike = 2973;
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
        spell_RaptorStrike = 14260;
    }
    if (myLevel >= 10)
    {
        ammoEntry = 2515;
        spell_SerpentSting = 13549;
        spell_AspectOfTheHawk = 13165;
        me->CastSpell(me, 23356, false);
        me->CastSpell(me, 23357, false);
        spell_TameBeast = 1515;
        spell_CallPet = 883;
        spell_DismissPet = 2641;
        spell_RevivePet = 982;
    }
    if (myLevel >= 12)
    {
        spell_ArcaneShot = 14281;
    }
    if (myLevel >= 16)
    {
        spell_RaptorStrike = 14261;
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
    if (myLevel >= 24)
    {
        spell_RaptorStrike = 14262;
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
    if (myLevel >= 32)
    {
        spell_RaptorStrike = 14263;
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
        spell_RaptorStrike = 14264;
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
        spell_RaptorStrike = 14265;
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
    if (myLevel >= 56)
    {
        spell_RaptorStrike = 14266;
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

    return true;
}

bool Nier_Hunter::ResetTalentsAndSpells()
{
    if (!Nier_Base::ResetTalentsAndSpells())
    {
        return false;
    }

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

    return true;
}

void Nier_Hunter::EquipRandomItem(uint32 pEquipSlot)
{
    uint32 itemClass = 0;
    uint32 itemSubclassArmor = 2;
    uint32 itemSubclass = 0;

    if (me->GetLevel() >= 40)
    {
        itemSubclassArmor = 3;
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
        itemSubclass = 1;
        inventoryType = InventoryType::INVTYPE_2HWEAPON;
    }
    else if (pEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_OFFHAND)
    {
        inventoryType = 0;
    }
    else if (pEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_RANGED)
    {
        itemClass = 2;
        itemSubclass = 2;
        inventoryType = InventoryType::INVTYPE_RANGED;
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
