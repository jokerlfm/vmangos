#ifndef NIER_ROGUE_H
#define NIER_ROGUE_H

#include "Nier_Base.h"

class Nier_Base;

class Nier_Rogue :public Nier_Base
{
public:
    Nier_Rogue();
    bool Attack(Unit* pTarget);
    bool Tank(Unit* pTarget);
    bool Heal(Unit* pTarget);
    bool Cure(Unit* pTarget);
    bool Buff(Unit* pTarget);
    bool Revive(Unit* pTarget);
    bool InitializeCharacter(uint32 pTargetLevel);
    bool ResetTalentsAndSpells();
    void EquipRandomItem(uint32 pEquipSlot);

public:
    uint32 spell_Dismantle;
    uint32 spell_Backstab;
    uint32 spell_Eviscerate;
    uint32 spell_FanofKnives;
    uint32 spell_Sprint;
    uint32 spell_TricksoftheTrade;
    uint32 spell_Kick;
    uint32 spell_Sap;
    uint32 spell_Stealth;
    uint32 spell_SliceandDice;
    uint32 spell_Evasion;
    uint32 spell_KidneyShot;
    uint32 spell_CheapShot;
    uint32 spell_Vanish;
    uint32 spell_Feint;
    uint32 spell_SinisterStrike;
    uint32 spell_DeadlyThrow;

    uint32 spell_BladeFlurry;
    uint32 spell_AdrenalineRush;

    uint32 spell_Riposte;

    uint32 item_InstantPoison;
    uint32 item_SlowPoison;

    int riposteDelay;
};
#endif
