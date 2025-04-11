#ifndef NIER_ACTION_PRIEST_H
#define NIER_ACTION_PRIEST_H

#include "Nier_Base.h"

class Nier_Priest :public Nier_Base
{
public:
    Nier_Priest();
    void InitializeCharacter(uint32 pmTargetLevel, uint32 pmSpecialtyTabIndex);
    void ResetTalent();
    bool InitializeEquipments(bool pmReset);
    void Prepare();
    bool Heal(Unit* pmTarget, bool pmInstantOnly);
    bool ReadyTank(Unit* pmTarget);
    bool GroupHeal(Unit* pmTarget, bool pmInstantOnly);
    bool SimpleHeal(Unit* pmTarget, bool pmInstantOnly);
    bool Cure(Unit* pmTarget);
    bool Buff(Unit* pmTarget);
    bool Revive(Player* pmTarget);

    bool Heal_Discipline(Unit* pmTarget, bool pmInstantOnly);
    bool Heal_Holy(Unit* pmTarget, bool pmInstantOnly);
private:
    uint32 spell_Renew;
    uint32 spell_LesserHeal;
    uint32 spell_Heal;
    uint32 spell_GreaterHeal;
    uint32 spell_FlashHeal;
    uint32 spell_Resurrection;
    uint32 spell_CureDisease;
    uint32 spell_DispelMagic;
    uint32 spell_DivineSpirit;
    uint32 spell_PowerWord_Fortitude;
    uint32 spell_PowerWord_Shield;
    uint32 spell_Penance;
    uint32 spell_Weakened_Soul;
    uint32 spell_Prayer_of_Healing;
    uint32 spell_Prayer_of_Spirit;
    uint32 spell_Prayer_of_Fortitude;
    uint32 spell_InnerFocus;
    uint32 spell_PowerInfusion;
    uint32 spell_PainSuppression;
    uint32 spell_DesperatePrayer;
    uint32 spell_HolyNova;
    uint32 aura_Surge_of_Light;
};
#endif
