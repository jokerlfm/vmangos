#ifndef NIER_ACTION_ROGUE_H
#define NIER_ACTION_ROGUE_H

#include "Nier_Base.h"

class Nier_Rogue :public Nier_Base
{
public:    
    Nier_Rogue(Player* pmMe);
    void InitializeCharacter(uint32 pmTargetLevel, uint32 pmSpecialtyTabIndex);
    void ResetTalent();
    bool InitializeEquipments(bool pmReset);
    void Update(uint32 pmDiff);
    void Prepare();
    bool Attack(Unit* pmTarget);
    bool Interrupt(Unit* pmTarget);
    bool DPS(Unit* pmTarget, bool pmRushing, bool pmChasing, float pmDistanceMax = DEFAULT_COMBAT_REACH, float pmDistanceMin = CONTACT_DISTANCE);
    bool Buff(Unit* pmTarget);
    uint32 Caution();

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
