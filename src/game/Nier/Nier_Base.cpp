#include "Nier_Base.h"
#include "World.h"
#include "Group.h"
#include "Player.h"
#include "Pet.h"
#include "CreatureAI.h"
#include "Spell.h"
#include "GridNotifiers.h"
#include "Map.h"
#include "SpellMgr.h"
#include "SpellAuras.h"
#include "Bag.h"
#include "TargetedMovementGenerator.h"
#include "AccountMgr.h"

NierActionTarget::NierActionTarget()
{
    duration = 0;
    timeLimit = 0;
    targetUnit = nullptr;
}

void NierActionTarget::Reset()
{
    duration = 0;
    timeLimit = 0;
    targetUnit = nullptr;    
}

Nier_Base::Nier_Base()
{
    checkDelay = 5 * IN_MILLISECONDS;

    nier_id = 0;
    master_id = 0;
    account_id = 0;
    account_name = "";
    character_id = 0;
    target_level = 0;
    target_specialty = 0;
    elapsed = 0;

    me = nullptr;
    actionTarget = new NierActionTarget();
    isRobot = false;
    specialty = 0;
    accountState = NierAccountState::NierAccountState_None;
    actionState = NierActionState::NierActionState_None;

    groupRole = NierGroupRole::NierGroupRole_DPS;

    assembleDelay = 0;
}

void Nier_Base::Prepare()
{
    if (me)
    {
        me->SetPvP(true);
        me->UpdatePvP(true);
        me->pvpInfo.inPvPCombat = true;
        me->DurabilityRepairAll(false, 0);
        if (!me->GetGroup())
        {
            if (me->GetMap()->Instanceable())
            {
                me->TeleportToHomebind();
            }
        }
    }
}

void Nier_Base::Reset()
{
    ClearTarget();
}

void Nier_Base::Update(uint32 pDiff)
{
    elapsed += pDiff;
    if (checkDelay >= 0)
    {
        checkDelay -= pDiff;
        return;
    }

    if (UpdateNierAccount(elapsed))
    {
        elapsed = 0;
        return;
    }
    if (UpdateNierAction(elapsed))
    {
        elapsed = 0;
        return;
    }
    if (UpdateNierAwareness(elapsed))
    {
        elapsed = 0;
        return;
    }
}

bool Nier_Base::UpdateNierAccount(uint32 pElapsed)
{
    bool accountResult = true;

    switch (accountState)
    {
    case NierAccountState_None:
    {
        checkDelay = urand(5 * MINUTE * IN_MILLISECONDS, 10 * MINUTE * IN_MILLISECONDS);
        break;
    }
    case NierAccountState_OffLine:
    {
        checkDelay = urand(5 * MINUTE * IN_MILLISECONDS, 10 * MINUTE * IN_MILLISECONDS);
        break;
    }
    case NierAccountState_Enter:
    {
        accountState = NierAccountState::NierAccountState_CheckAccount;
        sLog.Out(LogType::LOG_BASIC, LogLevel::LOG_LVL_BASIC, "Nier %d - %d - %d go online.", nier_id, account_id, character_id);
        break;
    }
    case NierAccountState_CheckAccount:
    {
        if (nier_id == 0)
        {
            accountState = NierAccountState::NierAccountState_None;
            checkDelay = urand(5 * MINUTE * IN_MILLISECONDS, 10 * MINUTE * IN_MILLISECONDS);
            sLog.Out(LogType::LOG_BASIC, LogLevel::LOG_LVL_ERROR, "invalid nier.");
            break;
        }
        if (account_id > 0)
        {
            sAccountMgr.SetSecurity(account_id, AccountTypes::SEC_MODERATOR);
            sLog.Out(LogType::LOG_BASIC, LogLevel::LOG_LVL_BASIC, "Nier account %d is ready.", account_id);
            accountState = NierAccountState::NierAccountState_CheckCharacter;
        }
        else
        {
            if (account_name.empty())
            {
                std::ostringstream anStream;
                anStream << NIER_MARK << nier_id;
                account_name = anStream.str();
            }

            uint32 queryAccountId = 0;
            std::ostringstream accountQueryStream;
            accountQueryStream << "SELECT id FROM account where username = '" << account_name << "'";
            std::unique_ptr<QueryResult> nierAccountQR = LoginDatabase.Query(accountQueryStream.str().c_str());
            if (nierAccountQR)
            {
                Field* fields = nierAccountQR->Fetch();
                queryAccountId = fields[0].GetUInt32();
            }
            if (queryAccountId > 0)
            {
                account_id = queryAccountId;
                sAccountMgr.SetSecurity(account_id, AccountTypes::SEC_MODERATOR);
                std::ostringstream sqlStream;
                sqlStream << "update nier set account_id = " << account_id << " where nier_id = " << nier_id;
                std::string sql = sqlStream.str();
                CharacterDatabase.DirectExecute(sql.c_str());
                sLog.Out(LogType::LOG_BASIC, LogLevel::LOG_LVL_BASIC, "Nier account %s is created.", account_name.c_str());
                accountState = NierAccountState::NierAccountState_CheckCharacter;
            }
            else
            {
                sLog.Out(LogType::LOG_BASIC, LogLevel::LOG_LVL_BASIC, "Nier account %s is not ready.", account_name.c_str());
                accountState = NierAccountState::NierAccountState_CreateAccount;
            }
        }
        break;
    }
    case NierAccountState_CreateAccount:
    {
        if (account_name.empty())
        {
            std::ostringstream anStream;
            anStream << NIER_MARK << nier_id;
            account_name = anStream.str();
        }

        if (sAccountMgr.CreateAccount(account_name, NIER_MARK) == AccountOpResult::AOR_OK)
        {
            accountState = NierAccountState::NierAccountState_CheckAccount;
        }
        else
        {
            sLog.Out(LogType::LOG_BASIC, LogLevel::LOG_LVL_BASIC, "Nier %d account can not be created.", nier_id);
            accountState = NierAccountState::NierAccountState_None;
            checkDelay = urand(5 * MINUTE * IN_MILLISECONDS, 10 * MINUTE * IN_MILLISECONDS);
        }
        break;
    }
    case NierAccountState_CheckCharacter:
    {
        std::ostringstream queryStream;
        queryStream << "SELECT guid FROM characters where account = " << account_id;
        std::unique_ptr<QueryResult> characterQR = CharacterDatabase.Query(queryStream.str().c_str());
        if (characterQR)
        {
            Field* characterFields = characterQR->Fetch();
            character_id = characterFields[0].GetUInt32();
            if (character_id > 0)
            {
                std::ostringstream sqlStream;
                sqlStream << "update nier set character_id = " << character_id << " where nier_id = " << nier_id;
                std::string sql = sqlStream.str();
                CharacterDatabase.DirectExecute(sql.c_str());
                sLog.Out(LogType::LOG_BASIC, LogLevel::LOG_LVL_BASIC, "Nier account_id %d character_id %d is ready.", account_id, character_id);
                //entityState = NierEntityState::NierEntityState_DoEnum;
                accountState = NierAccountState::NierAccountState_DoLogin;
                checkDelay = urand(2 * IN_MILLISECONDS, 5 * IN_MILLISECONDS);
                break;
            }
        }
        sLog.Out(LogType::LOG_BASIC, LogLevel::LOG_LVL_BASIC, "Nier account_id %d character_id is not ready.", account_id);
        accountState = NierAccountState::NierAccountState_CreateCharacter;
        checkDelay = urand(2 * IN_MILLISECONDS, 5 * IN_MILLISECONDS);
        break;
    }
    case NierAccountState_CreateCharacter:
    {
        std::string currentName = "";
        bool nameValid = false;
        while (sNierManager->nierNameMap.find(sNierManager->nameIndex) != sNierManager->nierNameMap.end())
        {
            currentName = sNierManager->nierNameMap[sNierManager->nameIndex];
            std::ostringstream queryStream;
            queryStream << "SELECT count(*) FROM characters where name = '" << currentName << "'";
            std::unique_ptr<QueryResult> checkNameQR = CharacterDatabase.Query(queryStream.str().c_str());
            if (!checkNameQR)
            {
                sLog.Out(LogType::LOG_BASIC, LogLevel::LOG_LVL_BASIC, "Name %s is available", currentName.c_str());
                nameValid = true;
            }
            else
            {
                Field* nameCountFields = checkNameQR->Fetch();
                uint32 nameCount = nameCountFields[0].GetUInt32();
                if (nameCount == 0)
                {
                    nameValid = true;
                }
            }
            sNierManager->nameIndex++;
            if (nameValid)
            {
                break;
            }
        }
        if (!nameValid)
        {
            sLog.Out(LogType::LOG_BASIC, LogLevel::LOG_LVL_ERROR, "No available names");
            accountState = NierAccountState::NierAccountState_None;
            checkDelay = urand(5 * MINUTE * IN_MILLISECONDS, 10 * MINUTE * IN_MILLISECONDS);
            return;
        }
        uint8 gender = 0, skin = 0, face = 0, hairStyle = 0, hairColor = 0, facialHair = 0;
        while (true)
        {
            gender = urand(0, 100);
            if (gender < 50)
            {
                gender = 0;
            }
            else
            {
                gender = 1;
            }
            face = urand(0, 5);
            hairStyle = urand(0, 5);
            hairColor = urand(0, 5);
            facialHair = urand(0, 5);

            WorldSession* createSession = new WorldSession(account_id, NULL, AccountTypes::SEC_PLAYER, 0, LocaleConstant::LOCALE_enUS);
            Player* newPlayer = new Player(createSession);
            if (!Player::SaveNewPlayer(createSession, sObjectMgr.GeneratePlayerLowGuid(), currentName, target_race, target_class, gender, skin, face, hairStyle, hairColor, facialHair))
            {
                newPlayer->CleanupsBeforeDelete();
                delete createSession;
                delete newPlayer;
                sLog.Out(LogType::LOG_BASIC, LogLevel::LOG_LVL_ERROR, "Character create failed, %s %d %d ", currentName.c_str(), target_race, target_class);
                sLog.Out(LogType::LOG_BASIC, LogLevel::LOG_LVL_BASIC, "Try again");
                continue;
            }
            newPlayer->SetAtLoginFlag(AT_LOGIN_NONE);
            newPlayer->SaveToDB(true, true);
            character_id = newPlayer->GetGUIDLow();
            sWorld.AddSession(createSession);
            std::ostringstream replyStream;
            replyStream << "nier character created : " << account_id << " - " << newPlayer->GetGUIDLow() << " - " << currentName;
            std::string replyString = replyStream.str();
            sWorld.SendServerMessage(ServerMessageType::SERVER_MSG_CUSTOM, replyString.c_str());
            sLog.Out(LogType::LOG_BASIC, LogLevel::LOG_LVL_BASIC, replyString.c_str());
            delete createSession;
            break;
        }
        accountState = NierAccountState::NierAccountState_CheckCharacter;
        checkDelay = urand(2 * IN_MILLISECONDS, 5 * IN_MILLISECONDS);
        break;
    }
    case NierAccountState_CheckLogin:
    {
        checkDelay = urand(2 * IN_MILLISECONDS, 5 * IN_MILLISECONDS);
        ObjectGuid playerGuid = ObjectGuid(HIGHGUID_PLAYER, character_id);
        if (Player* me = ObjectAccessor::FindPlayer(playerGuid))
        {
            if (me->IsInWorld())
            {
                std::ostringstream replyStream;
                replyStream << "nier character logged in : " << account_id << " - " << character_id;
                std::string replyString = replyStream.str();
                sWorld.SendServerMessage(ServerMessageType::SERVER_MSG_CUSTOM, replyString.c_str());
                sLog.Out(LogType::LOG_BASIC, LogLevel::LOG_LVL_BASIC, replyString.c_str());
                accountState = NierAccountState::NierAccountState_Initialize;
                break;
            }
        }
        break;
    }
    case NierAccountState_DoLogin:
    {
        WorldSession* loginSession = sWorld.FindSession(account_id);
        if (!loginSession)
        {
            loginSession = new WorldSession(account_id, NULL, AccountTypes::SEC_PLAYER, 0, LocaleConstant::LOCALE_enUS);
            sWorld.AddSession(loginSession);
        }
        ObjectGuid playerGuid = ObjectGuid(HIGHGUID_PLAYER, character_id);
        loginSession->HandlePlayerLogin_Simple(playerGuid);
        std::ostringstream replyStream;
        replyStream << "log in character : " << account_id << " - " << character_id;
        std::string replyString = replyStream.str();
        sWorld.SendServerMessage(ServerMessageType::SERVER_MSG_CUSTOM, replyString.c_str());
        sLog.Out(LogType::LOG_BASIC, LogLevel::LOG_LVL_BASIC, replyString.c_str());
        checkDelay = urand(5 * IN_MILLISECONDS, 10 * IN_MILLISECONDS);
        accountState = NierAccountState::NierAccountState_CheckLogin;
        checkDelay = urand(2 * IN_MILLISECONDS, 5 * IN_MILLISECONDS);
        break;
    }
    case NierAccountState_DoEnum:
    {
        break;
    }
    case NierAccountState_CheckEnum:
    {
        break;
    }
    case NierAccountState_Initialize:
    {
        ObjectGuid playerGuid = ObjectGuid(HIGHGUID_PLAYER, character_id);
        if (Player* me = ObjectAccessor::FindPlayer(playerGuid))
        {
            if (me->IsInWorld())
            {
                ObjectGuid masterGuid = ObjectGuid(HIGHGUID_PLAYER, master_id);
                if (Player* master = ObjectAccessor::FindPlayer(masterGuid))
                {
                    if (master->IsInWorld())
                    {
                        InitializeCharacter(master->GetLevel());
                        std::ostringstream replyStream;
                        replyStream << "nier initialized : " << account_id << " - " << character_id << " - " << me->GetName();
                        std::string replyString = replyStream.str();
                        sWorld.SendServerMessage(ServerMessageType::SERVER_MSG_CUSTOM, replyString.c_str());
                        sLog.Out(LogType::LOG_BASIC, LogLevel::LOG_LVL_BASIC, replyString.c_str());
                        accountState = NierAccountState::NierAccountState_Equip;
                        checkDelay = urand(2 * IN_MILLISECONDS, 5 * IN_MILLISECONDS);
                        break;
                    }
                }
            }
        }
        checkDelay = urand(10 * IN_MILLISECONDS, 20 * IN_MILLISECONDS);
        break;
    }
    case NierAccountState_Equip:
    {
        ObjectGuid playerGuid = ObjectGuid(HIGHGUID_PLAYER, character_id);
        if (Player* me = ObjectAccessor::FindPlayer(playerGuid))
        {
            if (me->IsInWorld())
            {
                if (InitializeEquipments())
                {
                    checkDelay = 500;
                    break;
                }
                else
                {
                    std::ostringstream replyStream;
                    replyStream << "nier done gearing : " << account_id << " - " << character_id << " - " << me->GetName();
                    std::string replyString = replyStream.str();
                    sWorld.SendServerMessage(ServerMessageType::SERVER_MSG_CUSTOM, replyString.c_str());
                    sLog.Out(LogType::LOG_BASIC, LogLevel::LOG_LVL_BASIC, replyString.c_str());
                    accountState = NierAccountState::NierAccountState_Online;
                    checkDelay = urand(1 * IN_MILLISECONDS, 3 * IN_MILLISECONDS);
                }
            }
        }
        break;
    }
    case NierAccountState_Online:
    {
        accountResult = false;
        break;
    }
    case NierAccountState_Exit:
    {
        break;
    }
    case NierAccountState_CheckLogoff:
    {
        break;
    }
    case NierAccountState_DoLogoff:
    {
        break;
    }
    default:
    {
        break;
    }
    }

    return accountResult;
}

bool Nier_Base::UpdateNierAction(uint32 pElapsed)
{
    bool actionResult = true;

    if (accountState == NierAccountState::NierAccountState_Online)
    {
        if (actionTarget)
        {
            if (actionTarget->duration > actionTarget->timeLimit)
            {
                actionState = NierActionState::NierActionState_None;
            }
            else
            {
                actionTarget->duration += pElapsed;
            }
        }
        if (me)
        {
            if (me->IsInWorld())
            {
                switch (actionState)
                {
                case NierActionState_None:
                {
                    actionResult = false;
                    break;
                }
                case NierActionState_Idle:
                {
                    break;
                }
                case NierActionState_Wander:
                {
                    if (!me->IsMoving())
                    {
                        float destDist = me->GetDistance(actionTarget->targetPos);
                        if (destDist > DEFAULT_OBJECT_SCALE)
                        {
                            me->GetMotionMaster()->MovePoint(0, actionTarget->targetPos.x, actionTarget->targetPos.y, actionTarget->targetPos.z, MoveOptions::MOVE_WALK_MODE | MoveOptions::MOVE_PATHFINDING, me->GetOrientation());
                        }
                    }
                    break;
                }
                case NierActionState_Follow:
                {
                    break;
                }
                case NierActionState_Tank:
                {
                    break;
                }
                case NierActionState_Attack:
                {
                    if (!Attack(actionTarget->targetUnit))
                    {
                        actionState = NierActionState::NierActionState_None;
                        actionTarget->Reset();
                    }
                    break;
                }
                case NierActionState_Heal:
                {
                    break;
                }
                case NierActionState_Cast:
                {
                    break;
                }
                case NierActionState_Assist:
                {
                    break;
                }
                case NierActionState_Rest:
                {
                    float hpp = me->GetHealthPercent();
                    float mpp = 100.0f;
                    uint32 meClass = me->GetClass();
                    if (meClass == Classes::CLASS_HUNTER || meClass == Classes::CLASS_SHAMAN || meClass == Classes::CLASS_PALADIN || meClass == Classes::CLASS_PRIEST || meClass == Classes::CLASS_WARLOCK || meClass == Classes::CLASS_MAGE || meClass == Classes::CLASS_DRUID)
                    {
                        mpp = me->GetPowerPercent(Powers::POWER_MANA);
                    }
                    if (hpp > 98.0f && mpp > 98.0f)
                    {
                        actionState = NierActionState::NierActionState_None;
                        actionTarget->Reset();
                        break;
                    }
                    if (Eat())
                    {
                        break;
                    }
                    if (Drink())
                    {
                        break;
                    }
                    break;
                }
                default:
                {
                    break;
                }
                }
            }
        }
    }

    return actionResult;
}

bool Nier_Base::UpdateNierAwareness(uint32 pElapsed)
{
    if (accountState == NierAccountState::NierAccountState_Online)
    {
        if (me)
        {
            if (me->IsInWorld())
            {
                if (Group* meGroup = me->GetGroup())
                {
                    // grouping 
                }
                else
                {
                    // solo
                    if (me->IsInCombat())
                    {
                        Unit* enemy = nullptr;
                        for (auto const& pAttacker : me->GetAttackers())
                        {
                            float attackerDistance = me->GetDistance(pAttacker);
                            if (attackerDistance < DEFAULT_VISIBILITY_DISTANCE)
                            {
                                enemy = pAttacker;
                                if (pAttacker->GetTypeId() == TypeID::TYPEID_PLAYER)
                                {
                                    break;
                                }
                            }
                        }
                        if (enemy)
                        {
                            actionState = NierActionState::NierActionState_Attack;
                            actionTarget->Reset();
                            actionTarget->targetUnit = enemy;
                            actionTarget->timeLimit = 20000;
                        }
                    }
                    else
                    {
                        if (Rest())
                        {
                            return true;
                        }
                        uint32 actionRate = urand(0, 100);
                        if (actionRate < 50)
                        {
                            if (Wander())
                            {
                                return true;
                            }
                        }
                        else if (actionRate < 70)
                        {
                            if (PVE())
                            {
                                return true;
                            }
                        }
                        else if (actionRate < 90)
                        {
                            if (PVP())
                            {
                                return true;
                            }
                        }
                        else
                        {
                            if (Idle())
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

bool Nier_Base::Rest()
{
    float hpp = me->GetHealthPercent();
    float mpp = 100.0f;
    uint32 meClass = me->GetClass();
    if (meClass == Classes::CLASS_HUNTER || meClass == Classes::CLASS_SHAMAN || meClass == Classes::CLASS_PALADIN || meClass == Classes::CLASS_PRIEST || meClass == Classes::CLASS_WARLOCK || meClass == Classes::CLASS_MAGE || meClass == Classes::CLASS_DRUID)
    {
        mpp = me->GetPowerPercent(Powers::POWER_MANA);
    }
    if (hpp < 50.0f || mpp < 50.0f)
    {
        actionState = NierActionState::NierActionState_Rest;
        actionTarget->Reset();
        actionTarget->timeLimit = 15000;
        return true;
    }

    return false;
}

bool Nier_Base::PVP()
{
    Unit* target = nullptr;

    if (Player* hostilePlayer = me->FindNearestHostilePlayer(VISIBILITY_DISTANCE_TINY))
    {
        if (me->IsValidAttackTarget(hostilePlayer))
        {
            target = hostilePlayer;
        }
    }
    if (target)
    {
        actionState = NierActionState::NierActionState_Attack;
        actionTarget->Reset();
        actionTarget->targetUnit = target;
        actionTarget->timeLimit = 20000;
        return true;
    }

    return false;
}

bool Nier_Base::PVE()
{
    Unit* target = nullptr;

    std::unordered_set<Creature*> targetSet = sNierManager->GetCreatureSetInRange(me, 0, VISIBILITY_DISTANCE_TINY);
    for (std::unordered_set<Creature*>::iterator targetIT = targetSet.begin(); targetIT != targetSet.end(); targetIT++)
    {
        if (me->IsValidAttackTarget(*targetIT))
        {
            target = *targetIT;
            break;
        }
    }
    if (target)
    {
        actionState = NierActionState::NierActionState_Attack;
        actionTarget->Reset();
        actionTarget->targetUnit = target;
        actionTarget->timeLimit = 20000;
        return true;
    }

    return false;
}

bool Nier_Base::Wander()
{
    actionState = NierActionState::NierActionState_Wander;
    actionTarget->Reset();
    float targetX = me->GetPositionX();
    float targetY = me->GetPositionY();
    float targetZ = me->GetPositionZ();
    float distance = frand(20.0f, 40.0f);
    float angle = frand(0.0f, 2 * M_PI_F);
    me->GetNearPoint(me, targetX, targetY, targetZ, me->GetObjectBoundingRadius(), distance, angle);
    actionTarget->targetPos.x = targetX;
    actionTarget->targetPos.y = targetY;
    actionTarget->targetPos.z = targetZ;
    actionTarget->timeLimit = urand(5000, 10000);
    return true;
}

bool Nier_Base::Idle()
{
    actionState = NierActionState::NierActionState_Idle;
    actionTarget->Reset();
    actionTarget->timeLimit = urand(5000, 10000);
    return true;
}

bool Nier_Base::Attack(Unit* pTarget)
{
    if (!me)
    {
        return false;
    }
    if (!me->IsAlive())
    {
        return false;
    }
    if (!me->IsValidAttackTarget(pTarget))
    {
        return false;
    }
    if (!me->IsInRange(pTarget, 0, VISIBILITY_DISTANCE_NORMAL))
    {
        return false;
    }

    return true;
}

bool Nier_Base::Interrupt(Unit* pmTarget)
{
    return false;
}

bool Nier_Base::DPS(Unit* pmTarget, bool pmRushing, bool pmChasing, float pmDistanceMax, float pmDistanceMin)
{
    return false;
}

bool Nier_Base::Tank(Unit* pTarget)
{
    if (groupRole != NierGroupRole::NierGroupRole_Tank)
    {
        return false;
    }
    if (!me)
    {
        return false;
    }
    if (!me->IsAlive())
    {
        return false;
    }
    if (!me->IsValidAttackTarget(pTarget))
    {
        return false;
    }
    if (!me->IsInRange(pTarget, 0, VISIBILITY_DISTANCE_NORMAL))
    {
        return false;
    }

    return true;
}

bool Nier_Base::Follow(Unit* pmFollowTarget, float pmDistance)
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
    if (!pmFollowTarget)
    {
        return false;
    }
    ChooseTarget(pmFollowTarget);
}

bool Nier_Base::Heal(Unit* pmTarget, bool pmInstantOnly)
{
    return false;
}

bool Nier_Base::ReadyTank(Unit* pmTarget)
{
    return false;
}

bool Nier_Base::GroupHeal(Unit* pmTarget, bool pmInstantOnly)
{
    return false;
}

bool Nier_Base::SimpleHeal(Unit* pmTarget, bool pmInstantOnly)
{
    return false;
}

bool Nier_Base::Cure(Unit* pmTarget)
{
    return false;
}

bool Nier_Base::Buff(Unit* pmTarget)
{
    return false;
}

bool Nier_Base::Mark(Unit* pmTarget, int pmRTI)
{
    return false;
}

bool Nier_Base::Assist(int pmRTI)
{
    return false;
}

bool Nier_Base::Revive(Unit* pTarget)
{
    if (!me)
    {
        return false;
    }
    if (!me->IsAlive())
    {
        return false;
    }
    if (pTarget->GetTypeId() != TypeID::TYPEID_PLAYER)
    {
        return false;
    }

    return true;
}

bool Nier_Base::Petting(bool pmSummon, bool pmReset)
{
    return false;
}

void Nier_Base::InitializeCharacter(uint32 pmTargetLevel)
{

}

void Nier_Base::ResetTalent()
{

}

bool Nier_Base::InitializeEquipments(bool pmReset)
{
    return true;
}

void Nier_Base::RemoveEquipments()
{
    if (!me)
    {
        return;
    }
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

void Nier_Base::LearnTalent(uint32 pmTalentId, uint32 pmMaxRank)
{
    if (!me)
    {
        return;
    }
    uint32 checkRank = 0;
    while (checkRank < pmMaxRank)
    {
        me->LearnTalent(pmTalentId, checkRank);
        checkRank++;
    }
}

void Nier_Base::TrainSpells(uint32 pmTrainerEntry)
{
    if (CreatureInfo const* cInfo = sObjectMgr.GetCreatureTemplate(pmTrainerEntry))
    {
        if (cInfo->trainer_type == TrainerType::TRAINER_TYPE_CLASS)
        {
            if (cInfo->trainer_class == me->GetClass())
            {
                bool hadNew = false;
                if (const TrainerSpellData* cSpells = sObjectMgr.GetNpcTrainerSpells(cInfo->trainer_id))
                {
                    do
                    {
                        hadNew = false;
                        for (const auto& itr : cSpells->spellList)
                        {
                            TrainerSpell const* eachSpell = &itr.second;
                            if (me->GetTrainerSpellState(eachSpell) == TRAINER_SPELL_GREEN)
                            {
                                hadNew = true;
                                SpellEntry const* proto = sSpellMgr.GetSpellEntry(eachSpell->spell);
                                me->InterruptSpellsWithChannelFlags(AURA_INTERRUPT_INTERACTING_CANCELS);
                                me->RemoveAurasWithInterruptFlags(AURA_INTERRUPT_INTERACTING_CANCELS);
                                me->RemoveSpellsCausingAura(SPELL_AURA_MOUNTED);
                                Spell* activeSpell;
                                activeSpell = new Spell(me, proto, false);
                                SpellCastTargets targets;
                                targets.setUnitTarget(me);
                                SpellCastResult scr = activeSpell->prepare(std::move(targets));
                                activeSpell->update(1); // Update the spell right now. Prevents desynch => take twice the money if you click really fast.
                                if (scr == SPELL_CAST_OK)
                                {
                                    me->GetSession()->SendTrainingSuccess(me->GetObjectGuid(), eachSpell->spell);
                                }
                                else
                                {
                                    me->GetSession()->SendTrainingFailure(me->GetObjectGuid(), eachSpell->spell, TRAIN_FAIL_UNAVAILABLE);
                                }
                            }
                        }
                    } while (hadNew);
                }
                if (const TrainerSpellData* tSpells = sObjectMgr.GetNpcTrainerTemplateSpells(cInfo->trainer_id))
                {
                    do
                    {
                        hadNew = false;
                        for (const auto& itr : tSpells->spellList)
                        {
                            TrainerSpell const* eachSpell = &itr.second;
                            if (me->GetTrainerSpellState(eachSpell) == TRAINER_SPELL_GREEN)
                            {
                                hadNew = true;
                                SpellEntry const* proto = sSpellMgr.GetSpellEntry(eachSpell->spell);
                                for (size_t i = 0; i < MAX_SPELL_REAGENTS; i++)
                                {
                                    if (proto->Reagent[i] > 0)
                                    {
                                        if (!me->HasItemCount(proto->Reagent[i], proto->ReagentCount[i]))
                                        {
                                            me->StoreNewItemInBestSlots(proto->Reagent[i], proto->ReagentCount[i] * 10);
                                        }
                                    }
                                }
                                me->InterruptSpellsWithChannelFlags(AURA_INTERRUPT_INTERACTING_CANCELS);
                                me->RemoveAurasWithInterruptFlags(AURA_INTERRUPT_INTERACTING_CANCELS);
                                me->RemoveSpellsCausingAura(SPELL_AURA_MOUNTED);
                                Spell* activeSpell;
                                activeSpell = new Spell(me, proto, false);
                                SpellCastTargets targets;
                                targets.setUnitTarget(me);
                                SpellCastResult scr = activeSpell->prepare(std::move(targets));
                                activeSpell->update(1); // Update the spell right now. Prevents desynch => take twice the money if you click really fast.
                                if (scr == SPELL_CAST_OK)
                                {
                                    me->GetSession()->SendTrainingSuccess(me->GetObjectGuid(), eachSpell->spell);
                                }
                                else
                                {
                                    me->GetSession()->SendTrainingFailure(me->GetObjectGuid(), eachSpell->spell, TRAIN_FAIL_UNAVAILABLE);
                                }
                            }
                        }
                    } while (hadNew);
                }
            }
        }
    }
}

void Nier_Base::EquipRandomItem(uint32 pmEquipSlot, uint32 pmClass, uint32 pmSubclass, uint32 pmMinQuality, int pmModType, std::unordered_set<uint32> pmInventoryTypeSet)
{
    bool checkStat = true;
    if (pmModType < 0)
    {
        checkStat = false;
    }
    uint32 inventoryType = 0;
    if (pmEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_HEAD)
    {
        inventoryType = 1;
    }
    else if (pmEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_SHOULDERS)
    {
        inventoryType = 3;
    }
    else if (pmEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_WRISTS)
    {
        inventoryType = 9;
    }
    else if (pmEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_WAIST)
    {
        inventoryType = 6;
    }
    else if (pmEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_FEET)
    {
        inventoryType = 8;
    }
    else if (pmEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_HANDS)
    {
        inventoryType = 10;
    }
    else if (pmEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_CHEST)
    {
        inventoryType = 5;
    }
    else if (pmEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_LEGS)
    {
        inventoryType = 7;
    }
    else if (pmEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_BACK)
    {
        inventoryType = 16;
    }
    else if (pmEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_NECK)
    {
        inventoryType = 2;
    }
    else if (pmEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_FINGER1)
    {
        inventoryType = 11;
    }
    else if (pmEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_FINGER2)
    {
        inventoryType = 11;
    }
    else if (pmEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_MAINHAND)
    {
        inventoryType = InventoryType::INVTYPE_WEAPON;
    }
    else if (pmEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_OFFHAND)
    {
        inventoryType = InventoryType::INVTYPE_WEAPON;
    }
    else if (pmEquipSlot == EquipmentSlots::EQUIPMENT_SLOT_RANGED)
    {
        inventoryType = 15;
    }
    else
    {
        return;
    }

    if (pmInventoryTypeSet.size() > 0)
    {
        inventoryType = *pmInventoryTypeSet.begin();
    }
    int maxReqLevel = me->GetLevel();
    int minReqLevel = maxReqLevel - 5;
    while (minReqLevel > 0 && maxReqLevel > 1)
    {
        if (sNierManager->equipsMap.find(inventoryType) != sNierManager->equipsMap.end())
        {
            int activeLevel = urand(minReqLevel, maxReqLevel);
            if (sNierManager->equipsMap[inventoryType][pmSubclass].find(activeLevel) != sNierManager->equipsMap[inventoryType][pmSubclass].end())
            {
                int itemsSize = sNierManager->equipsMap[inventoryType][pmSubclass][activeLevel].size();
                if (itemsSize > 0)
                {
                    int itemIndex = urand(0, itemsSize - 1);
                    uint32 itemEntry = sNierManager->equipsMap[inventoryType][pmSubclass][activeLevel][itemIndex];
                    if (const ItemPrototype* pProto = sObjectMgr.GetItemPrototype(itemEntry))
                    {
                        bool hasStat = false;
                        if (checkStat)
                        {
                            if (pProto->RandomProperty > 0)
                            {
                                hasStat = true;
                            }
                            else
                            {
                                for (uint32 statIndex = 0; statIndex < MAX_ITEM_PROTO_STATS; statIndex++)
                                {
                                    if (pProto->ItemStat[statIndex].ItemStatType == pmModType)
                                    {
                                        hasStat = true;
                                        break;
                                    }
                                }
                            }
                        }
                        else
                        {
                            hasStat = true;
                        }
                        if (hasStat)
                        {
                            uint16 eDest;
                            uint8 msg = me->CanEquipNewItem(NULL_SLOT, eDest, itemEntry, false);
                            if (msg == EQUIP_ERR_OK)
                            {
                                if (Item* pItem = Item::CreateItem(itemEntry, 1, me->GetObjectGuid()))
                                {
                                    if (uint32 randomPropertyId = Item::GenerateItemRandomPropertyId(itemEntry))
                                    {
                                        pItem->SetItemRandomProperties(randomPropertyId);
                                        pItem->SetState(ItemUpdateState::ITEM_NEW, me);
                                    }
                                    me->SendNewItem(pItem, 1, true, true);
                                    ItemPosCountVec sDest;
                                    uint8 storeResult = me->CanStoreItem(NULL_BAG, NULL_SLOT, sDest, pItem, false);
                                    if (storeResult == EQUIP_ERR_OK)
                                    {
                                        me->StoreItem(sDest, pItem, true);
                                    }
                                }
                                for (int i = INVENTORY_SLOT_ITEM_START; i < INVENTORY_SLOT_ITEM_END; ++i)
                                {
                                    if (Item* targetItem = me->GetItemByPos(INVENTORY_SLOT_BAG_0, i))
                                    {
                                        if (targetItem->GetEntry() == itemEntry)
                                        {
                                            uint16 dest = 0;
                                            InventoryResult ir = me->CanEquipItem(NULL_SLOT, dest, targetItem, false);
                                            if (ir == EQUIP_ERR_OK)
                                            {
                                                me->RemoveItem(INVENTORY_SLOT_BAG_0, i, true);
                                                me->EquipItem(dest, targetItem, true);
                                                break;
                                            }
                                        }
                                    }
                                }
                            }

                            //if (me->StoreNewItemInBestSlots(itemEntry, 1))
                            //{
                            //	std::ostringstream msgStream;
                            //	msgStream << me->GetName() << " Equiped " << itemEntry;
                            //	sWorld.SendServerMessage(ServerMessageType::SERVER_MSG_CUSTOM, msgStream.str().c_str());
                            //	sLog.Out(LogType::LOG_BASIC, LogLevel::LOG_LVL_BASIC, msgStream.str().c_str());
                            //	return;
                            //}
                        }
                    }
                }
            }
        }
        maxReqLevel = maxReqLevel - 1;
        minReqLevel = maxReqLevel - 5;
    }
}

void Nier_Base::PetAttack(Unit* pmTarget)
{
    if (me)
    {
        if (Pet* myPet = me->GetPet())
        {
            if (myPet->IsAlive())
            {
                if (CreatureAI* cai = myPet->AI())
                {
                    cai->AttackStart(pmTarget);
                }
            }
        }
    }
}

void Nier_Base::PetStop()
{
    if (me)
    {
        if (Pet* myPet = me->GetPet())
        {
            myPet->AttackStop();
            if (CharmInfo* pci = myPet->GetCharmInfo())
            {
                if (pci->IsCommandAttack())
                {
                    pci->SetIsCommandAttack(false);
                }
                if (!pci->IsCommandFollow())
                {
                    pci->SetIsCommandFollow(true);
                }
            }
        }
    }
}

bool Nier_Base::UseItem(Item* pmItem, Unit* pmTarget)
{
    if (me->CanUseItem(pmItem) != EQUIP_ERR_OK)
    {
        return false;
    }

    if (me->IsNonMeleeSpellCasted(false, false, true))
    {
        return false;
    }

    if (const ItemPrototype* proto = pmItem->GetProto())
    {
        ChooseTarget(pmTarget);
        SpellCastTargets targets;
        targets.Update(pmTarget);
        me->CastItemUseSpell(pmItem, targets);
        return true;
    }

    return false;
}

bool Nier_Base::UseItem(Item* pmItem, Item* pmTarget)
{
    if (!me)
    {
        return false;
    }
    if (me->CanUseItem(pmItem) != EQUIP_ERR_OK)
    {
        return false;
    }
    if (me->IsNonMeleeSpellCasted(false, false, true))
    {
        return false;
    }
    if (!pmTarget)
    {
        return false;
    }

    if (const ItemPrototype* proto = pmItem->GetProto())
    {
        SpellCastTargets targets;
        targets.setItemTarget(pmTarget);
        me->CastItemUseSpell(pmItem, targets);
        return true;
    }

    return false;
}

bool Nier_Base::CastSpell(Unit* pmTarget, uint32 pmSpellId, bool pmCheckAura, bool pmOnlyMyAura, bool pmClearShapeShift, uint32 pmMaxAuraStack)
{
    if (!SpellValid(pmSpellId))
    {
        return false;
    }
    if (!me)
    {
        return false;
    }
    if (me->IsNonMeleeSpellCasted(false, false, true))
    {
        return true;
    }
    if (pmClearShapeShift)
    {
        me->RemoveSpellsCausingAura(SPELL_AURA_MOD_SHAPESHIFT);
    }
    if (const SpellEntry* pS = sSpellMgr.GetSpellEntry(pmSpellId))
    {
        if (pmTarget)
        {
            if (!me->IsWithinLOSInMap(pmTarget))
            {
                return false;
            }
            if (pmTarget->IsImmuneToSpell(pS, false))
            {
                return false;
            }
            if (pmCheckAura)
            {
                if (pmOnlyMyAura)
                {
                    if (sNierManager->HasAura(pmTarget, pmSpellId, me))
                    {
                        return false;
                    }
                }
                else
                {
                    if (sNierManager->HasAura(pmTarget, pmSpellId))
                    {
                        return false;
                    }
                }
            }
            if (Spell* checkSpell = new Spell(me, pS, false))
            {
                SpellCastResult scr = checkSpell->CheckCast(true);
                if (scr != SpellCastResult::SPELL_CAST_OK)
                {
                    return false;
                }
            }
            if (!me->HasInArc(pmTarget, M_PI / 2))
            {
                me->SetFacingToObject(pmTarget);
            }
            if (me->GetTargetGuid() != pmTarget->GetObjectGuid())
            {
                ChooseTarget(pmTarget);
            }
        }
        for (size_t i = 0; i < MAX_SPELL_REAGENTS; i++)
        {
            if (pS->Reagent[i] > 0)
            {
                if (!me->HasItemCount(pS->Reagent[i], pS->ReagentCount[i]))
                {
                    me->StoreNewItemInBestSlots(pS->Reagent[i], pS->ReagentCount[i] * 10);
                }
            }
        }
        if (me->GetStandState() != UnitStandStateType::UNIT_STAND_STATE_STAND)
        {
            me->SetStandState(UNIT_STAND_STATE_STAND);
        }
        //me->CastSpell(pmTarget, pS, false);
        //return true;

        SpellCastResult scr = me->CastSpell(pmTarget, pS->Id, false);
        if (scr == SpellCastResult::SPELL_CAST_OK)
        {
            return true;
        }
    }

    return false;
}

void Nier_Base::CancelAura(uint32 pmSpellID)
{
    if (pmSpellID == 0)
    {
        return;
    }
    if (!me)
    {
        return;
    }
    me->RemoveAurasDueToSpell(pmSpellID);
}

bool Nier_Base::Eat()
{
    uint32 foodEntry = 0;
    uint32 myLevel = me->GetLevel();
    if (myLevel >= 75)
    {
        foodEntry = 35950;
    }
    else if (myLevel >= 65)
    {
        foodEntry = 33449;
    }
    else if (myLevel >= 55)
    {
        foodEntry = 21023;
    }
    else if (myLevel >= 45)
    {
        foodEntry = 8950;
    }
    else if (myLevel >= 35)
    {
        foodEntry = 4601;
    }
    else if (myLevel >= 25)
    {
        foodEntry = 4544;
    }
    else if (myLevel >= 15)
    {
        foodEntry = 4542;
    }
    else if (myLevel >= 5)
    {
        foodEntry = 4541;
    }
    else
    {
        foodEntry = 4540;
    }
    if (!me->HasItemCount(foodEntry, 1))
    {
        me->StoreNewItemInBestSlots(foodEntry, 20);
    }
    uint32 itemSpellId = 0;
    if (ItemPrototype const* proto = sObjectMgr.GetItemPrototype(foodEntry))
    {
        for (const auto& spellData : proto->Spells)
        {
            if (spellData.SpellId)
            {
                if (spellData.SpellTrigger == ITEM_SPELLTRIGGER_ON_USE)
                {
                    itemSpellId = spellData.SpellId;
                    break;
                }
            }
        }
    }
    if (itemSpellId > 0)
    {
        if (!me->HasAura(itemSpellId))
        {
            me->CombatStop(true);
            me->StopMoving();
            me->GetMotionMaster()->Clear();
            ClearTarget();

            Item* pFood = GetItemInInventory(foodEntry);
            if (pFood && !pFood->IsInTrade())
            {
                if (UseItem(pFood, me))
                {
                    return true;
                }
            }
        }
    }

    return false;
}

bool Nier_Base::Drink()
{
    uint32 drinkEntry = 0;
    uint32 myLevel = me->GetLevel();
    if (myLevel >= 75)
    {
        drinkEntry = 33445;
    }
    else if (myLevel >= 70)
    {
        drinkEntry = 33444;
    }
    else if (myLevel >= 65)
    {
        drinkEntry = 27860;
    }
    else if (myLevel >= 60)
    {
        drinkEntry = 28399;
    }
    else if (myLevel >= 55)
    {
        drinkEntry = 18300;
    }
    else if (myLevel >= 45)
    {
        drinkEntry = 8766;
    }
    else if (myLevel >= 35)
    {
        drinkEntry = 1645;
    }
    else if (myLevel >= 25)
    {
        drinkEntry = 1708;
    }
    else if (myLevel >= 15)
    {
        drinkEntry = 1205;
    }
    else if (myLevel >= 5)
    {
        drinkEntry = 1179;
    }
    else
    {
        drinkEntry = 159;
    }

    if (!me->HasItemCount(drinkEntry, 1))
    {
        me->StoreNewItemInBestSlots(drinkEntry, 20);
    }
    uint32 itemSpellId = 0;
    if (ItemPrototype const* proto = sObjectMgr.GetItemPrototype(drinkEntry))
    {
        for (const auto& spellData : proto->Spells)
        {
            if (spellData.SpellId)
            {
                if (spellData.SpellTrigger == ITEM_SPELLTRIGGER_ON_USE)
                {
                    itemSpellId = spellData.SpellId;
                    break;
                }
            }
        }
    }
    if (itemSpellId > 0)
    {
        if (!me->HasAura(itemSpellId))
        {
            me->CombatStop(true);
            me->StopMoving();
            me->GetMotionMaster()->Clear();
            ClearTarget();
            Item* pDrink = GetItemInInventory(drinkEntry);
            if (pDrink && !pDrink->IsInTrade())
            {
                if (UseItem(pDrink, me))
                {
                    return true;
                }
            }
        }
    }

    return false;
}

bool Nier_Base::HealthPotion()
{
    if (!me)
    {
        return false;
    }
    else if (!me->IsAlive())
    {
        return false;
    }
    else if (!me->IsInCombat())
    {
        return false;
    }
    uint32 potionEntry = 0;
    uint32 myLevel = me->GetLevel();
    if (myLevel >= 70)
    {
        potionEntry = 33447;
    }
    else if (myLevel >= 55)
    {
        potionEntry = 22829;
    }
    else if (myLevel >= 45)
    {
        potionEntry = 13446;
    }
    else if (myLevel >= 35)
    {
        potionEntry = 3928;
    }
    else if (myLevel >= 21)
    {
        potionEntry = 1710;
    }
    else if (myLevel >= 12)
    {
        potionEntry = 929;
    }
    else if (myLevel >= 3)
    {
        potionEntry = 858;
    }
    else
    {
        potionEntry = 118;
    }
    if (!me->HasItemCount(potionEntry, 1))
    {
        me->StoreNewItemInBestSlots(potionEntry, 20);
    }
    Item* pPotion = GetItemInInventory(potionEntry);
    if (pPotion && !pPotion->IsInTrade())
    {
        if (UseItem(pPotion, me))
        {
            return true;
        }
    }
    return false;
}

bool Nier_Base::ManaPotion()
{
    if (!me)
    {
        return false;
    }
    else if (!me->IsAlive())
    {
        return false;
    }
    else if (!me->IsInCombat())
    {
        return false;
    }
    uint32 potionEntry = 0;
    uint32 myLevel = me->GetLevel();
    if (myLevel >= 70)
    {
        potionEntry = 33448;
    }
    else if (myLevel >= 55)
    {
        potionEntry = 22832;
    }
    else if (myLevel >= 49)
    {
        potionEntry = 13444;
    }
    else if (myLevel >= 41)
    {
        potionEntry = 13443;
    }
    else if (myLevel >= 31)
    {
        potionEntry = 6149;
    }
    else if (myLevel >= 22)
    {
        potionEntry = 3827;
    }
    else if (myLevel >= 14)
    {
        potionEntry = 3385;
    }
    else if (myLevel >= 5)
    {
        potionEntry = 2455;
    }
    if (potionEntry > 0)
    {
        if (!me->HasItemCount(potionEntry, 1))
        {
            me->StoreNewItemInBestSlots(potionEntry, 20);
        }
        Item* pPotion = GetItemInInventory(potionEntry);
        if (pPotion && !pPotion->IsInTrade())
        {
            if (UseItem(pPotion, me))
            {
                return true;
            }
        }
    }

    return false;
}

void Nier_Base::ChooseTarget(Unit* pmTarget)
{
    if (pmTarget)
    {
        if (me)
        {
            me->SetSelectionGuid(pmTarget->GetObjectGuid());
            me->SetTargetGuid(pmTarget->GetObjectGuid());
        }
    }
}

void Nier_Base::ClearTarget()
{
    if (me)
    {
        me->SetSelectionGuid(ObjectGuid());
        me->SetTargetGuid(ObjectGuid());
        me->AttackStop();
        me->InterruptNonMeleeSpells(true);
    }
}

bool Nier_Base::SpellValid(uint32 pmSpellID)
{
    if (pmSpellID == 0)
    {
        return false;
    }
    if (!me->IsSpellReady(pmSpellID))
    {
        return false;
    }

    return true;
}

Item* Nier_Base::GetItemInInventory(uint32 pmEntry)
{
    if (!me)
    {
        return NULL;
    }
    for (uint8 i = INVENTORY_SLOT_ITEM_START; i < INVENTORY_SLOT_ITEM_END; i++)
    {
        Item* pItem = me->GetItemByPos(INVENTORY_SLOT_BAG_0, i);
        if (pItem)
        {
            if (pItem->GetEntry() == pmEntry)
            {
                return pItem;
            }
        }
    }

    for (uint8 i = INVENTORY_SLOT_BAG_START; i < INVENTORY_SLOT_BAG_END; i++)
    {
        if (Bag* pBag = (Bag*)me->GetItemByPos(INVENTORY_SLOT_BAG_0, i))
        {
            for (uint32 j = 0; j < pBag->GetBagSize(); j++)
            {
                Item* pItem = me->GetItemByPos(i, j);
                if (pItem)
                {
                    if (pItem->GetEntry() == pmEntry)
                    {
                        return pItem;
                    }
                }
            }
        }
    }

    return NULL;
}
