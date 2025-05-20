#include "Nier_Druid.h"
#include "SpellAuras.h"

Nier_Druid::Nier_Druid()
{
    spell_InsectSwarm = 0;
    spell_MoonkinForm = 0;
    spell_Typhoon = 0;
    spell_Starfall = 0;
    spell_Wrath = 0;
    spell_Rebirth = 0;
    spell_Innervate = 0;
    spell_RemoveCurse = 0;
    spell_Thorns = 0;
    spell_FaerieFire = 0;
    spell_EntanglingRoots = 0;
    spell_Hurricane = 0;
    spell_Revive = 0;
    spell_Barkskin = 0;
    spell_Starfire = 0;
    spell_Hibernate = 0;
    spell_Gift_Of_The_Wild = 0;
    spell_Mark_Of_The_Wild = 0;
    spell_Moonfire = 0;
    spell_Force_Of_Nature = 0;
    spell_CurePoison = 0;

    aura_Eclipse_Solar = 0;
    aura_Eclipse_Lunar = 0;

    spell_DemoralizingRoar = 0;
    spell_Enrage = 0;
    spell_BearForm = 0;
    spell_Bash = 0;
    spell_Maul = 0;
    spell_Swipe = 0;
    spell_Faerie_Fire_Feral = 0;
    spell_Growl = 0;
}

bool Nier_Druid::Attack(Unit* pTarget)
{
    if (!Nier_Base::Attack(pTarget))
    {
        return false;
    }

    if (spell_BearForm > 0)
    {
        if (CastSpell(me, spell_BearForm, true))
        {
            return true;
        }
    }

    ChooseTarget(pTarget);
    me->Attack(pTarget, true);
    if (Chase(pTarget))
    {
        if (spell_Faerie_Fire_Feral > 0)
        {
            if (CastSpell(pTarget, spell_Faerie_Fire_Feral, true))
            {
                return true;
            }
        }
        if (spell_Enrage > 0)
        {
            if (CastSpell(me, spell_Enrage))
            {
                return true;
            }
        }

        uint32 myRage = me->GetPower(Powers::POWER_RAGE);
        if (myRage > 100)
        {
            if (pTarget->IsNonMeleeSpellCasted(false, false, true))
            {
                if (spell_Bash > 0)
                {
                    if (CastSpell(pTarget, spell_Bash))
                    {
                        return true;
                    }
                }
            }
            if (spell_DemoralizingRoar > 0)
            {
                if (CastSpell(pTarget, spell_DemoralizingRoar, true))
                {
                    return true;
                }
            }
        }
        if (myRage > 150)
        {
            if (spell_Maul > 0)
            {
                if (CastSpell(pTarget, spell_Maul))
                {
                    return true;
                }
            }
        }
    }

    return true;
}

bool Nier_Druid::Tank(Unit* pTarget)
{
    if (!Nier_Base::Tank(pTarget))
    {
        return false;
    }

    if (spell_BearForm > 0)
    {
        if (CastSpell(me, spell_BearForm, true))
        {
            return true;
        }
    }

    ChooseTarget(pTarget);
    me->Attack(pTarget, true);
    if (Chase(pTarget))
    {
        if (spell_Faerie_Fire_Feral > 0)
        {
            if (CastSpell(pTarget, spell_Faerie_Fire_Feral, true))
            {
                return true;
            }
        }
        if (spell_Enrage > 0)
        {
            if (CastSpell(me, spell_Enrage))
            {
                return true;
            }
        }
        if (pTarget->GetTargetGuid() != me->GetObjectGuid())
        {
            if (spell_Growl > 0)
            {
                if (CastSpell(pTarget, spell_Growl))
                {
                    return true;
                }
            }
        }
        uint32 myRage = me->GetPower(Powers::POWER_RAGE);
        if (myRage > 100)
        {
            if (pTarget->IsNonMeleeSpellCasted(false, false, true))
            {
                if (spell_Bash > 0)
                {
                    if (CastSpell(pTarget, spell_Bash))
                    {
                        return true;
                    }
                }
            }
            if (spell_DemoralizingRoar > 0)
            {
                if (CastSpell(pTarget, spell_DemoralizingRoar, true))
                {
                    return true;
                }
            }
        }
        if (myRage > 200)
        {
            if (spell_Swipe > 0)
            {
                if (CastSpell(pTarget, spell_Swipe))
                {
                    return true;
                }
            }
        }
        if (myRage > 400)
        {
            if (spell_Maul > 0)
            {
                if (CastSpell(pTarget, spell_Maul))
                {
                    return true;
                }
            }
        }
    }

    return true;
}

bool Nier_Druid::Heal(Unit* pTarget)
{
    if (!Nier_Base::Heal(pTarget))
    {
        return false;
    }

    return false;
}

bool Nier_Druid::Cure(Unit* pTarget)
{
    if (!Nier_Base::Cure(pTarget))
    {
        return false;
    }

    std::multimap< uint32, SpellAuraHolder*> sahMap = pTarget->GetSpellAuraHolderMap();
    for (std::multimap< uint32, SpellAuraHolder*>::iterator sahIT = sahMap.begin(); sahIT != sahMap.end(); sahIT++)
    {
        if (SpellAuraHolder* eachSAH = sahIT->second)
        {
            if (const SpellEntry* pS = eachSAH->GetSpellProto())
            {
                if (!pS->IsPositiveSpell())
                {
                    if (pS->Dispel == DispelType::DISPEL_POISON)
                    {
                        if (CastSpell(pTarget, spell_CurePoison))
                        {
                            return true;
                        }
                    }
                    else
                    {
                        if (pS->Dispel == DispelType::DISPEL_CURSE)
                        {
                            if (CastSpell(pTarget, spell_RemoveCurse))
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

bool Nier_Druid::Buff(Unit* pTarget)
{
    if (!Nier_Base::Buff(pTarget))
    {
        return false;
    }

    if (spell_Mark_Of_The_Wild > 0)
    {
        if (CastSpell(pTarget, spell_Mark_Of_The_Wild, true, false, true))
        {
            return true;
        }
    }

    return false;
}

bool Nier_Druid::Revive(Unit* pTarget)
{
    if (!Nier_Base::Revive(pTarget))
    {
        return false;
    }

    return true;
}

bool Nier_Druid::InitializeCharacter(uint32 pTargetLevel)
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
    spell_Wrath = 5176;
    spell_Mark_Of_The_Wild = 1126;
    aura_Eclipse_Solar = 48517;
    aura_Eclipse_Lunar = 48518;

    if (myLevel >= 4)
    {
        spell_Moonfire = 8921;
    }
    if (myLevel >= 6)
    {
        spell_Wrath = 5177;
        spell_Thorns = 467;
    }
    if (myLevel >= 8)
    {
        spell_EntanglingRoots = 339;
    }
    if (myLevel >= 10)
    {
        spell_Mark_Of_The_Wild = 5232;
        spell_Moonfire = 8924;
        spell_DemoralizingRoar = 99;
        spell_BearForm = 5487;
        spell_Maul = 6807;
        spell_Growl = 6795;
    }
    if (myLevel >= 12)
    {
        spell_Revive = 50769;
        spell_Enrage = 5229;
    }
    if (myLevel >= 14)
    {
        spell_Wrath = 5178;
        spell_Thorns = 782;
        me->CastSpell(me, 8947, false);
        spell_CurePoison = 8946;
        spell_Bash = 5211;
    }
    if (myLevel >= 16)
    {
        spell_Moonfire = 8925;
        spell_Swipe = 779;
    }
    if (myLevel >= 18)
    {
        spell_RemoveCurse = 475;
        spell_FaerieFire = 770;
        spell_EntanglingRoots = 1062;
        spell_Hibernate = 2637;
        spell_Maul = 6808;
    }
    if (myLevel >= 20)
    {
        spell_Rebirth = 20484;
        spell_Starfire = 2912;
        spell_Mark_Of_The_Wild = 6756;
        spell_DemoralizingRoar = 1735;
    }
    if (myLevel >= 22)
    {
        spell_Wrath = 5179;
        spell_Moonfire = 8926;
    }
    if (myLevel >= 24)
    {
        spell_RemoveCurse = 2782;
        spell_Thorns = 1075;
        spell_Revive = 50768;
        spell_Swipe = 780;
    }
    if (myLevel >= 25)
    {

    }
    if (myLevel >= 26)
    {
        spell_Starfire = 8949;
        spell_Maul = 6809;
    }
    if (myLevel >= 28)
    {
        spell_EntanglingRoots = 5195;
        spell_Moonfire = 8927;
    }
    if (myLevel >= 30)
    {
        spell_InsectSwarm = 5570;
        spell_InsectSwarm = 24974;
        spell_Wrath = 5180;
        spell_Rebirth = 20739;
        spell_Mark_Of_The_Wild = 5234;
        spell_Bash = 6798;
    }
    if (myLevel >= 32)
    {
        spell_DemoralizingRoar = 9490;
    }
    if (myLevel >= 33)
    {
        spell_Faerie_Fire_Feral = 16857;
        spell_Faerie_Fire_Feral = 17390;
    }
    if (myLevel >= 34)
    {
        spell_Thorns = 8914;
        spell_Starfire = 8950;
        spell_Moonfire = 8928;
        spell_Maul = 8972;
        spell_Swipe = 769;
    }
    if (myLevel >= 36)
    {
        spell_Revive = 50767;
    }
    if (myLevel >= 37)
    {

    }
    if (myLevel >= 38)
    {
        spell_Wrath = 6780;
        spell_EntanglingRoots = 5196;
        spell_Hibernate = 18657;
    }
    if (myLevel >= 40)
    {
        spell_InsectSwarm = 24975;
        spell_MoonkinForm = 24858;
        spell_Rebirth = 20742;
        spell_Innervate = 29166;
        spell_Hurricane = 16914;
        spell_Mark_Of_The_Wild = 8907;
        spell_Moonfire = 8929;
        spell_BearForm = 9634;
    }
    if (myLevel >= 41)
    {

    }
    if (myLevel >= 42)
    {
        spell_Starfire = 8951;
        spell_DemoralizingRoar = 9747;
        spell_Maul = 9745;
        spell_Faerie_Fire_Feral = 17391;
    }
    if (myLevel >= 44)
    {
        spell_Thorns = 9756;
        spell_Barkskin = 22812;
        spell_Swipe = 9754;
    }
    if (myLevel >= 46)
    {
        spell_Wrath = 8905;
        spell_Moonfire = 9833;
        spell_Bash = 8983;
    }
    if (myLevel >= 48)
    {
        spell_EntanglingRoots = 9852;
        spell_Revive = 50766;
    }
    if (myLevel >= 50)
    {
        spell_InsectSwarm = 24976;
        spell_Typhoon = 50516;
        spell_Rebirth = 20747;
        spell_Hurricane = 17401;
        spell_Starfire = 9875;
        spell_Gift_Of_The_Wild = 21849;
        spell_Mark_Of_The_Wild = 9884;
        spell_Maul = 9880;
    }
    if (myLevel >= 51)
    {
        spell_Force_Of_Nature = 33831;
    }
    if (myLevel >= 52)
    {
        spell_Moonfire = 9834;
        spell_DemoralizingRoar = 9898;
    }
    if (myLevel >= 54)
    {
        spell_Wrath = 9912;
        spell_Thorns = 9910;
        spell_Swipe = 9908;
        spell_Faerie_Fire_Feral = 17392;
    }
    if (myLevel >= 58)
    {
        spell_EntanglingRoots = 9853;
        spell_Starfire = 9876;
        spell_Hibernate = 18658;
        spell_Moonfire = 9835;
        spell_Maul = 9881;
    }
    if (myLevel >= 60)
    {
        spell_InsectSwarm = 24977;
        spell_Typhoon = 53223;
        spell_Starfall = 48505;
        spell_Rebirth = 20748;
        spell_Hurricane = 17402;
        spell_Revive = 50765;
        spell_Starfire = 25298;
        spell_Gift_Of_The_Wild = 21850;
        spell_Mark_Of_The_Wild = 9885;
    }
    if (myLevel >= 61)
    {
        spell_Wrath = 26984;
    }
    if (myLevel >= 63)
    {
        spell_Moonfire = 26987;
    }
    if (myLevel >= 64)
    {
        spell_Thorns = 26992;
    }
    if (myLevel >= 65)
    {

    }
    if (myLevel >= 66)
    {

    }
    if (myLevel >= 67)
    {
        spell_Starfire = 26986;
    }
    if (myLevel >= 68)
    {
        spell_EntanglingRoots = 26989;
    }
    if (myLevel >= 69)
    {
        spell_Wrath = 26985;
        spell_Rebirth = 26994;
        spell_Revive = 50764;
    }
    if (myLevel >= 70)
    {
        spell_Typhoon = 53225;
        spell_Starfall = 53199;
        spell_Hurricane = 27012;
        spell_Gift_Of_The_Wild = 26991;
        spell_Mark_Of_The_Wild = 26990;
        spell_Moonfire = 26988;
    }
    if (myLevel >= 71)
    {

    }
    if (myLevel >= 72)
    {
        spell_Starfire = 48464;
    }
    if (myLevel >= 73)
    {

    }
    if (myLevel >= 74)
    {
        spell_Wrath = 48459;
        spell_Thorns = 53307;
    }
    if (myLevel >= 75)
    {
        spell_Typhoon = 53226;
        spell_Starfall = 53200;
        spell_Moonfire = 48462;
    }
    if (myLevel >= 76)
    {

    }
    if (myLevel >= 77)
    {

    }
    if (myLevel >= 78)
    {
        spell_EntanglingRoots = 53308;
        spell_Starfire = 48465;
    }
    if (myLevel >= 79)
    {
        spell_Wrath = 48461;
        spell_Rebirth = 48477;
    }
    if (myLevel >= 80)
    {
        spell_InsectSwarm = 48468;
        spell_Typhoon = 61384;
        spell_Starfall = 53201;
        spell_Hurricane = 48467;
        spell_Revive = 50763;
        spell_Gift_Of_The_Wild = 48470;
        spell_Mark_Of_The_Wild = 48469;
        spell_Moonfire = 48463;
    }
    me->UpdateSkillsToMaxSkillsForLevel();
    std::ostringstream msgStream;
    msgStream << me->GetName() << " initialized";
    sWorld.SendServerMessage(ServerMessageType::SERVER_MSG_CUSTOM, msgStream.str().c_str());

    return true;
}

bool Nier_Druid::ResetTalentsAndSpells()
{
    if (!Nier_Base::ResetTalentsAndSpells())
    {
        return false;
    }

    // talent tab : 283 - balance 301 - feral 302 - restoration

    // 283
    LearnTalent(795);
    LearnTalent(799);
    LearnTalent(794);
    LearnTalent(798);
    LearnTalent(803);
    LearnTalent(801);
    LearnTalent(1162);
    LearnTalent(805);
    LearnTalent(808);
    LearnTalent(809);

    LearnTalent(797);
    LearnTalent(796);

    //LearnTalent(762);
    //LearnTalent(783);
    //LearnTalent(1822);
    //LearnTalent(789);
    //LearnTalent(764);
    //LearnTalent(792);
    //LearnTalent(788);
    //LearnTalent(2239);
    //LearnTalent(1782);
    //LearnTalent(1784);
    //LearnTalent(793);
    //LearnTalent(1912);
    //LearnTalent(1783);
    //LearnTalent(1785);
    //LearnTalent(2240);
    //LearnTalent(1923);
    //LearnTalent(1787);
    //LearnTalent(1925);
    //LearnTalent(790);
    //LearnTalent(1928);
    //LearnTalent(1926);

    //LearnTalent(1284);

    //LearnTalent(1924);
    //LearnTalent(1786);
    //LearnTalent(2238);
    //LearnTalent(763);
    //LearnTalent(784);

    // druid trainer Denatharion
    TrainSpells(4218);

    return true;
}

void Nier_Druid::EquipRandomItem(uint32 pEquipSlot)
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
        itemSubclass = 10;
        inventoryType = InventoryType::INVTYPE_2HWEAPON;
    }
    else if (pEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_OFFHAND)
    {
        inventoryType = 0;
    }
    else if (pEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_RANGED)
    {
        inventoryType = 0;
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
