#include "Nier_Rogue.h"

Nier_Rogue::Nier_Rogue()
{
    spell_Dismantle = 0;
    spell_Backstab = 0;
    spell_Eviscerate = 0;
    spell_FanofKnives = 0;
    spell_BladeFlurry = 0;
    spell_Sprint = 0;
    spell_TricksoftheTrade = 0;
    spell_Kick = 0;
    spell_Sap = 0;
    spell_Stealth = 0;
    spell_SliceandDice = 0;
    spell_Evasion = 0;
    spell_KidneyShot = 0;
    spell_CheapShot = 0;
    spell_Vanish = 0;
    spell_Feint = 0;
    spell_SinisterStrike = 0;
    spell_DeadlyThrow = 0;

    spell_AdrenalineRush = 0;
    spell_Riposte = 0;

    item_InstantPoison = 0;
    item_SlowPoison = 0;

    riposteDelay = 0;
}

bool Nier_Rogue::Attack(Unit* pTarget)
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

    if (targetDistance > NIER_DISTANCE_ENGAGE)
    {
        if (CastSpell(me, spell_Sprint))
        {
            return true;
        }
    }
    ChooseTarget(pTarget);
    me->Attack(pTarget, true);
    if (Chase(pTarget))
    {
        uint32 myEnergy = me->GetPower(Powers::POWER_ENERGY);
        uint32 comboPoints = me->GetComboPoints();
        if (me->GetHealthPercent() < 30.0f)
        {
            HealthPotion();
        }
        if (pTarget->GetTargetGuid() == me->GetObjectGuid())
        {
            if (CastSpell(me, spell_Evasion))
            {
                return true;
            }
            if (pTarget->GetTypeId() != TypeID::TYPEID_PLAYER)
            {
                if (myEnergy >= 20)
                {
                    if (CastSpell(pTarget, spell_Feint))
                    {
                        return true;
                    }
                }
                return true;
            }
        }
        if (pTarget->IsNonMeleeSpellCasted(false, false, true))
        {
            if (CastSpell(pTarget, spell_Kick))
            {
                return true;
            }
            if (comboPoints > 0)
            {
                if (CastSpell(pTarget, spell_KidneyShot))
                {
                    return true;
                }
            }
        }
        if (CastSpell(me, spell_AdrenalineRush))
        {
            return true;
        }
        if (myEnergy > 25)
        {
            if (CastSpell(me, spell_BladeFlurry))
            {
                return true;
            }
            if (!me->HasAura(spell_SliceandDice))
            {
                if (comboPoints > 1)
                {
                    if (CastSpell(pTarget, spell_SliceandDice))
                    {
                        return true;
                    }
                }
            }
            else
            {
                if (comboPoints > 0)
                {
                    uint32 finishRate = urand(1, 4);
                    if (comboPoints > finishRate)
                    {
                        if (CastSpell(pTarget, spell_Eviscerate))
                        {
                            return true;
                        }
                    }
                }
            }
        }
        if (myEnergy > 45)
        {
            if (CastSpell(pTarget, spell_SinisterStrike))
            {
                return true;
            }
        }
    }

    return true;
}

bool Nier_Rogue::Tank(Unit* pTarget)
{
    if (!Nier_Base::Tank(pTarget))
    {
        return false;
    }

    return true;
}

bool Nier_Rogue::Heal(Unit* pTarget)
{
    if (!Nier_Base::Heal(pTarget))
    {
        return false;
    }

    return false;
}

bool Nier_Rogue::Cure(Unit* pTarget)
{
    if (!Nier_Base::Cure(pTarget))
    {
        return false;
    }

    return false;
}

bool Nier_Rogue::Buff(Unit* pTarget)
{
    if (!Nier_Base::Buff(pTarget))
    {
        return false;
    }

    return false;
}

bool Nier_Rogue::Revive(Unit* pTarget)
{
    if (!Nier_Base::Revive(pTarget))
    {
        return false;
    }

    return true;
}

bool Nier_Rogue::InitializeCharacter(uint32 pTargetLevel)
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
    me->LearnSpell(1180, false);
    me->LearnSpell(15590, false);
    me->LearnSpell(2567, false);
    item_SlowPoison = 3775;

    spell_Stealth = 1784;
    spell_SinisterStrike = 1752;
    spell_Eviscerate = 2098;

    if (myLevel >= 4)
    {

    }
    if (myLevel >= 6)
    {
        spell_SinisterStrike = 1757;
    }
    if (myLevel >= 8)
    {
        spell_Eviscerate = 6760;
        spell_Evasion = 5277;
    }
    if (myLevel >= 10)
    {
        spell_Sprint = 2983;
        spell_Sap = 6770;
        spell_SliceandDice = 5171;
    }
    if (myLevel >= 12)
    {
        spell_Kick = 1766;
    }
    if (myLevel >= 14)
    {
        spell_SinisterStrike = 1758;
    }
    if (myLevel >= 16)
    {
        spell_Eviscerate = 6761;
        spell_Feint = 1966;
    }
    if (myLevel >= 18)
    {

    }
    if (myLevel >= 20)
    {
        item_InstantPoison = 6947;
        spell_Dismantle = 51722;
    }
    if (myLevel >= 22)
    {
        spell_Vanish = 1856;
        spell_SinisterStrike = 1759;
    }
    if (myLevel >= 24)
    {
        spell_Eviscerate = 6762;
    }
    if (myLevel >= 26)
    {

    }
    if (myLevel >= 26)
    {
        spell_CheapShot = 1833;
    }
    if (myLevel >= 28)
    {
        item_InstantPoison = 6949;
        spell_Sap = 2070;
        spell_Feint = 6768;
    }
    if (myLevel >= 30)
    {
        spell_BladeFlurry = 13877;
        spell_KidneyShot = 408;
        spell_SinisterStrike = 1760;
    }
    if (myLevel >= 32)
    {
        spell_Eviscerate = 8623;
    }
    if (myLevel >= 34)
    {
        spell_Sprint = 8696;
    }
    if (myLevel >= 36)
    {
        item_InstantPoison = 6950;
    }
    if (myLevel >= 37)
    {

    }
    if (myLevel >= 38)
    {
        spell_SinisterStrike = 8621;
    }
    if (myLevel >= 40)
    {
        spell_Eviscerate = 8624;
        spell_Feint = 8637;
        spell_AdrenalineRush = 13750;
    }
    if (myLevel >= 41)
    {

    }
    if (myLevel >= 42)
    {
        spell_SliceandDice = 6774;
        spell_Vanish = 1857;
    }
    if (myLevel >= 44)
    {
        item_InstantPoison = 8926;
    }
    if (myLevel >= 46)
    {
        spell_SinisterStrike = 11293;
    }
    if (myLevel >= 48)
    {
        spell_Eviscerate = 11299;
        spell_Sap = 11297;
    }
    if (myLevel >= 50)
    {
        spell_Evasion = 26669;
        spell_KidneyShot = 8643;
    }
    if (myLevel >= 52)
    {
        item_InstantPoison = 8927;
        spell_Feint = 11303;
    }
    if (myLevel >= 54)
    {
        spell_SinisterStrike = 11294;
    }
    if (myLevel >= 56)
    {
        spell_Eviscerate = 11300;
    }
    if (myLevel >= 58)
    {
        spell_Sprint = 11305;
    }
    if (myLevel >= 60)
    {
        item_InstantPoison = 8928;
        spell_Eviscerate = 31016;
        spell_Feint = 25302;
    }
    if (myLevel >= 62)
    {
        spell_Vanish = 26889;
        spell_SinisterStrike = 26861;
    }
    if (myLevel >= 64)
    {
        spell_Eviscerate = 26865;
        spell_Feint = 27448;
        spell_DeadlyThrow = 26679;
    }
    if (myLevel >= 66)
    {

    }
    if (myLevel >= 68)
    {
        item_InstantPoison = 21927;
    }
    if (myLevel >= 69)
    {

    }
    if (myLevel >= 70)
    {
        spell_SinisterStrike = 26862;
        spell_DeadlyThrow = 48673;
    }
    if (myLevel >= 71)
    {
        spell_Sap = 51724;
    }
    if (myLevel >= 72)
    {
        spell_Feint = 48658;
    }
    if (myLevel >= 73)
    {
        item_InstantPoison = 43230;
        spell_Eviscerate = 48667;
    }
    if (myLevel >= 74)
    {

    }
    if (myLevel >= 75)
    {
        spell_TricksoftheTrade = 57934;
    }
    if (myLevel >= 76)
    {
        spell_SinisterStrike = 48637;
        spell_DeadlyThrow = 48674;
    }
    if (myLevel >= 77)
    {

    }
    if (myLevel >= 78)
    {
        spell_Feint = 48659;
    }
    if (myLevel >= 79)
    {
        item_InstantPoison = 43231;
        spell_Eviscerate = 48668;
    }
    if (myLevel >= 80)
    {
        spell_FanofKnives = 51723;
        spell_SinisterStrike = 48638;
    }
    me->UpdateSkillsToMaxSkillsForLevel();
    std::ostringstream msgStream;
    msgStream << me->GetName() << " initialized";
    sWorld.SendServerMessage(ServerMessageType::SERVER_MSG_CUSTOM, msgStream.str().c_str());

    return true;
}

bool Nier_Rogue::ResetTalentsAndSpells()
{
    if (!Nier_Base::ResetTalentsAndSpells())
    {
        return false;
    }

    // talent tab : 181 - Combat, 182 - Assassination
    LearnTalent(201);
    LearnTalent(186);
    LearnTalent(187);
    LearnTalent(181);
    LearnTalent(204);
    LearnTalent(301);
    LearnTalent(206);
    LearnTalent(182);
    LearnTalent(221);
    LearnTalent(223);
    LearnTalent(1703);
    LearnTalent(1122);
    LearnTalent(205);

    LearnTalent(276);
    LearnTalent(270);
    LearnTalent(277);
    LearnTalent(281);

    // rogue trainer Osborne the Night Man
    TrainSpells(918);

    return true;
}

void Nier_Rogue::EquipRandomItem(uint32 pEquipSlot)
{
    uint32 itemClass = 0;
    uint32 itemSubclass = 0;
    uint32 inventoryType = 0;
    if (pEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_HEAD)
    {
        itemClass = 4;
        itemSubclass = 2;
        inventoryType = 1;
    }
    else if (pEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_SHOULDERS)
    {
        itemClass = 4;
        itemSubclass = 2;
        inventoryType = 3;
    }
    else if (pEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_WRISTS)
    {
        itemClass = 4;
        itemSubclass = 2;
        inventoryType = 9;
    }
    else if (pEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_WAIST)
    {
        itemClass = 4;
        itemSubclass = 2;
        inventoryType = 6;
    }
    else if (pEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_FEET)
    {
        itemClass = 4;
        itemSubclass = 2;
        inventoryType = 8;
    }
    else if (pEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_HANDS)
    {
        itemClass = 4;
        itemSubclass = 2;
        inventoryType = 10;
    }
    else if (pEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_CHEST)
    {
        itemClass = 4;
        itemSubclass = 2;
        inventoryType = 5;
    }
    else if (pEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_LEGS)
    {
        itemClass = 4;
        itemSubclass = 2;
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
        itemSubclass = 15;
        inventoryType = InventoryType::INVTYPE_WEAPON;
    }
    else if (pEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_OFFHAND)
    {
        itemClass = 2;
        itemSubclass = 15;
        inventoryType = InventoryType::INVTYPE_WEAPON;
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

    int maxReqLevel = me->GetLevel();
    int minReqLevel = maxReqLevel - 10;
    if (minReqLevel < 0)
    {
        minReqLevel = 0;
    }

    EquipOne(pEquipSlot, itemClass, itemSubclass, inventoryType, minReqLevel, maxReqLevel);
}
