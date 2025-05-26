#include "Nier_Base.h"

#include "NierConfig.h"
#include "NierManager.h"
#include "Player.h"
#include "Item.h"
#include "Group.h"
#include "Spell.h"
#include "CreatureAI.h"
#include "Bag.h"
#include "AccountMgr.h"
#include "ItemPrototype.h"
#include "GridNotifiers.h"

Nier_Base::Nier_Base()
{
    creating = false;

    nier_id = 0;
    master_character_id = 0;
    account_id = 0;
    account_name = "";
    character_id = 0;
    target_level = 0;
    target_specialty = 0;
    target_race = 0;
    target_class = 0;

    me = nullptr;
    actionDuration = 0;
    actionTimeLimit = 0;
    actionTargetUnit = nullptr;
    actionTargetSpell = 0;

    followDistance = 0.0f;

    specialty = 0;
    accountState = NierAccountState::NierAccountState_None;
    actionState = NierActionState::NierActionState_None;

    timeValue = 0;
    checkDelay = 0;
}

void Nier_Base::ClearAction()
{
    actionState = NierActionState::NierActionState_None;
    actionDuration = 0;
    actionTimeLimit = 0;
    actionTargetUnit = nullptr;
    if (me)
    {
        actionTargetPos = me->GetPosition();
    }
    actionTargetSpell = 0;
}

void Nier_Base::Prepare()
{
    if (me)
    {
        me->SetPvP(true);
        me->UpdatePvP(true);
        me->DurabilityRepairAll(false, 0);
        if (me->GetMap()->Instanceable())
        {
            me->TeleportToHomebind(TeleportToOptions::TELE_TO_GM_MODE, false);
        }
        followDistance = frand(ATTACK_DISTANCE, INSPECT_DISTANCE);
    }
}

void Nier_Base::Update(uint64 pTimeValue)
{
    uint64 elapsed = pTimeValue - timeValue;
    timeValue = pTimeValue;
    checkDelay -= elapsed;
    actionDuration += elapsed;
    if (checkDelay > 0)
    {
        return;
    }

    if (UpdateAccount())
    {
        return;
    }
    if (UpdateAction())
    {
        return;
    }
    if (UpdateMind())
    {
        return;
    }
}

bool Nier_Base::UpdateAccount()
{
    bool accountResult = true;

    std::ostringstream replyStream;
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
        creating = false;
        accountState = NierAccountState::NierAccountState_CheckAccount;
        replyStream << "Nier enter " << nier_id << " - " << account_id << " - " << character_id << " - ";
        sWorld.SendServerMessage(ServerMessageType::SERVER_MSG_CUSTOM, replyStream.str().c_str());
        break;
    }
    case NierAccountState_CheckAccount:
    {
        if (account_name.empty())
        {
            accountState = NierAccountState::NierAccountState_None;
            checkDelay = urand(5 * MINUTE * IN_MILLISECONDS, 10 * MINUTE * IN_MILLISECONDS);
            replyStream << "invalid nier";
            sWorld.SendServerMessage(ServerMessageType::SERVER_MSG_CUSTOM, replyStream.str().c_str());
            break;
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
            std::ostringstream sqlStream;
            sqlStream << "update nier set account_id = " << account_id << " where account_name = '" << account_name << "'";
            std::string sql = sqlStream.str();
            CharacterDatabase.DirectExecute(sql.c_str());
            replyStream << "Nier account is ready - " << account_name;
            accountState = NierAccountState::NierAccountState_CheckCharacter;
        }
        else
        {
            replyStream << "Nier account is not ready - " << account_name;
            accountState = NierAccountState::NierAccountState_CreateAccount;
        }
        sWorld.SendServerMessage(ServerMessageType::SERVER_MSG_CUSTOM, replyStream.str().c_str());
        break;
    }
    case NierAccountState_CreateAccount:
    {
        if (account_name.empty())
        {
            accountState = NierAccountState::NierAccountState_None;
            checkDelay = urand(5 * MINUTE * IN_MILLISECONDS, 10 * MINUTE * IN_MILLISECONDS);
            replyStream << "invalid nier";
            sWorld.SendServerMessage(ServerMessageType::SERVER_MSG_CUSTOM, replyStream.str().c_str());
            break;
        }
        if (sAccountMgr.CreateAccount(account_name, NIER_MARK) == AccountOpResult::AOR_OK)
        {
            accountState = NierAccountState::NierAccountState_CheckAccount;
        }
        else
        {
            replyStream << "Nier account can not be created - " << nier_id;
            sWorld.SendServerMessage(ServerMessageType::SERVER_MSG_CUSTOM, replyStream.str().c_str());
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
                replyStream << "Nier is ready - " << account_id << " - " << character_id;
                sWorld.SendServerMessage(ServerMessageType::SERVER_MSG_CUSTOM, replyStream.str().c_str());
                //accountState = NierAccountState::NierAccountState_DoEnum;
                accountState = NierAccountState::NierAccountState_DoLogin;
                checkDelay = urand(2 * IN_MILLISECONDS, 5 * IN_MILLISECONDS);
                break;
            }
        }
        replyStream << "Nier is not ready - " << account_id;
        sWorld.SendServerMessage(ServerMessageType::SERVER_MSG_CUSTOM, replyStream.str().c_str());
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
                replyStream << "Name is available - " << currentName;
                sWorld.SendServerMessage(ServerMessageType::SERVER_MSG_CUSTOM, replyStream.str().c_str());
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
            replyStream << "No available names";
            sWorld.SendServerMessage(ServerMessageType::SERVER_MSG_CUSTOM, replyStream.str().c_str());
            accountState = NierAccountState::NierAccountState_None;
            checkDelay = urand(5 * MINUTE * IN_MILLISECONDS, 10 * MINUTE * IN_MILLISECONDS);
            return false;
        }
        uint8 gender = 0, skin = 0, face = 0, hairStyle = 0, hairColor = 0, facialHair = 0;
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

        if (WorldSession* createSession = new WorldSession(account_id, NULL, AccountTypes::SEC_PLAYER, 0, LocaleConstant::LOCALE_enUS))
        {
            if (Player::SaveNewPlayer(createSession, sObjectMgr.GeneratePlayerLowGuid(), currentName, target_race, target_class, gender, skin, face, hairStyle, hairColor, facialHair))
            {
                creating = true;
                replyStream << "character created - " << nier_id;
                sWorld.SendServerMessage(ServerMessageType::SERVER_MSG_CUSTOM, replyStream.str().c_str());
                accountState = NierAccountState::NierAccountState_CheckCharacter;
                checkDelay = urand(1 * IN_MILLISECONDS, 5 * IN_MILLISECONDS);
            }
            else
            {
                replyStream << "create character failed - " << currentName << " - " << target_race << " - " << target_class;
                sWorld.SendServerMessage(ServerMessageType::SERVER_MSG_CUSTOM, replyStream.str().c_str());
                accountState = NierAccountState::NierAccountState_None;
                checkDelay = urand(5 * MINUTE * IN_MILLISECONDS, 10 * MINUTE * IN_MILLISECONDS);
            }
            delete createSession;
        }
        else
        {
            replyStream << "create session failed - " << nier_id;
            sWorld.SendServerMessage(ServerMessageType::SERVER_MSG_CUSTOM, replyStream.str().c_str());
            accountState = NierAccountState::NierAccountState_None;
            checkDelay = urand(5 * MINUTE * IN_MILLISECONDS, 10 * MINUTE * IN_MILLISECONDS);
        }
        break;
    }
    case NierAccountState_CheckLogin:
    {
        checkDelay = urand(2 * IN_MILLISECONDS, 5 * IN_MILLISECONDS);
        ObjectGuid playerGuid = ObjectGuid(HighGuid::HIGHGUID_PLAYER, character_id);
        if (Player* targetPlayer = ObjectAccessor::FindPlayer(playerGuid))
        {
            if (targetPlayer->IsInWorld())
            {
                targetPlayer->nier = this;
                me = targetPlayer;
                replyStream << "nier character logged in - " << account_id << " - " << character_id;
                sWorld.SendServerMessage(ServerMessageType::SERVER_MSG_CUSTOM, replyStream.str().c_str());
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
        loginSession->nier_id = nier_id;
        ObjectGuid playerGuid = ObjectGuid(HighGuid::HIGHGUID_PLAYER, character_id);
        WorldPacket wpLogin(CMSG_PLAYER_LOGIN, 16);
        wpLogin << playerGuid;
        loginSession->HandlePlayerLoginOpcode(wpLogin);
        replyStream << "log in character - " << account_id << " - " << character_id;
        sWorld.SendServerMessage(ServerMessageType::SERVER_MSG_CUSTOM, replyStream.str().c_str());
        accountState = NierAccountState::NierAccountState_CheckLogin;
        checkDelay = urand(2 * IN_MILLISECONDS, 5 * IN_MILLISECONDS);
        break;
    }
    case NierAccountState_DoEnum:
    {
        WorldSession* loginSession = sWorld.FindSession(account_id);
        if (!loginSession)
        {
            loginSession = new WorldSession(account_id, NULL, AccountTypes::SEC_PLAYER, 0, LocaleConstant::LOCALE_enUS);
            sWorld.AddSession(loginSession);
        }
        loginSession->nier_id = nier_id;
        WorldPacket wpEnum(CMSG_CHAR_ENUM, 4);
        loginSession->HandleCharEnumOpcode(wpEnum);
        sLog.Out(LogType::LOG_BASIC, LogLevel::LOG_LVL_BASIC, "Enum character %d %d ", account_id, character_id);
        accountState = NierAccountState::NierAccountState_CheckEnum;
        checkDelay = urand(5 * IN_MILLISECONDS, 10 * IN_MILLISECONDS);
        break;
    }
    case NierAccountState_CheckEnum:
    {
        checkDelay = urand(5 * IN_MILLISECONDS, 10 * IN_MILLISECONDS);
        break;
    }
    case NierAccountState_Initialize:
    {
        if (me->IsInWorld())
        {
            ObjectGuid masterGuid = ObjectGuid(HighGuid::HIGHGUID_PLAYER, master_character_id);
            if (Player* master = ObjectAccessor::FindPlayer(masterGuid))
            {
                if (master->IsInWorld())
                {
                    InitializeCharacter(master->GetLevel());
                    replyStream << "nier initialized : " << account_id << " - " << character_id << " - " << me->GetName();
                    sWorld.SendServerMessage(ServerMessageType::SERVER_MSG_CUSTOM, replyStream.str().c_str());

                    // role initialize
                    uint32 meClass = me->GetClass();
                    if (meClass == Classes::CLASS_WARRIOR || meClass == Classes::CLASS_DRUID)
                    {
                        me->nierGroupRole = NierGroupRole::NierGroupRole_Tank;
                    }
                    else if (meClass == Classes::CLASS_PRIEST)
                    {
                        me->nierGroupRole = NierGroupRole::NierGroupRole_Healer;
                    }
                    else
                    {
                        me->nierGroupRole = NierGroupRole::NierGroupRole_DPS;
                    }

                    accountState = NierAccountState::NierAccountState_Equip;
                    checkDelay = urand(2 * IN_MILLISECONDS, 5 * IN_MILLISECONDS);
                    break;
                }
            }
        }
        checkDelay = urand(10 * IN_MILLISECONDS, 20 * IN_MILLISECONDS);
        break;
    }
    case NierAccountState_Equip:
    {
        if (me->IsInWorld())
        {
            for (uint32 equipSlot = EquipmentSlots::EQUIPMENT_SLOT_HEAD; equipSlot < EquipmentSlots::EQUIPMENT_SLOT_TABARD; equipSlot++)
            {
                EquipRandomItem(equipSlot);
            }
            replyStream << "nier equipped : " << account_id << " - " << character_id << " - " << me->GetName();
            sWorld.SendServerMessage(ServerMessageType::SERVER_MSG_CUSTOM, replyStream.str().c_str());
            if (creating)
            {
                accountState = NierAccountState::NierAccountState_DoLogout;
            }
            else
            {
                Prepare();
                accountState = NierAccountState::NierAccountState_Online;
            }
            checkDelay = urand(1 * IN_MILLISECONDS, 3 * IN_MILLISECONDS);
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
    case NierAccountState_CheckLogout:
    {
        if (me->IsInWorld())
        {
            replyStream << "still in world : " << account_id << " - " << character_id << " - " << me->GetName();
            checkDelay = urand(1 * IN_MILLISECONDS, 3 * IN_MILLISECONDS);
        }
        else
        {
            creating = false;
            replyStream << "offline : " << account_id << " - " << character_id;
            accountState = NierAccountState::NierAccountState_OffLine;
            checkDelay = urand(1 * IN_MILLISECONDS, 3 * IN_MILLISECONDS);
        }
        sWorld.SendServerMessage(ServerMessageType::SERVER_MSG_CUSTOM, replyStream.str().c_str());
        break;
    }
    case NierAccountState_DoLogout:
    {
        if (me->IsInWorld())
        {
            me->GetSession()->LogoutPlayer(true);
            replyStream << "nier logout : " << account_id << " - " << character_id << " - " << me->GetName();
            accountState = NierAccountState::NierAccountState_CheckLogout;
            checkDelay = urand(1 * IN_MILLISECONDS, 3 * IN_MILLISECONDS);
        }
        else
        {
            replyStream << "not in world : " << account_id << " - " << character_id;
            accountState = NierAccountState::NierAccountState_OffLine;
            checkDelay = urand(1 * IN_MILLISECONDS, 3 * IN_MILLISECONDS);
        }
        sWorld.SendServerMessage(ServerMessageType::SERVER_MSG_CUSTOM, replyStream.str().c_str());
        break;
    }
    default:
    {
        break;
    }
    }

    return accountResult;
}

bool Nier_Base::UpdateAction()
{
    bool actionResult = true;

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
        break;
    }
    case NierActionState_Follow:
    {
        Follow();
        break;
    }
    case NierActionState_Tank:
    {
        if (!Tank(actionTargetUnit))
        {
            ClearAction();
            actionResult = false;
        }
        break;
    }
    case NierActionState_Attack:
    {
        if (!Attack(actionTargetUnit))
        {
            ClearAction();
            actionResult = false;
        }
        break;
    }
    case NierActionState_Heal:
    {
        if (!Heal(actionTargetUnit))
        {
            ClearAction();
            actionResult = false;
        }
        break;
    }
    case NierActionState_Cast:
    {
        if (!CastSpell(actionTargetUnit, actionTargetSpell))
        {
            ClearAction();
            actionResult = false;
        }
        break;
    }
    case NierActionState_Assist:
    {
        break;
    }
    case NierActionState_Rest:
    {
        if (me->IsInCombat())
        {
            ClearAction();
            actionResult = false;
        }
        else
        {
            if (Eat())
            {
                break;
            }
            if (Drink())
            {
                break;
            }
        }
        break;
    }
    case NierActionState::NierActionState_Freeze:
    {
        if (me->IsMoving())
        {
            me->StopMoving();
        }
        actionTimeLimit = 1800000;
        break;
    }
    case NierActionState::NierActionState_Assemble:
    {
        if (actionDuration > actionTimeLimit)
        {
            if (actionTargetUnit)
            {
                if (Player* targetPlayer = actionTargetUnit->ToPlayer())
                {
                    if (Teleport(actionTargetUnit->GetMapId(), actionTargetUnit->GetPositionX(), actionTargetUnit->GetPositionY(), actionTargetUnit->GetPositionZ(), actionTargetUnit->GetOrientation()))
                    {
                        sNierManager->WhisperTo(targetPlayer, "coming", me);
                        if (me->IsAlive())
                        {
                            actionState = NierActionState::NierActionState_Teleport;
                            actionDuration = 0;
                            actionTimeLimit = urand(1000, 2000);
                            actionTargetSpell = 0;
                        }
                        else
                        {
                            actionState = NierActionState::NierActionState_Corpse;
                            actionDuration = 0;
                            actionTimeLimit = urand(1000, 3000);
                            actionTargetSpell = 0;
                        }
                    }
                }
            }
        }
        actionResult = false;
        break;
    }
    case NierActionState::NierActionState_Formation:
    {
        if (!me->IsMoving())
        {
            if (me->GetDistance(actionTargetPos) > CONTACT_DISTANCE)
            {
                MoveToPosition(actionTargetPos);
            }
        }
        break;
    }
    case NierActionState::NierActionState_Corpse:
    {
        if (actionDuration > actionTimeLimit)
        {
            if (!me->IsAlive())
            {
                me->ResurrectPlayer(10.0f);
                me->Say("revived", Language::LANG_UNIVERSAL);
            }
        }
        actionResult = false;
        break;
    }
    case NierActionState::NierActionState_Teleport:
    {
        break;
    }
    case NierActionState::NierActionState_Revive:
    {
        break;
    }
    default:
    {
        break;
    }
    }

    if (actionDuration > actionTimeLimit)
    {
        ClearAction();
        actionResult = false;
    }

    return actionResult;
}

bool Nier_Base::UpdateMind()
{
    if (!me)
    {
        return false;
    }
    if (!me->IsInWorld())
    {
        return false;
    }
    if (!me->IsAlive())
    {
        return false;
    }
    if (!me->CanFreeMove())
    {
        return true;
    }
    if (Group* meGroup = me->GetGroup())
    {
        // grouping
        switch (me->nierGroupRole)
        {
        case NierGroupRole::NierGroupRole_Tank:
        {
            // target
            if (Unit* enemy = me->GetSelectedUnit())
            {
                if (me->IsInCombat() && enemy->IsInCombat())
                {
                    float enemyDistance = me->GetDistance(enemy);
                    if (enemyDistance < VISIBILITY_DISTANCE_TINY)
                    {
                        if (Tank(enemy))
                        {
                            return true;
                        }
                    }
                }
            }
            // skull
            ObjectGuid ogSkull = meGroup->GetGuidByTargetIcon(7);
            if (!ogSkull.IsEmpty())
            {
                if (Unit* skull = ObjectAccessor::GetUnit(*me, ogSkull))
                {
                    float skullDistance = me->GetDistance(skull);
                    if (skullDistance < VISIBILITY_DISTANCE_TINY)
                    {
                        if (Tank(skull))
                        {
                            return true;
                        }
                    }
                }
            }
            // leader target 
            if (Player* leader = ObjectAccessor::FindPlayer(meGroup->GetLeaderGuid()))
            {
                if (leader->IsInCombat())
                {
                    if (Unit* leaderTarget = leader->GetSelectedUnit())
                    {
                        float ltDistance = me->GetDistance(leaderTarget);
                        if (ltDistance < INSPECT_DISTANCE)
                        {
                            if (Tank(leaderTarget))
                            {
                                return true;
                            }
                        }
                    }
                }
            }
            std::set<Unit*> attackersSet = me->GetAttackers();
            // attacker
            for (Unit* pAttacker : attackersSet)
            {
                float attackerDistance = me->GetDistance(pAttacker);
                if (attackerDistance < VISIBILITY_DISTANCE_TINY)
                {
                    if (Tank(pAttacker))
                    {
                        return true;
                    }
                }
            }
            break;
        }
        case NierGroupRole::NierGroupRole_Healer:
        {
            if (me->IsInCombat())
            {
                if (Heal(me))
                {
                    return true;
                }
            }
            ObjectGuid ogTank = meGroup->GetGuidByTargetIcon(0);
            if (Player* tank = ObjectAccessor::FindPlayer(ogTank))
            {
                if (tank->IsInCombat())
                {
                    Heal(tank);
                    return true;
                }
            }
            break;
        }
        case NierGroupRole::NierGroupRole_DPS:
        {
            // skull
            ObjectGuid ogSkull = meGroup->GetGuidByTargetIcon(7);
            if (!ogSkull.IsEmpty())
            {
                if (Unit* skull = ObjectAccessor::GetUnit(*me, ogSkull))
                {
                    float skullDistance = me->GetDistance(skull);
                    if (skullDistance < VISIBILITY_DISTANCE_TINY)
                    {
                        if (Attack(skull))
                        {
                            return true;
                        }
                    }
                }
            }
            // tank target 
            ObjectGuid ogTank = meGroup->GetGuidByTargetIcon(0);
            if (!ogTank.IsEmpty())
            {
                if (Player* tank = ObjectAccessor::FindPlayer(ogTank))
                {
                    if (tank->IsInCombat())
                    {
                        if (Unit* tTarget = tank->GetSelectedUnit())
                        {
                            if (Attack(tTarget))
                            {
                                return true;
                            }
                        }
                    }
                }
            }
            // target
            if (Unit* enemy = me->GetSelectedUnit())
            {
                if (me->IsInCombat() && enemy->IsInCombat())
                {
                    float enemyDistance = me->GetDistance(enemy);
                    if (enemyDistance < VISIBILITY_DISTANCE_SMALL)
                    {
                        if (Attack(enemy))
                        {
                            return true;
                        }
                    }
                }
            }
            // leader target 
            if (Player* leader = ObjectAccessor::FindPlayer(meGroup->GetLeaderGuid()))
            {
                if (leader->IsInCombat())
                {
                    if (Unit* leaderTarget = leader->GetSelectedUnit())
                    {
                        float ltDistance = me->GetDistance(leaderTarget);
                        if (ltDistance < INTERACTION_DISTANCE)
                        {
                            if (Attack(leaderTarget))
                            {
                                return true;
                            }
                        }
                    }
                }
            }
            break;
        }
        default:
        {
            break;
        }
        }

        // nearby
        //std::list<Creature*> enemies;
        //MaNGOS::AllCreaturesOfEntryInRange checker(me, 0, VISIBILITY_DISTANCE_TINY);
        //MaNGOS::CreatureListSearcher<MaNGOS::AllCreaturesOfEntryInRange> searcher(enemies, checker);
        //Cell::VisitGridObjects(me, searcher, VISIBILITY_DISTANCE_TINY);
        //for (const auto& eachEnemy : enemies)
        //{
        //    if (Tank(eachEnemy))
        //    {
        //        meGroup->SetTargetIcon(7, eachEnemy->GetObjectGuid());
        //        return true;
        //    }
        //}

        if (Rest())
        {
            return true;
        }
        for (GroupReference* groupRef = meGroup->GetFirstMember(); groupRef != nullptr; groupRef = groupRef->next())
        {
            if (Player* member = groupRef->getSource())
            {
                if (Cure(member))
                {
                    return true;
                }
                if (Buff(member))
                {
                    return true;
                }
                if (Revive(member))
                {
                    actionState = NierActionState::NierActionState_Revive;
                    actionTargetUnit = member;
                    actionDuration = 0;
                    actionTimeLimit = 12000;
                    return true;
                }
            }
        }

        if (Follow())
        {
            return true;
        }
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
            Attack(enemy);
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

    return false;
}

bool Nier_Base::Rest(bool pForce)
{
    if (!me)
    {
        return false;
    }
    if (!me->IsAlive())
    {
        return false;
    }
    if (me->IsInCombat())
    {
        return false;
    }

    float hpp = me->GetHealthPercent();
    float mpp = 100.0f;
    uint32 meClass = me->GetClass();
    if (meClass == Classes::CLASS_HUNTER || meClass == Classes::CLASS_SHAMAN || meClass == Classes::CLASS_PALADIN || meClass == Classes::CLASS_PRIEST || meClass == Classes::CLASS_WARLOCK || meClass == Classes::CLASS_MAGE || meClass == Classes::CLASS_DRUID)
    {
        mpp = me->GetPowerPercent(Powers::POWER_MANA);
    }
    if (pForce || hpp < 50.0f || mpp < 50.0f)
    {
        actionState = NierActionState::NierActionState_Rest;
        actionTimeLimit = 15000;
        return true;
    }

    return false;
}

bool Nier_Base::PVP()
{
    if (Player* target = GetNearbyHostilePlayer())
    {
        if (Attack(target))
        {
            ClearAction();
            actionState = NierActionState::NierActionState_Attack;
            actionTimeLimit = 20000;
            actionTargetUnit = target;
            actionTargetPos = target->GetPosition();

            return true;
        }
    }

    return false;
}

bool Nier_Base::PVE()
{
    if (Unit* target = GetNearbyHostileUnit())
    {
        if (Attack(target))
        {
            ClearAction();
            actionState = NierActionState::NierActionState_Attack;
            actionTimeLimit = 20000;
            actionTargetUnit = target;
            actionTargetPos = target->GetPosition();

            return true;
        }
    }

    return false;
}

bool Nier_Base::Wander()
{
    ClearAction();
    float distance = frand(ATTACK_DISTANCE, VISIBILITY_DISTANCE_TINY);
    float angle = frand(0.0f, 2 * M_PI);
    me->GetNearPoint(me, actionTargetPos.x, actionTargetPos.y, actionTargetPos.z, me->GetObjectBoundingRadius(), distance, angle);
    MoveToPosition(actionTargetPos, false);
    actionState = NierActionState::NierActionState_Wander;
    actionTimeLimit = urand(5000, 10000);

    return true;
}

bool Nier_Base::Idle()
{
    ClearAction();
    actionState = NierActionState::NierActionState_Idle;
    actionTimeLimit = urand(5000, 10000);

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
    if (!pTarget)
    {
        return false;
    }
    if (!me->IsValidAttackTarget(pTarget))
    {
        return false;
    }

    return true;
}

bool Nier_Base::Tank(Unit* pTarget)
{
    if (!me)
    {
        return false;
    }
    if (me->nierGroupRole != NierGroupRole::NierGroupRole_Tank)
    {
        return false;
    }
    if (!me->IsAlive())
    {
        return false;
    }
    if (!pTarget)
    {
        return false;
    }
    if (!me->IsValidAttackTarget(pTarget))
    {
        return false;
    }

    return true;
}

bool Nier_Base::Heal(Unit* pTarget)
{
    if (!me)
    {
        return false;
    }
    if (!me->IsAlive())
    {
        return false;
    }
    if (!pTarget)
    {
        return false;
    }
    if (!pTarget->IsAlive())
    {
        return false;
    }

    return true;
}

bool Nier_Base::Follow()
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
    if (Group* meGroup = me->GetGroup())
    {
        if (Player* leader = ObjectAccessor::FindPlayer(meGroup->GetLeaderGuid()))
        {
            if (me->GetDistance(leader) > VISIBILITY_DISTANCE_SMALL)
            {
                return false;
            }
            ChooseTarget(leader);

            if (me->GetDistance(leader) < followDistance)
            {
                if (me->IsMoving())
                {
                    me->StopMoving();
                }
                if (!me->HasInArc(leader, M_PI_F / 8))
                {
                    me->SetFacingTo(me->GetAngle(leader));
                }
            }
            else
            {
                float destPosTargetDist = leader->GetDistance(actionTargetPos);
                if (destPosTargetDist > followDistance)
                {
                    leader->GetNearPoint(leader, actionTargetPos.x, actionTargetPos.y, actionTargetPos.z, 0.0f, followDistance - ATTACK_DISTANCE, leader->GetAngle(me));
                    MoveToPosition(actionTargetPos);
                }
                else
                {
                    float destPosMeDist = me->GetDistance(actionTargetPos);
                    if (destPosMeDist > CONTACT_DISTANCE)
                    {
                        if (!me->IsMoving())
                        {
                            MoveToPosition(actionTargetPos);
                        }
                    }
                }
            }
        }

        return true;
    }

    return false;
}

bool Nier_Base::Cure(Unit* pTarget)
{
    if (!me)
    {
        return false;
    }
    if (!me->IsAlive())
    {
        return false;
    }
    if (!pTarget)
    {
        return false;
    }
    if (!pTarget->IsAlive())
    {
        return false;
    }

    return true;
}

bool Nier_Base::Buff(Unit* pTarget)
{
    if (!me)
    {
        return false;
    }
    if (!me->IsAlive())
    {
        return false;
    }
    if (!pTarget)
    {
        return false;
    }
    if (!pTarget->IsAlive())
    {
        return false;
    }

    return true;
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
    if (pTarget->IsAlive())
    {
        return false;
    }
    if (me->GetDistance(pTarget) > VISIBILITY_DISTANCE_TINY)
    {
        return false;
    }

    return true;
}

bool Nier_Base::InitializeCharacter(uint32 pTargetLevel)
{
    if (!me)
    {
        return false;
    }

    return true;
}

bool Nier_Base::ResetTalentsAndSpells()
{
    if (!me)
    {
        return false;
    }
    me->ResetTalents(true);

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

void Nier_Base::LearnTalent(uint32 pTalentId, uint32 pMaxRank)
{
    if (!me)
    {
        return;
    }
    uint32 checkRank = 0;
    while (checkRank < pMaxRank)
    {
        me->LearnTalent(pTalentId, checkRank);
        checkRank++;
    }
}

void Nier_Base::TrainSpells(uint32 pTrainerEntry)
{
    if (CreatureInfo const* cInfo = sObjectMgr.GetCreatureTemplate(pTrainerEntry))
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

void Nier_Base::EquipRandomItem(uint32 pEquipSlot)
{

}

void Nier_Base::PetAttack(Unit* pTarget)
{
    if (me)
    {
        if (Pet* myPet = me->GetPet())
        {
            if (myPet->IsAlive())
            {
                if (CreatureAI* cai = myPet->AI())
                {
                    cai->AttackStart(pTarget);
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

bool Nier_Base::UseItem(Item* pItem, Unit* pTarget)
{
    if (!me)
    {
        return false;
    }
    if (me->CanUseItem(pItem) != EQUIP_ERR_OK)
    {
        return false;
    }

    if (me->IsNonMeleeSpellCasted(false, false, true))
    {
        return false;
    }

    if (ItemPrototype const* proto = pItem->GetProto())
    {
        for (uint8 i = 0; i < MAX_ITEM_PROTO_SPELLS; ++i)
        {
            _ItemSpell const& spellData = proto->Spells[i];
            if (sNierManager->HasAura(me, spellData.SpellId))
            {
                return false;
            }
        }
    }
    if (const ItemPrototype* proto = pItem->GetProto())
    {
        ChooseTarget(pTarget);
        SpellCastTargets targets;
        targets.Update(pTarget);
        me->CastItemUseSpell(pItem, targets);
        return true;
    }

    return false;
}

bool Nier_Base::UseItem(Item* pItem, Item* pTarget)
{
    if (!me)
    {
        return false;
    }
    if (me->CanUseItem(pItem) != EQUIP_ERR_OK)
    {
        return false;
    }
    if (me->IsNonMeleeSpellCasted(false, false, true))
    {
        return false;
    }
    if (!pTarget)
    {
        return false;
    }

    if (const ItemPrototype* proto = pItem->GetProto())
    {
        SpellCastTargets targets;
        targets.setItemTarget(pTarget);
        me->CastItemUseSpell(pItem, targets);
        return true;
    }

    return false;
}

bool Nier_Base::CastSpell(Unit* pTarget, uint32 pSpellId, bool pCheckAura, bool pOnlyMyAura, bool pClearShapeShift, uint32 pMaxAuraStack)
{
    if (!SpellValid(pSpellId))
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
    if (const SpellEntry* pS = sSpellMgr.GetSpellEntry(pSpellId))
    {
        if (pTarget)
        {
            if (!me->IsWithinLOSInMap(pTarget))
            {
                return false;
            }
            if (pTarget->IsImmuneToSpell(pS, false))
            {
                return false;
            }
            if (pCheckAura)
            {
                if (pOnlyMyAura)
                {
                    if (sNierManager->HasAura(pTarget, pSpellId, me))
                    {
                        return false;
                    }
                }
                else
                {
                    if (sNierManager->HasAura(pTarget, pSpellId))
                    {
                        return false;
                    }
                }
            }
            if (!me->HasInArc(pTarget, M_PI_F / 8))
            {
                me->SetFacingTo(me->GetAngle(pTarget));
            }
            if (me->GetTargetGuid() != pTarget->GetObjectGuid())
            {
                ChooseTarget(pTarget);
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
        if (pClearShapeShift)
        {
            me->RemoveSpellsCausingAura(SPELL_AURA_MOD_SHAPESHIFT);
        }
        //me->CastSpell(pTarget, pS, TriggerCastFlags::TRIGGERED_NONE);
        //return true;

        SpellCastResult scr = me->CastSpell(pTarget, pS->Id, false);
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
    if (Item* pFood = GetItemInInventory(foodEntry))
    {
        if (UseItem(pFood, me))
        {
            return true;
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
    if (Item* pDrink = GetItemInInventory(drinkEntry))
    {
        if (UseItem(pDrink, me))
        {
            return true;
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
    if (Item* pPotion = GetItemInInventory(potionEntry))
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
        };
        if (Item* pPotion = GetItemInInventory(potionEntry))
        {
            if (UseItem(pPotion, me))
            {
                return true;
            }
        }
    }

    return false;
}

void Nier_Base::ChooseTarget(Unit* pTarget)
{
    if (pTarget)
    {
        if (me)
        {
            me->SetSelectionGuid(pTarget->GetObjectGuid());
            me->SetTargetGuid(pTarget->GetObjectGuid());
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

bool Nier_Base::SpellValid(uint32 pSpellID)
{
    if (pSpellID == 0)
    {
        return false;
    }
    if (!me)
    {
        return false;
    }
    if (!me->IsSpellReady(pSpellID))
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

Player* Nier_Base::GetNearbyHostilePlayer()
{

    if (Player* eachPlayer = me->FindNearestHostilePlayer(VISIBILITY_DISTANCE_NORMAL))
    {
        if (eachPlayer->IsAlive())
        {
            if (me->IsValidAttackTarget(eachPlayer))
            {
                if (eachPlayer->CanDetectStealthOf(me, VISIBILITY_DISTANCE_TINY))
                {
                    return eachPlayer;
                }
            }
        }
    }

    return nullptr;
}

Unit* Nier_Base::GetNearbyHostileUnit()
{
    std::list<Creature*> creatureList;
    me->GetCreatureListWithEntryInGrid(creatureList, 0, VISIBILITY_DISTANCE_TINY);
    if (!creatureList.empty())
    {
        for (std::list<Creature*>::iterator itr = creatureList.begin(); itr != creatureList.end(); ++itr)
        {
            if (Creature* hostileCreature = *itr)
            {
                if (hostileCreature->IsAlive())
                {
                    if (!hostileCreature->IsCivilian())
                    {
                        if (me->IsValidAttackTarget(hostileCreature))
                        {
                            return hostileCreature;
                        }
                    }
                }
            }
        }
    }

    return nullptr;
}

void Nier_Base::MoveToPosition(Position pTargetpos, bool pRun)
{
    me->SetStandState(UnitStandStateType::UNIT_STAND_STATE_STAND);
    if (pRun)
    {
        me->SetWalk(false);
    }
    else
    {
        me->SetWalk(true);
    }
    me->GetMotionMaster()->MovePoint(0, pTargetpos.x, pTargetpos.y, pTargetpos.z, MoveOptions::MOVE_RUN_MODE | MoveOptions::MOVE_PATHFINDING);
}

bool Nier_Base::Chase(Unit* pTarget, float pDistance)
{
    if (me->GetObjectGuid() == pTarget->GetObjectGuid())
    {
        return true;
    }

    bool meInRange = false;
    bool meInLos = false;

    float targetDistance = me->GetDistance(pTarget);
    if (pDistance < ATTACK_DISTANCE)
    {
        if (targetDistance < MIN_MELEE_REACH)
        {
            meInRange = true;
            meInLos = true;
        }
        if (!meInRange)
        {
            float destPosTargetDist = pTarget->GetDistance(actionTargetPos);
            if (destPosTargetDist > DEFAULT_COMBAT_REACH)
            {
                pTarget->GetNearPoint(pTarget, actionTargetPos.x, actionTargetPos.y, actionTargetPos.z, 0.0f, CONTACT_DISTANCE, pTarget->GetAngle(me));
                MoveToPosition(actionTargetPos);
            }
            else
            {
                float destPosMeDist = me->GetDistance(actionTargetPos);
                if (destPosMeDist > CONTACT_DISTANCE)
                {
                    if (!me->IsMoving())
                    {
                        MoveToPosition(actionTargetPos);
                    }
                }
            }
        }
    }
    else
    {
        if (me->GetDistance(pTarget) < pDistance)
        {
            meInRange = true;
        }
        if (me->IsWithinLOSInMap(pTarget))
        {
            meInLos = true;
        }
        if (!meInRange || !meInLos)
        {
            bool destPosInRange = false;
            bool destPosInLos = false;
            float destPosTargetDist = pTarget->GetDistance(actionTargetPos);
            if (destPosTargetDist < pDistance)
            {
                destPosInRange = true;
            }
            if (pTarget->IsWithinLOS(actionTargetPos.x, actionTargetPos.y, actionTargetPos.z, 1.0f))
            {
                destPosInLos = true;
            }
            if (!destPosInRange || !destPosInLos)
            {
                float dynDistance = pDistance - ATTACK_DISTANCE;
                while (dynDistance > CONTACT_DISTANCE)
                {
                    pTarget->GetNearPoint(pTarget, actionTargetPos.x, actionTargetPos.y, actionTargetPos.z, 0.0f, dynDistance, pTarget->GetAngle(me));
                    if (pTarget->IsWithinLOS(actionTargetPos.x, actionTargetPos.y, actionTargetPos.z, 1.0f))
                    {
                        break;
                    }
                    dynDistance = dynDistance - 1.0f;
                }
                MoveToPosition(actionTargetPos);
            }
            else
            {
                float destPosMeDist = me->GetDistance(actionTargetPos);
                if (destPosMeDist > CONTACT_DISTANCE)
                {
                    if (!me->IsMoving())
                    {
                        MoveToPosition(actionTargetPos);
                    }
                }
            }
        }
    }

    if (meInRange && meInLos)
    {
        if (me->IsMoving())
        {
            me->StopMoving();
        }
        if (!me->HasInArc(pTarget, M_PI_F / 8))
        {
            me->SetFacingTo(me->GetAngle(pTarget));
        }
        return true;
    }

    return false;
}

bool Nier_Base::Teleport(uint32 pMapId, float pX, float pY, float pZ, float pO)
{
    if (!me)
    {
        return false;
    }
    if (me->IsAlive())
    {
        me->CombatStop(true);
        me->GetThreatManager().clearReferences();
    }
    me->TeleportTo(pMapId, pX, pY, pZ, pO, TeleportToOptions::TELE_TO_GM_MODE);
    return true;
}

void Nier_Base::EquipOne(uint32 pEquipSlot, uint32 pItemClass, uint32 pItemSubclass, uint32 pInventoryType, uint32 pMinReqLevel, uint32 pMaxReqLevel)
{
    std::ostringstream msgStream;
    std::ostringstream itemQueryStream;
    itemQueryStream << "SELECT entry FROM item_template where class = " << pItemClass << " and subclass = " << pItemSubclass << " and inventory_type = " << pInventoryType << " and required_level >= " << pMinReqLevel << " and required_level <= " << pMaxReqLevel << " and bonding < 4 and allowable_class = -1 and allowable_race = -1 and required_skill = 0 and required_spell = 0 and required_honor_rank = 0 and required_city_rank = 0 and required_reputation_faction = 0 order by rand() ";
    auto itemQR = WorldDatabase.Query(itemQueryStream.str().c_str());
    if (itemQR)
    {
        do
        {
            Field* fields = itemQR->Fetch();
            uint32 itemEntry = fields[0].GetUInt32();

            if (Item* pItem = Item::CreateItem(itemEntry, 1))
            {
                uint16 dest = 0;
                if (me->CanEquipItem(pEquipSlot, dest, pItem, false) == InventoryResult::EQUIP_ERR_OK)
                {
                    me->EquipItem(dest, pItem, true);
                    msgStream << me->GetName() << " Equiped " << pItem->GetProto()->Name1;
                    sWorld.SendServerMessage(ServerMessageType::SERVER_MSG_CUSTOM, msgStream.str().c_str());
                    return;
                }
            }
        } while (itemQR->NextRow());
    }
    msgStream << me->GetName() << " No usable equip " << pEquipSlot << " - " << pMinReqLevel << " - " << pMaxReqLevel;
    sWorld.SendServerMessage(ServerMessageType::SERVER_MSG_CUSTOM, msgStream.str().c_str());
}
