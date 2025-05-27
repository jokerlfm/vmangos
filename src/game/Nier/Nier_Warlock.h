#ifndef NIER_WARLOCK_H
#define NIER_WARLOCK_H

#include "Nier_Base.h"

class Nier_Warlock :public Nier_Base
{
public:
    Nier_Warlock();
    bool Attack(Unit* pTarget);
    bool Tank(Unit* pTarget);
    bool Heal(Unit* pTarget);
    bool Cure(Unit* pTarget);
    bool Buff(Unit* pTarget);
    bool Revive(Unit* pTarget);
    bool InitializeCharacter(uint32 pTargetLevel);
    bool ResetTalentsAndSpells();
    void EquipRandomItem(uint32 pEquipSlot);
    void Prepare();

    uint32 spell_Shoot;
    uint32 spell_Immolate;
    uint32 spell_ShadowBolt;
    uint32 spell_SummonImp;
    uint32 spell_Nightfall;
    uint32 spell_Corruption;
    uint32 spell_CurseOfWeakness;
    uint32 spell_LifeTap;
    uint32 spell_DrainLife;

    uint32 spell_AmplifyCurse;
    uint32 spell_DemonArmor;

    std::unordered_set<uint32> petSpellBooksItemIdSet;
};
#endif
