#include "Nier_Warrior.h"
#include "Player.h"
#include "Group.h"
#include "Spell.h"
#include "World.h"

Nier_Warrior::Nier_Warrior(Player* pmMe) :Nier_Base(pmMe)
{
	ogVigilanceTarget = ObjectGuid();

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

	spellDelay_DemoralizingShout = DEFAULT_WARRIOR_SPELL_DELAY;
	spellDelay_BattleShout = DEFAULT_WARRIOR_SPELL_DELAY;
	spellDelay_Revenge = 0;
}

void Nier_Warrior::Update(uint32 pmDiff)
{
	if (spellDelay_DemoralizingShout >= 0)
	{
		spellDelay_DemoralizingShout -= pmDiff;
	}
	if (spellDelay_BattleShout >= 0)
	{
		spellDelay_BattleShout -= pmDiff;
	}
	if (spellDelay_Revenge >= 0)
	{
		spellDelay_Revenge -= pmDiff;
	}
	Nier_Base::Update(pmDiff);
}

void Nier_Warrior::InitializeCharacter(uint32 pmTargetLevel, uint32 pmSpecialtyTabIndex)
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
}

void Nier_Warrior::ResetTalent()
{
	if (!me)
	{
		return;
	}
	me->ResetTalents(true);

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
}

bool Nier_Warrior::InitializeEquipments(bool pmReset)
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
		int modType = ItemModType::ITEM_MOD_STRENGTH;
		uint32 equipItemClass = 0;
		uint32 equipItemSubClass = 0;
		uint32 armorSubClass = 3;
		if (myLevel < 40)
		{
			armorSubClass = 3;
		}
		else
		{
			armorSubClass = 4;
		}
		if (checkEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_HEAD)
		{
			equipItemClass = 4;
			equipItemSubClass = armorSubClass;
		}
		else if (checkEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_SHOULDERS)
		{
			equipItemClass = 4;
			equipItemSubClass = armorSubClass;
		}
		else if (checkEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_WRISTS)
		{
			equipItemClass = 4;
			equipItemSubClass = armorSubClass;
		}
		else if (checkEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_WAIST)
		{
			equipItemClass = 4;
			equipItemSubClass = armorSubClass;
		}
		else if (checkEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_FEET)
		{
			equipItemClass = 4;
			equipItemSubClass = armorSubClass;
		}
		else if (checkEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_HANDS)
		{
			equipItemClass = 4;
			equipItemSubClass = armorSubClass;
		}
		else if (checkEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_CHEST)
		{
			equipItemClass = 4;
			equipItemSubClass = armorSubClass;
		}
		else if (checkEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_LEGS)
		{
			equipItemClass = 4;
			equipItemSubClass = armorSubClass;
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
			equipItemSubClass = 7;
			inventoryTypeSet.insert(InventoryType::INVTYPE_WEAPON);
			inventoryTypeSet.insert(InventoryType::INVTYPE_WEAPONMAINHAND);
		}
		else if (checkEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_OFFHAND)
		{
			equipItemClass = 4;
			equipItemSubClass = 6;
			inventoryTypeSet.insert(InventoryType::INVTYPE_SHIELD);
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

void Nier_Warrior::Prepare()
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

bool Nier_Warrior::Tank(Unit* pmTarget, bool aoe)
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
	if (!nm->Tank(pmTarget))
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
	bool canMelee = me->CanReachWithMeleeAutoAttack(pmTarget);
	float myHealthPCT = me->GetHealthPercent();
	if (targetDistance < NIER_NORMAL_DISTANCE)
	{
		if (spell_HeroicThrow > 0)
		{
			if (CastSpell(pmTarget, spell_HeroicThrow))
			{
				return true;
			}
		}
		if (myHealthPCT < 20.0f)
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
	}
	uint32 myRage = me->GetPower(Powers::POWER_RAGE);
	if (targetDistance < NIER_FAR_DISTANCE)
	{
		if (myRage < 100)
		{
			if (CastSpell(me, spell_Bloodrage))
			{
				return true;
			}
		}
		if (!pmTarget->GetTargetGuid().IsEmpty())
		{
			if (pmTarget->GetTargetGuid() != me->GetObjectGuid())
			{
				if (targetDistance > NIER_NORMAL_DISTANCE)
				{
					if (spell_Warbringer > 0)
					{
						if (CastSpell(pmTarget, spell_Charge))
						{
							nm->moveCheckDelay = 1000;
							return true;
						}
						if (CastSpell(pmTarget, spell_intercept))
						{
							nm->moveCheckDelay = 1000;
							return true;
						}
						if (spell_Intervene > 0)
						{
							if (CastSpell(pmTarget, spell_Intervene))
							{
								nm->moveCheckDelay = 1000;
								return true;
							}
						}
					}
				}
				if (canMelee)
				{
					if (me->GetHealthPercent() < 30.0f)
					{
						HealthPotion();
					}
					if (spell_Taunt > 0)
					{
						if (CastSpell(pmTarget, spell_Taunt))
						{
							return true;
						}
					}
					if (spell_MockingBlow > 0)
					{
						if (CastSpell(pmTarget, spell_MockingBlow))
						{
							return true;
						}
					}
				}
				if (spell_ChallengingShout > 0)
				{
					if (CastSpell(pmTarget, spell_ChallengingShout))
					{
						return true;
					}
				}
			}
		}
		if (spell_DemoralizingShout > 0)
		{
			if (spellDelay_DemoralizingShout < 0)
			{
				if (targetDistance < INTERACTION_DISTANCE)
				{
					if (CastSpell(pmTarget, spell_DemoralizingShout, true))
					{
						spellDelay_DemoralizingShout = DEFAULT_WARRIOR_SPELL_DELAY;
						return true;
					}
				}
			}
		}
	}
	if (canMelee)
	{
		if (spell_ThunderClap > 0)
		{
			if (CastSpell(pmTarget, spell_ThunderClap))
			{
				return true;
			}
		}
		if (pmTarget->IsNonMeleeSpellCasted(false, false, true))
		{
			if (spell_ShieldBash > 0)
			{
				if (CastSpell(pmTarget, spell_ShieldBash))
				{
					return true;
				}
			}
			if (spell_ConcussionBlow > 0)
			{
				if (CastSpell(pmTarget, spell_ConcussionBlow))
				{
					return true;
				}
			}
		}
		if (spell_ShieldBlock > 0)
		{
			if (CastSpell(me, spell_ShieldBlock))
			{
				return true;
			}
		}
		if (spell_BattleShout > 0)
		{
			if (spellDelay_BattleShout < 0)
			{
				if (CastSpell(nullptr, spell_BattleShout, true))
				{
					spellDelay_BattleShout = DEFAULT_WARRIOR_SPELL_DELAY;
					return true;
				}
			}
		}
		if (spell_BerserkerRage > 0)
		{
			if (CastSpell(pmTarget, spell_BerserkerRage))
			{
				return true;
			}
		}
		if (spell_Bloodthirst > 0)
		{
			if (CastSpell(pmTarget, spell_Bloodthirst))
			{
				return true;
			}
		}
		if (aoe)
		{
			if (spell_Shockwave > 0)
			{
				if (CastSpell(me, spell_Shockwave))
				{
					return true;
				}
			}
		}
		if (spell_ShieldSlam > 0)
		{
			if (CastSpell(pmTarget, spell_ShieldSlam))
			{
				return true;
			}
		}
		if (spell_Revenge > 0)
		{
			if (spellDelay_Revenge < 0)
			{
				if (CastSpell(pmTarget, spell_Revenge))
				{
					spellDelay_Revenge = 10000;
					return true;
				}
			}
		}
		if (spell_Rend > 0)
		{
			if (CastSpell(pmTarget, spell_Rend, true, true))
			{
				return true;
			}
		}
		if (spell_Devastate > 0)
		{
			if (CastSpell(pmTarget, spell_Devastate, true, true, false, 5))
			{
				return true;
			}
		}
		if (spell_SunderArmor > 0)
		{
			if (CastSpell(pmTarget, spell_SunderArmor, true, true, false, 5))
			{
				return true;
			}
		}
		if (myRage > 400)
		{
			if (spell_Disarm > 0)
			{
				if (pmTarget->GetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_DISPLAY))
				{
					if (CastSpell(pmTarget, spell_Disarm))
					{
						return true;
					}
				}
			}
			if (spell_HeroicStrike > 0)
			{
				if (CastSpell(pmTarget, spell_HeroicStrike))
				{
					return true;
				}
			}
		}
	}

	return true;
}

bool Nier_Warrior::Buff(Unit* pmTarget)
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
		if (spell_DefensiveStance > 0)
		{
			if (CastSpell(me, spell_DefensiveStance, true))
			{
				return true;
			}
		}
		if (spell_Vigilance > 0)
		{
			if (ogVigilanceTarget.IsEmpty())
			{
				if (Group* myGroup = me->GetGroup())
				{
					for (GroupReference* groupRef = myGroup->GetFirstMember(); groupRef != nullptr; groupRef = groupRef->next())
					{
						if (Player* member = groupRef->getSource())
						{
							if (member->GetObjectGuid() != me->GetObjectGuid())
							{
								if (member->groupRole == GroupRole::GroupRole_Healer)
								{
									ogVigilanceTarget = member->GetObjectGuid();
									break;
								}
							}
						}
					}
				}
			}
			if (Player* healer = ObjectAccessor::FindPlayer(ogVigilanceTarget))
			{
				if (healer->IsInWorld())
				{
					if (healer->IsInSameGroupWith(me))
					{
						if (CastSpell(healer, spell_Vigilance, true))
						{
							return true;
						}
					}
					else
					{
						ogVigilanceTarget = ObjectGuid();
					}
				}
				else
				{
					ogVigilanceTarget = ObjectGuid();
				}
			}
			else
			{
				ogVigilanceTarget = ObjectGuid();
			}
		}
	}

	return false;
}
