#ifndef NIER_BASE_H
#define NIER_BASE_H

enum NierAccountState :uint32
{
    NierAccountState_None = 0,
    NierAccountState_OffLine,
    NierAccountState_Enter,
    NierAccountState_CheckAccount,
    NierAccountState_CreateAccount,
    NierAccountState_CheckCharacter,
    NierAccountState_CreateCharacter,
    NierAccountState_CheckLogin,
    NierAccountState_DoLogin,
    NierAccountState_DoEnum,
    NierAccountState_CheckEnum,
    NierAccountState_Initialize,
    NierAccountState_Equip,
    NierAccountState_Online,
    NierAccountState_Exit,
    NierAccountState_CheckLogoff,
    NierAccountState_DoLogoff,
    NierAccountState_RedoLogin,
    NierAccountState_CheckRedoLogin,
};

enum NierActionState :uint32
{
    NierActionState_None = 0,
    NierActionState_Idle,
    NierActionState_Wander,
    NierActionState_Follow,
    NierActionState_Tank,
    NierActionState_Attack,
    NierActionState_Heal,
    NierActionState_Cast,
    NierActionState_Assist,
    NierActionState_Rest,
    NierActionState_Freeze,
    NierActionState_Assemble,
    NierActionState_Bunch,
    NierActionState_Revive,
    NierActionState_Corpse,
};

enum NierGroupRole :uint32
{
    NierGroupRole_DPS = 0,
    NierGroupRole_Tank,
    NierGroupRole_Healer
};

class Nier_Base
{
public:
    Nier_Base();
    virtual bool Attack(Unit* pTarget);
    virtual bool Tank(Unit* pTarget);
    virtual bool Heal(Unit* pTarget);
    virtual bool Cure(Unit* pTarget);
    virtual bool Buff(Unit* pTarget);
    virtual bool Revive(Unit* pTarget);
    virtual bool InitializeCharacter(uint32 pTargetLevel);
    virtual bool ResetTalentsAndSpells();
    virtual void EquipRandomItem(uint32 pEquipSlot);

    void Prepare();
    void Update(uint64 pTimeValue);
    bool UpdateAccount();
    bool UpdateAction();
    bool UpdateMind();

    bool Idle();
    bool Wander();
    bool PVE();
    bool PVP();
    bool Follow();
    bool Chase(Unit* pTarget, float pDistance = CONTACT_DISTANCE);

    void RemoveEquipments();
    void EquipOne(uint32 pEquipSlot, uint32 pItemClass, uint32 pItemSubclass, uint32 pInventoryType, uint32 pMinReqLevel, uint32 pMaxReqLevel);
    void LearnTalent(uint32 pTalentId, uint32 pMaxRank = MAX_TALENT_RANK);
    void TrainSpells(uint32 pTrainerEntry);
    void PetAttack(Unit* pmTarget);
    void PetStop();
    bool UseItem(Item* pItem, Unit* pTarget);
    bool UseItem(Item* pItem, Item* pTarget);
    bool CastSpell(Unit* pmTarget, uint32 pmSpellId, bool pmCheckAura = false, bool pmOnlyMyAura = false, bool pmClearShapeShift = false, uint32 pmMaxAuraStack = 1);
    void CancelAura(uint32 pmSpellID);
    bool Rest();
    bool Eat();
    bool Drink();
    bool HealthPotion();
    bool ManaPotion();
    void MoveToPosition(Position pTargetpos, bool pRun = true);

    void ChooseTarget(Unit* pTarget);
    void ClearTarget();
    void ClearAction();
    bool SpellValid(uint32 pSpellID);
    Item* GetItemInInventory(uint32 pmEntry);
    Player* GetNearbyHostilePlayer();
    Unit* GetNearbyHostileUnit();

    Player* me;

    uint32 actionDuration;
    uint32 actionTimeLimit;
    Unit* actionTargetUnit;
    Position actionTargetPos;
    uint32 actionTargetSpell;

    float followDistance;

    uint32 specialty;
    uint32 accountState;
    uint32 actionState;

    uint32 nier_id;
    uint32 master_character_id;
    uint32 account_id;
    std::string account_name;
    uint32 character_id;
    uint32 target_level;
    uint32 target_race;
    uint32 target_class;
    uint32 target_specialty;

    uint64 timeValue;    
    int checkDelay;

};
#endif
