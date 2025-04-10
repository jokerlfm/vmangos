#include "Nier_Rogue.h"
#include "Player.h"
#include "Group.h"
#include "Spell.h"
#include "World.h"

Nier_Rogue::Nier_Rogue(Player* pmMe) :Nier_Base(pmMe)
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

void Nier_Rogue::InitializeCharacter(uint32 pmTargetLevel, uint32 pmSpecialtyTabIndex)
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
	spell_Stealth = 1784;
	spell_SinisterStrike = 1752;
	spell_Eviscerate = 2098;
	me->LearnSpell(1180, false);
	me->LearnSpell(15590, false);
	me->LearnSpell(2567, false);
	item_SlowPoison = 3775;
	if (myLevel >= 4)
	{
		spell_Backstab = 53;
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
		spell_Backstab = 2589;
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
		spell_Backstab = 2590;
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
		spell_CheapShot = 1833;
	}
	if (myLevel >= 28)
	{
		spell_Backstab = 2591;
		item_InstantPoison = 6949;
		spell_Sap = 2070;
		spell_Feint = 6768;
	}
	if (myLevel >= 29)
	{
		spell_Riposte = 14251;
	}
	if (myLevel >= 30)
	{
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
		spell_Backstab = 8721;
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
		spell_Backstab = 11279;
		item_InstantPoison = 8926;
	}
	if (myLevel >= 45)
	{
		spell_BladeFlurry = 13877;
	}
	if (myLevel >= 46)
	{
		spell_SinisterStrike = 11293;
	}
	if (myLevel >= 48)
	{
		spell_Eviscerate = 11299;
		spell_Sap = 11297;
		spell_AdrenalineRush = 13750;
	}
	if (myLevel >= 50)
	{
		spell_Evasion = 26669;
		spell_KidneyShot = 8643;
	}
	if (myLevel >= 52)
	{
		spell_Backstab = 11280;
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
		spell_Backstab = 11281;
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
}

void Nier_Rogue::ResetTalent()
{
	if (!me)
	{
		return;
	}
	me->ResetTalents(true);

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
}

bool Nier_Rogue::InitializeEquipments(bool pmReset)
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
		uint32 modType = ItemModType::ITEM_MOD_AGILITY;
		uint32 equipItemClass = 0;
		uint32 equipItemSubClass = 0;
		if (checkEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_HEAD)
		{
			equipItemClass = 4;
			equipItemSubClass = 2;
		}
		else if (checkEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_SHOULDERS)
		{
			equipItemClass = 4;
			equipItemSubClass = 2;
		}
		else if (checkEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_WRISTS)
		{
			equipItemClass = 4;
			equipItemSubClass = 2;
		}
		else if (checkEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_WAIST)
		{
			equipItemClass = 4;
			equipItemSubClass = 2;
		}
		else if (checkEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_FEET)
		{
			equipItemClass = 4;
			equipItemSubClass = 2;
		}
		else if (checkEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_HANDS)
		{
			equipItemClass = 4;
			equipItemSubClass = 2;
		}
		else if (checkEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_CHEST)
		{
			equipItemClass = 4;
			equipItemSubClass = 2;
		}
		else if (checkEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_LEGS)
		{
			equipItemClass = 4;
			equipItemSubClass = 2;
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
			equipItemSubClass = 15;
			inventoryTypeSet.insert(InventoryType::INVTYPE_WEAPON);
			inventoryTypeSet.insert(InventoryType::INVTYPE_WEAPONMAINHAND);
			modType = -1;
		}
		else if (checkEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_OFFHAND)
		{
			equipItemClass = 2;
			equipItemSubClass = 15;
			inventoryTypeSet.insert(InventoryType::INVTYPE_WEAPON);
			inventoryTypeSet.insert(InventoryType::INVTYPE_WEAPONOFFHAND);
			modType = -1;
		}
		else if (checkEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_RANGED)
		{
			equipItemClass = 2;
			equipItemSubClass = 16;
			inventoryTypeSet.insert(InventoryType::INVTYPE_THROWN);
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
		EquipRandomItem(checkEquipSlot, equipItemClass, equipItemSubClass, minQuality, modType, inventoryTypeSet);
	}

	return true;
}

void Nier_Rogue::Update(uint32 pmDiff)
{
	if (riposteDelay > 0)
	{
		riposteDelay -= pmDiff;
	}

	Nier_Base::Update(pmDiff);
}

void Nier_Rogue::Prepare()
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

bool Nier_Rogue::Attack(Unit* pmTarget)
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
	if (!nm->Chase(pmTarget, DEFAULT_COMBAT_REACH, 0.5f))
	{
		if (me->GetTargetGuid() == pmTarget->GetObjectGuid())
		{
			ClearTarget();
		}
		return false;
	}
	ChooseTarget(pmTarget);

	me->Attack(pmTarget, true);
	float targetDistance = me->GetDistance(pmTarget);
	if (targetDistance > NIER_NORMAL_DISTANCE)
	{
		if (CastSpell(me, spell_Sprint))
		{
			return true;
		}
	}
	uint32 myEnergy = me->GetPower(Powers::POWER_ENERGY);
	uint32 comboPoints = me->GetComboPoints();
	bool canMelee = me->CanReachWithMeleeAutoAttack(pmTarget);
	if (canMelee)
	{
		if (me->GetHealthPercent() < 30.0f)
		{
			HealthPotion();
		}
		if (pmTarget->GetTargetGuid() == me->GetObjectGuid())
		{
			if (CastSpell(me, spell_Evasion))
			{
				return true;
			}
			//if (!me->HasAura(spell_Evasion))
			//{
			//    if (CastSpell(me, spell_Vanish))
			//    {
			//        return true;
			//    }
			//}
		}
		me->Attack(pmTarget, true);
		if (pmTarget->GetTypeId() == TypeID::TYPEID_PLAYER)
		{
			if (spell_BladeFlurry > 0)
			{
				if (myEnergy >= 25)
				{
					if (CastSpell(me, spell_BladeFlurry))
					{
						return true;
					}
				}
			}
			if (spell_AdrenalineRush > 0)
			{
				if (CastSpell(me, spell_AdrenalineRush))
				{
					return true;
				}
			}
		}
		if (myEnergy >= 25)
		{
			if (pmTarget->IsNonMeleeSpellCasted(false, false, true))
			{
				if (spell_Kick > 0)
				{
					if (CastSpell(pmTarget, spell_Kick))
					{
						return true;
					}
				}
				if (comboPoints > 0)
				{
					if (spell_KidneyShot > 0)
					{
						if (CastSpell(pmTarget, spell_KidneyShot))
						{
							return true;
						}
					}
				}
			}
		}
		if (myEnergy >= 25)
		{
			if (!me->HasAura(spell_SliceandDice))
			{
				if (comboPoints > 0)
				{
					if (spell_SliceandDice > 0)
					{
						if (CastSpell(pmTarget, spell_SliceandDice))
						{
							return true;
						}
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
						if (CastSpell(pmTarget, spell_Eviscerate))
						{
							return true;
						}
					}
				}
			}
		}
		if (spell_Riposte > 0)
		{
			if (riposteDelay <= 0)
			{
				if (myEnergy >= 10)
				{
					if (CastSpell(pmTarget, spell_Riposte))
					{
						riposteDelay = 10000;
						return true;
					}
				}
			}
		}
		if (myEnergy >= 45)
		{
			if (CastSpell(pmTarget, spell_SinisterStrike))
			{
				return true;
			}
		}
	}

	return true;
}

bool Nier_Rogue::DPS(Unit* pmTarget, bool pmRushing, bool pmChasing, float pmDistanceMax, float pmDistanceMin)
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
	me->Attack(pmTarget, true);
	float targetDistance = me->GetDistance(pmTarget);
	if (targetDistance > NIER_NORMAL_DISTANCE)
	{
		if (CastSpell(me, spell_Sprint))
		{
			return true;
		}
	}
	uint32 myEnergy = me->GetPower(Powers::POWER_ENERGY);
	uint32 comboPoints = me->GetComboPoints();
	bool canMelee = me->CanReachWithMeleeAutoAttack(pmTarget);
	if (canMelee)
	{
		if (me->GetHealthPercent() < 30.0f)
		{
			HealthPotion();
		}
		if (pmTarget->GetTargetGuid() == me->GetObjectGuid())
		{
			if (spell_Evasion > 0)
			{
				if (CastSpell(me, spell_Evasion))
				{
					return true;
				}
				//if (!me->HasAura(spell_Evasion))
				//{
				//    if (CastSpell(me, spell_Vanish))
				//    {
				//        return true;
				//    }
				//}
			}
		}
		else
		{
			me->Attack(pmTarget, true);
			if (pmTarget->GetTypeId() != TypeID::TYPEID_PLAYER)
			{
				if (myEnergy >= 20)
				{
					if (spell_Feint > 0)
					{
						if (CastSpell(pmTarget, spell_Feint))
						{
							return true;
						}
					}
				}
			}
			if (pmRushing)
			{
				if (myEnergy >= 25)
				{
					if (spell_BladeFlurry > 0)
					{
						if (CastSpell(me, spell_BladeFlurry))
						{
							return true;
						}
					}
				}
				if (spell_AdrenalineRush > 0)
				{
					if (CastSpell(me, spell_AdrenalineRush))
					{
						return true;
					}
				}
			}
			if (myEnergy >= 25)
			{
				if (!me->HasAura(spell_SliceandDice))
				{
					if (comboPoints > 0)
					{
						if (spell_SliceandDice > 0)
						{
							if (CastSpell(pmTarget, spell_SliceandDice))
							{
								return true;
							}
						}
					}
				}
				else
				{
					if (comboPoints > 0)
					{
						if (spell_Eviscerate > 0)
						{
							uint32 finishRate = urand(1, 4);
							if (comboPoints > finishRate)
							{
								if (CastSpell(pmTarget, spell_Eviscerate))
								{
									return true;
								}
							}
						}
					}
				}
			}
			if (myEnergy >= 45)
			{
				if (CastSpell(pmTarget, spell_SinisterStrike))
				{
					return true;
				}
			}
		}
	}

	return true;
}

bool Nier_Rogue::Interrupt(Unit* pmTarget)
{
	if (me->CanReachWithMeleeAutoAttack(pmTarget))
	{
		uint32 myEnergy = me->GetPower(Powers::POWER_ENERGY);
		uint32 comboPoints = me->GetComboPoints();
		if (myEnergy >= 25)
		{
			if (spell_Kick > 0)
			{
				if (CastSpell(pmTarget, spell_Kick))
				{
					return true;
				}
			}
			if (comboPoints > 0)
			{
				if (spell_KidneyShot > 0)
				{
					if (CastSpell(pmTarget, spell_KidneyShot))
					{
						return true;
					}
				}
			}
		}
	}
	return false;
}

bool Nier_Rogue::Buff(Unit* pmTarget)
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
		if (item_InstantPoison > 0)
		{
			if (!me->HasItemCount(item_InstantPoison, 1))
			{
				me->StoreNewItemInBestSlots(item_InstantPoison, 20);
			}
			if (Item* poison = GetItemInInventory(item_InstantPoison))
			{
				if (Item* oWeapon = me->GetItemByPos(INVENTORY_SLOT_BAG_0, EquipmentSlots::EQUIPMENT_SLOT_OFFHAND))
				{
					if (oWeapon->GetEnchantmentId(EnchantmentSlot::TEMP_ENCHANTMENT_SLOT) == 0)
					{
						if (UseItem(poison, oWeapon))
						{
							return true;
						}
					}
				}
			}
		}
		if (item_SlowPoison > 0)
		{
			if (!me->HasItemCount(item_SlowPoison, 1))
			{
				me->StoreNewItemInBestSlots(item_SlowPoison, 20);
			}
			if (Item* poison = GetItemInInventory(item_SlowPoison))
			{
				if (Item* mWeapon = me->GetItemByPos(INVENTORY_SLOT_BAG_0, EquipmentSlots::EQUIPMENT_SLOT_MAINHAND))
				{
					if (mWeapon->GetEnchantmentId(EnchantmentSlot::TEMP_ENCHANTMENT_SLOT) == 0)
					{
						if (UseItem(poison, mWeapon))
						{
							return true;
						}
					}
				}
			}
		}
		//if (!me->GetGroup())
		//{
		//    if (CastSpell(me, spell_Stealth, true))
		//    {
		//        return true;
		//    }
		//}
	}

	return false;
}

uint32 Nier_Rogue::Caution()
{
	uint32 result = Nier_Base::Caution();
	if (result > 0)
	{
		if (spell_Sprint > 0)
		{
			CastSpell(me, spell_Sprint);
		}
	}

	return result;
}
