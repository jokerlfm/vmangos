#ifndef NIER_WARRIOR_H
#define NIER_WARRIOR_H

#ifndef DEFAULT_WARRIOR_SPELL_DELAY
#define DEFAULT_WARRIOR_SPELL_DELAY 20000
#endif

#include "Nier_Base.h"

class Nier_Base;

class Nier_Warrior :public Nier_Base
{
public:
    Nier_Warrior();
    bool Attack(Unit* pTarget);
    bool Tank(Unit* pTarget);
    bool Heal(Unit* pTarget);
    bool Cure(Unit* pTarget);
    bool Buff(Unit* pTarget);
    bool Revive(Unit* pTarget);
    bool InitializeCharacter(uint32 pTargetLevel);
    bool ResetTalentsAndSpells();
    void EquipRandomItem(uint32 pEquipSlot);

private:
    uint32 spell_DefensiveStance;
    uint32 spell_Taunt;
    uint32 spell_MockingBlow;
    uint32 spell_PiercingHowl;
    uint32 spell_DemoralizingShout;
    uint32 spell_ShieldBash;
    uint32 spell_ShieldBlock;
    uint32 spell_ShieldSlam;
    uint32 spell_ShieldWall;
    uint32 spell_Revenge;
    uint32 spell_Devastate;
    uint32 spell_Disarm;
    uint32 spell_Vigilance;
    uint32 spell_BerserkerRage;
    uint32 spell_ThunderClap;
    uint32 spell_LastStand;
    uint32 spell_SunderArmor;
    uint32 spell_Bloodthirst;
    uint32 spell_Cleave;
    uint32 spell_Rend;
    uint32 spell_Bloodrage;
    uint32 spell_HeroicStrike;
    uint32 spell_HeroicThrow;
    uint32 spell_intercept;
    uint32 spell_Intervene;
    uint32 spell_BattleShout;
    uint32 spell_Shockwave;
    uint32 spell_ConcussionBlow;
    uint32 spell_ChallengingShout;
    uint32 spell_Warbringer;
    uint32 spell_Charge;

    int spellDelay_DemoralizingShout;
    int spellDelay_BattleShout;
    int spellDelay_Revenge;
};
#endif
