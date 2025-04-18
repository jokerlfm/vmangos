#ifndef NIER_ACTION_BASE_H
#define NIER_ACTION_BASE_H

#ifndef DEFAULT_ACTION_LIMIT_DELAY
#define DEFAULT_ACTION_LIMIT_DELAY 5000
#endif

#ifndef DEFAULT_MOVEMENT_UPDATE_DELAY
#define DEFAULT_MOVEMENT_UPDATE_DELAY 100
#endif

#ifndef DEFAULT_MOVEMENT_CHECK_DELAY
#define DEFAULT_MOVEMENT_CHECK_DELAY 500
#endif

#include "Nier/NierConfig.h"
#include "Nier/NierManager.h"
#include "MotionMaster.h"
#include "Item.h"
#include "Player.h"
#include "Group.h"
#include "Spell.h"
#include "SpellAuras.h"
#include "SpellMgr.h"
#include "Map.h"

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
};

enum NierGroupRole :uint32
{
    NierGroupRole_DPS = 0,
    NierGroupRole_Tank,
    NierGroupRole_Healer
};

class NierActionTarget
{
public:
    NierActionTarget();
    void Reset();

public:
    uint32 duration;
    uint32 timeLimit;

    Unit* targetUnit;
    Position targetPos;
};

class Nier_Base
{
public:
    Nier_Base();
    virtual void Reset();
    virtual void Prepare();
    virtual void Update(uint32 pDiff);
    virtual bool UpdateNierAccount(uint32 pElapsed);
    virtual bool UpdateNierAction(uint32 pElapsed);
    virtual bool UpdateNierAwareness(uint32 pElapsed);
    virtual bool Attack(Unit* pTarget);
    virtual bool Interrupt(Unit* pmTarget);
    virtual bool DPS(Unit* pmTarget, bool pmRushing, bool pmChasing, float pmDistanceMax = DEFAULT_COMBAT_REACH, float pmDistanceMin = CONTACT_DISTANCE);
    virtual bool Tank(Unit* pTarget);
    virtual bool Heal(Unit* pmTarget, bool pmInstantOnly);
    virtual bool Follow(Unit* pmFollowTarget, float pmDistance);
    virtual bool ReadyTank(Unit* pmTarget);
    virtual bool GroupHeal(Unit* pmTarget, bool pmInstantOnly);
    virtual bool SimpleHeal(Unit* pmTarget, bool pmInstantOnly);
    virtual bool Cure(Unit* pmTarget);
    virtual bool Buff(Unit* pmTarget);
    virtual bool Mark(Unit* pmTarget, int pmRTI);
    virtual bool Assist(int pmRTI);
    virtual bool Revive(Unit* pTarget);
    virtual bool Petting(bool pmSummon = true, bool pmReset = false);
    virtual void InitializeCharacter(uint32 pTargetLevel);
    virtual void ResetTalentsAndSpells();
    virtual bool InitializeEquipments(bool pmReset = false);

    bool Idle();
    bool Wander();
    bool PVE();
    bool PVP();
    void RemoveEquipments();
    void LearnTalent(uint32 pmTalentId, uint32 pmMaxRank = MAX_TALENT_RANK);
    void TrainSpells(uint32 pmTrainerEntry);
    void EquipRandomItem(uint32 pmEquipSlot, uint32 pmClass, uint32 pmSubclass, uint32 pmMinQuality, int pmModType, std::unordered_set<uint32> pmInventoryTypeSet = std::unordered_set<uint32>());
    void PetAttack(Unit* pmTarget);
    void PetStop();
    bool UseItem(Item* pmItem, Unit* pmTarget);
    bool UseItem(Item* pmItem, Item* pmTarget);
    bool CastSpell(Unit* pmTarget, uint32 pmSpellId, bool pmCheckAura = false, bool pmOnlyMyAura = false, bool pmClearShapeShift = false, uint32 pmMaxAuraStack = 1);
    void CancelAura(uint32 pmSpellID);
    bool Rest();
    bool Eat();
    bool Drink();
    bool HealthPotion();
    bool ManaPotion();

    void ChooseTarget(Unit* pmTarget);
    void ClearTarget();
    bool SpellValid(uint32 pmSpellID);
    Item* GetItemInInventory(uint32 pmEntry);

    int checkDelay;
    int elapsed;

    Player* me;
    NierActionTarget* actionTarget;
    bool isRobot;

    uint32 specialty;
    uint32 accountState;
    uint32 actionState;

    uint32 nier_id;
    uint32 master_id;
    uint32 account_id;
    std::string account_name;
    uint32 character_id;
    uint32 target_level;
    uint32 target_race;
    uint32 target_class;
    uint32 target_specialty;

    uint32 groupRole;

    int assembleDelay;
};

#endif
