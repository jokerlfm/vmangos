#include "NierManager.h"
#include "NierConfig.h"
#include "Nier_Base.h"
#include "Nier_Druid.h"
#include "Nier_Hunter.h"
#include "Nier_Mage.h"
#include "Nier_Paladin.h"
#include "Nier_Priest.h"
#include "Nier_Rogue.h"
#include "Nier_Shaman.h"
#include "Nier_Warlock.h"
#include "Nier_Warrior.h"

#include "MingManager.h"

#include "CellImpl.h"
#include "GridNotifiers.h"
#include "GridNotifiersImpl.h"
#include "Item.h"
#include "Player.h"
#include "Group.h"
#include "World.h"
#include "AccountMgr.h"
#include "MoveSplineInit.h"
#include "Chat.h"

NierManager::NierManager()
{
    checkDelay = 0;
    allianceRaces.clear();
    hordeRaces.clear();
    nameIndex = 0;
    nierMap.clear();
    nierNameMap.clear();
    characterTalentTabNameMap.clear();
    equipsMap.clear();
}

void NierManager::InitializeManager()
{
    if (sNierConfig.Enable == 0)
    {
        return;
    }

    sLog.Out(LogType::LOG_BASIC, LogLevel::LOG_LVL_BASIC, "Initialize nier");

    checkDelay = 500;

    allianceRaces.clear();
    allianceRaces[CLASS_WARRIOR][allianceRaces[CLASS_WARRIOR].size()] = RACE_HUMAN;
    allianceRaces[CLASS_WARRIOR][allianceRaces[CLASS_WARRIOR].size()] = RACE_NIGHTELF;
    allianceRaces[CLASS_WARRIOR][allianceRaces[CLASS_WARRIOR].size()] = RACE_GNOME;
    allianceRaces[CLASS_WARRIOR][allianceRaces[CLASS_WARRIOR].size()] = RACE_DWARF;
    hordeRaces[CLASS_WARRIOR][hordeRaces[CLASS_WARRIOR].size()] = RACE_ORC;
    hordeRaces[CLASS_WARRIOR][hordeRaces[CLASS_WARRIOR].size()] = Races::RACE_UNDEAD;
    hordeRaces[CLASS_WARRIOR][hordeRaces[CLASS_WARRIOR].size()] = RACE_TAUREN;
    hordeRaces[CLASS_WARRIOR][hordeRaces[CLASS_WARRIOR].size()] = RACE_TROLL;
    //hordeRaces[CLASS_WARRIOR][hordeRaces[CLASS_WARRIOR].size()] = Races::RACE_DRAENEI;

    allianceRaces[CLASS_PALADIN][allianceRaces[CLASS_PALADIN].size()] = RACE_HUMAN;
    allianceRaces[CLASS_PALADIN][allianceRaces[CLASS_PALADIN].size()] = RACE_DWARF;
    //hordeRaces[CLASS_PALADIN][hordeRaces[CLASS_PALADIN].size()] = RACE_BLOODELF;
//    hordeRaces[Classes::CLASS_PALADIN][hordeRaces[Classes::CLASS_PALADIN].size()] = Races::RACE_DRAENEI;

    allianceRaces[CLASS_ROGUE][allianceRaces[CLASS_ROGUE].size()] = RACE_HUMAN;
    allianceRaces[CLASS_ROGUE][allianceRaces[CLASS_ROGUE].size()] = RACE_DWARF;
    allianceRaces[CLASS_ROGUE][allianceRaces[CLASS_ROGUE].size()] = RACE_NIGHTELF;
    allianceRaces[CLASS_ROGUE][allianceRaces[CLASS_ROGUE].size()] = RACE_GNOME;
    hordeRaces[CLASS_ROGUE][hordeRaces[CLASS_ROGUE].size()] = RACE_ORC;
    hordeRaces[CLASS_ROGUE][hordeRaces[CLASS_ROGUE].size()] = RACE_TROLL;
    hordeRaces[CLASS_ROGUE][hordeRaces[CLASS_ROGUE].size()] = Races::RACE_UNDEAD;
    //hordeRaces[Classes::CLASS_ROGUE][hordeRaces[Classes::CLASS_ROGUE].size()] = Races::RACE_BLOODELF;

    allianceRaces[CLASS_PRIEST][allianceRaces[CLASS_PRIEST].size()] = RACE_HUMAN;
    allianceRaces[CLASS_PRIEST][allianceRaces[CLASS_PRIEST].size()] = RACE_DWARF;
    allianceRaces[CLASS_PRIEST][allianceRaces[CLASS_PRIEST].size()] = RACE_NIGHTELF;
    hordeRaces[CLASS_PRIEST][hordeRaces[CLASS_PRIEST].size()] = RACE_TROLL;
    hordeRaces[CLASS_PRIEST][hordeRaces[CLASS_PRIEST].size()] = Races::RACE_UNDEAD;
    //hordeRaces[Classes::CLASS_PRIEST][hordeRaces[Classes::CLASS_PRIEST].size()] = Races::RACE_DRAENEI;
    //hordeRaces[Classes::CLASS_PRIEST][hordeRaces[Classes::CLASS_PRIEST].size()] = Races::RACE_BLOODELF;

    allianceRaces[CLASS_MAGE][allianceRaces[CLASS_MAGE].size()] = RACE_HUMAN;
    allianceRaces[CLASS_MAGE][allianceRaces[CLASS_MAGE].size()] = RACE_GNOME;
    hordeRaces[CLASS_MAGE][hordeRaces[CLASS_MAGE].size()] = Races::RACE_UNDEAD;
    hordeRaces[CLASS_MAGE][hordeRaces[CLASS_MAGE].size()] = RACE_TROLL;/*
    hordeRaces[Classes::CLASS_MAGE][hordeRaces[Classes::CLASS_MAGE].size()] = Races::RACE_DRAENEI;
    hordeRaces[Classes::CLASS_MAGE][hordeRaces[Classes::CLASS_MAGE].size()] = Races::RACE_BLOODELF;*/

    allianceRaces[CLASS_WARLOCK][allianceRaces[CLASS_WARLOCK].size()] = RACE_HUMAN;
    allianceRaces[CLASS_WARLOCK][allianceRaces[CLASS_WARLOCK].size()] = RACE_GNOME;
    hordeRaces[CLASS_WARLOCK][hordeRaces[CLASS_WARLOCK].size()] = Races::RACE_UNDEAD;
    hordeRaces[CLASS_WARLOCK][hordeRaces[CLASS_WARLOCK].size()] = RACE_ORC;
    //hordeRaces[Classes::CLASS_WARLOCK][hordeRaces[Classes::CLASS_WARLOCK].size()] = Races::RACE_BLOODELF;

    //allianceRaces[CLASS_SHAMAN][allianceRaces[CLASS_SHAMAN].size()] = RACE_DRAENEI;
    hordeRaces[CLASS_SHAMAN][hordeRaces[CLASS_SHAMAN].size()] = RACE_ORC;
    hordeRaces[CLASS_SHAMAN][hordeRaces[CLASS_SHAMAN].size()] = RACE_TAUREN;
    hordeRaces[CLASS_SHAMAN][hordeRaces[CLASS_SHAMAN].size()] = RACE_TROLL;
    //hordeRaces[Classes::CLASS_SHAMAN][hordeRaces[Classes::CLASS_SHAMAN].size()] = Races::RACE_DRAENEI;

    allianceRaces[CLASS_HUNTER][allianceRaces[CLASS_HUNTER].size()] = RACE_DWARF;
    allianceRaces[CLASS_HUNTER][allianceRaces[CLASS_HUNTER].size()] = RACE_NIGHTELF;
    hordeRaces[CLASS_HUNTER][hordeRaces[CLASS_HUNTER].size()] = RACE_ORC;
    hordeRaces[CLASS_HUNTER][hordeRaces[CLASS_HUNTER].size()] = RACE_TAUREN;
    hordeRaces[CLASS_HUNTER][hordeRaces[CLASS_HUNTER].size()] = RACE_TROLL;
    //hordeRaces[Classes::CLASS_HUNTER][hordeRaces[Classes::CLASS_HUNTER].size()] = Races::RACE_DRAENEI;
    //hordeRaces[Classes::CLASS_HUNTER][hordeRaces[Classes::CLASS_HUNTER].size()] = Races::RACE_BLOODELF;

    allianceRaces[CLASS_DRUID][allianceRaces[CLASS_DRUID].size()] = RACE_NIGHTELF;
    hordeRaces[CLASS_DRUID][hordeRaces[CLASS_DRUID].size()] = RACE_TAUREN;

    characterTalentTabNameMap.clear();
    characterTalentTabNameMap[Classes::CLASS_WARRIOR][0] = "Arms";
    characterTalentTabNameMap[Classes::CLASS_WARRIOR][1] = "Fury";
    characterTalentTabNameMap[Classes::CLASS_WARRIOR][2] = "Protection";

    characterTalentTabNameMap[Classes::CLASS_HUNTER][0] = "Beast Mastery";
    characterTalentTabNameMap[Classes::CLASS_HUNTER][1] = "Marksmanship";
    characterTalentTabNameMap[Classes::CLASS_HUNTER][2] = "Survival";

    characterTalentTabNameMap[Classes::CLASS_SHAMAN][0] = "Elemental";
    characterTalentTabNameMap[Classes::CLASS_SHAMAN][1] = "Enhancement";
    characterTalentTabNameMap[Classes::CLASS_SHAMAN][2] = "Restoration";

    characterTalentTabNameMap[Classes::CLASS_PALADIN][0] = "Holy";
    characterTalentTabNameMap[Classes::CLASS_PALADIN][1] = "Protection";
    characterTalentTabNameMap[Classes::CLASS_PALADIN][2] = "Retribution";

    characterTalentTabNameMap[Classes::CLASS_WARLOCK][0] = "Affliction";
    characterTalentTabNameMap[Classes::CLASS_WARLOCK][1] = "Demonology";
    characterTalentTabNameMap[Classes::CLASS_WARLOCK][2] = "Destruction";

    characterTalentTabNameMap[Classes::CLASS_PRIEST][0] = "Discipline";
    characterTalentTabNameMap[Classes::CLASS_PRIEST][1] = "Holy";
    characterTalentTabNameMap[Classes::CLASS_PRIEST][2] = "Shadow";

    characterTalentTabNameMap[Classes::CLASS_ROGUE][0] = "Assassination";
    characterTalentTabNameMap[Classes::CLASS_ROGUE][1] = "Combat";
    characterTalentTabNameMap[Classes::CLASS_ROGUE][2] = "subtlety";

    characterTalentTabNameMap[Classes::CLASS_MAGE][0] = "Arcane";
    characterTalentTabNameMap[Classes::CLASS_MAGE][1] = "Fire";
    characterTalentTabNameMap[Classes::CLASS_MAGE][2] = "Frost";

    characterTalentTabNameMap[Classes::CLASS_DRUID][0] = "Balance";
    characterTalentTabNameMap[Classes::CLASS_DRUID][1] = "Feral";
    characterTalentTabNameMap[Classes::CLASS_DRUID][2] = "Restoration";

    if (sNierConfig.Reset)
    {
        DeleteNiers();
    }

    std::unique_ptr<QueryResult> nierQR = CharacterDatabase.Query("SELECT nier_id, master_id, account_name, character_id, target_level, target_race, target_class, target_specialty FROM nier");
    if (nierQR)
    {
        do
        {
            Field* fields = nierQR->Fetch();
            uint32 nier_id= fields[0].GetUInt32();
            uint32 master_id = fields[1].GetUInt32();
            std::string account_name = fields[2].GetString();
            uint32 character_id = fields[3].GetUInt32();
            uint32 target_level = fields[4].GetUInt32();
            uint32 target_race = fields[5].GetUInt32();
            uint32 target_class = fields[6].GetUInt32();
            uint32 target_specialty = fields[7].GetUInt32();

            Nier_Base* nb = nullptr;
            switch (target_class)
            {
            case CLASS_WARRIOR:
            {
                nb = new Nier_Warrior();
                break;
            }
            case CLASS_PALADIN:
            {
nb = new Nier_Paladin();
break;
            }
            case CLASS_HUNTER:
            {
                nb = new Nier_Hunter();
                break;
            }
            case CLASS_ROGUE:
            {
                nb = new Nier_Rogue();
                break;
            }
            case CLASS_PRIEST:
            {
                nb = new Nier_Priest();
                break;
            }
            case CLASS_SHAMAN:
            {
                nb = new Nier_Shaman();
                break;
            }
            case CLASS_MAGE:
            {
                nb = new Nier_Mage();
                break;
            }
            case CLASS_WARLOCK:
            {
                nb = new Nier_Warlock();
                break;
            }
            case CLASS_DRUID:
            {
                nb = new Nier_Druid();
                break;
            }
            default:
            {
                break;
            }
            }
            if (nb)
            {
                nb->nier_id = fields[0].GetUInt32();
                nb->account_name = fields[1].GetString();
                nb->character_id = fields[2].GetUInt32();
                nb->target_level = fields[3].GetUInt32();
                nb->target_race = fields[4].GetUInt32();
                nb->target_class = fields[5].GetUInt32();
                nb->target_specialty = fields[6].GetUInt32();
                nierMap[nier_id] = nb;
            }
        } while (nierQR->NextRow());
    }

    nameIndex = 0;
    std::unique_ptr<QueryResult> nierNameQR = WorldDatabase.Query("SELECT name FROM nier_names order by rand()");
    if (nierNameQR)
    {
        do
        {
            Field* fields = nierNameQR->Fetch();
            std::string eachName = fields[0].GetString();
            nierNameMap[nierNameMap.size()] = eachName;
        } while (nierNameQR->NextRow());
    }

    sLog.Out(LogType::LOG_BASIC, LogLevel::LOG_LVL_BASIC, "nier initialized");
}

NierManager* NierManager::instance()
{
    static NierManager instance;
    return &instance;
}

void NierManager::UpdateNierManager(uint32 pmDiff)
{
    if (sNierConfig.Enable == 0)
    {
        return;
    }

    if (checkDelay >= 0)
    {
        checkDelay -= pmDiff;
    }
    if (checkDelay < 0)
    {
        checkDelay = NIER_MANAGER_CHECK_DELAY;        
        std::unordered_map<uint32, WorldSession*> allSessions = sWorld.GetAllSessions();
        for (std::unordered_map<uint32, WorldSession*>::iterator wsIT = allSessions.begin(); wsIT != allSessions.end(); wsIT++)
        {
            if (WorldSession* eachWS = wsIT->second)
            {
                if (nierMap.find(eachWS->GetAccountId()) == nierMap.end())
                {
                    nierMap[eachWS->GetAccountId()] = nullptr;
                }
            }
        }
    }
}

void NierManager::UpdateNiers(uint32 pDiff)
{
    for (std::unordered_map<uint32, Nier_Base*>::iterator reIT = nierMap.begin(); reIT != nierMap.end(); reIT++)
    {
        if (reIT->second)
        {
            reIT->second->Update(pDiff);
        }
    }
}

void NierManager::LogoutNiers(bool pmInstant)
{
    for (std::unordered_map<uint32, Nier_Base*>::iterator reIT = nierMap.begin(); reIT != nierMap.end(); reIT++)
    {
        if (reIT->second)
        {
            if (pmInstant)
            {
                ObjectGuid playerGuid = ObjectGuid(HIGHGUID_PLAYER, reIT->second->character_id);
                if (Player* eachPlayer = ObjectAccessor::FindPlayer(playerGuid))
                {
                    std::ostringstream logStream;
                    logStream << "Logout nier : " << eachPlayer->GetName();
                    sLog.Out(LogType::LOG_BASIC, LogLevel::LOG_LVL_BASIC, logStream.str().c_str());
                    eachPlayer->GetSession()->LogoutPlayer(true);
                }
            }
            else
            {
                reIT->second->accountState = NierAccountState::NierAccountState_DoLogoff;
                reIT->second->checkDelay = urand(1 * IN_MILLISECONDS, 3 * IN_MILLISECONDS);
            }
        }
    }
}

void NierManager::DeleteNiers()
{
    std::unique_ptr<QueryResult> nierQR = CharacterDatabase.Query("SELECT account_id FROM nier");
    if (nierQR)
    {
        do
        {
            Field* fields = nierQR->Fetch();
            uint32 eachAccountId = fields[0].GetUInt32();
            if (eachAccountId > 0)
            {
                sAccountMgr.DeleteAccount(eachAccountId);
            }
        } while (nierQR->NextRow());
    }

    CharacterDatabase.DirectExecute("delete from nier");

    std::ostringstream accountQueryStream;
    accountQueryStream << "SELECT id FROM account where username like '" << NIER_MARK << "%'";
    std::string accountQuerySQL = accountQueryStream.str();
    std::unique_ptr<QueryResult> nierAccountQR = LoginDatabase.Query(accountQuerySQL.c_str());
    if (nierAccountQR)
    {
        do
        {
            Field* fields = nierAccountQR->Fetch();
            uint32 eachAccountId = fields[0].GetUInt32();
            if (eachAccountId > 0)
            {
                sAccountMgr.DeleteAccount(eachAccountId);
            }
        } while (nierAccountQR->NextRow());
    }
}

bool NierManager::CreateNier(uint32 pMasterId, uint32 pClass)
{
    ObjectGuid masterGuid = ObjectGuid(HIGHGUID_PLAYER, pMasterId);
    if (Player* master = ObjectAccessor::FindPlayer(masterGuid))
    {
        if (master->IsInWorld())
        {
            if (master->GetLevel() >= 20)
            {
                uint32 nier_id = 0;
                std::unique_ptr<QueryResult> targetNierQR = CharacterDatabase.PQuery("SELECT nier_id FROM nier where master_id = %d and target_class = %d", pMasterId, pClass);
                if (targetNierQR)
                {
                    Field* fields = targetNierQR->Fetch();
                    nier_id = fields[0].GetUInt32();
                }
                if (nier_id > 0)
                {
                    std::ostringstream replyStream;
                    replyStream << "nier already exists : " << pMasterId << " - " << pClass;
                    std::string replyString = replyStream.str();
                    sWorld.SendServerMessage(ServerMessageType::SERVER_MSG_CUSTOM, replyString.c_str());
                    sLog.Out(LogType::LOG_BASIC, LogLevel::LOG_LVL_BASIC, replyString.c_str());
                    return false;
                }
                uint32 targetRace = 0;
                if (master->GetTeamId() == TeamId::TEAM_ALLIANCE)
                {
                    uint32 raceIndex = urand(0, allianceRaces[pClass].size() - 1);
                    targetRace = allianceRaces[pClass][raceIndex];
                }
                else
                {
                    uint32 raceIndex = urand(0, hordeRaces[pClass].size() - 1);
                    targetRace = allianceRaces[pClass][raceIndex];
                }

                uint32 maxId = 0;
                std::unique_ptr<QueryResult> maxIdQR = CharacterDatabase.Query("SELECT nier_id FROM nier order by nier_id desc limit 3");
                if (maxIdQR)
                {
                    Field* fields = maxIdQR->Fetch();
                    maxId = fields[0].GetUInt32();
                }
                maxId += 1;
                std::ostringstream accountNameStream;
                accountNameStream << NIER_MARK << maxId;
                std::string checkAccountName = accountNameStream.str();
                std::ostringstream accountQuerySQLStream;
                accountQuerySQLStream << "SELECT id FROM account where username ='" << checkAccountName << "'";
                std::string accountQuerySQL = accountQuerySQLStream.str();
                std::unique_ptr<QueryResult> accountNameQR = LoginDatabase.Query(accountQuerySQL.c_str());
                if (accountNameQR)
                {
                    sLog.Out(LogType::LOG_BASIC, LogLevel::LOG_LVL_ERROR, "Account already %s exists.", checkAccountName);
                    return false;
                }
                if (!sAccountMgr.CreateAccount(checkAccountName, NIER_MARK) == AccountOpResult::AOR_OK)
                {
                    sLog.Out(LogType::LOG_BASIC, LogLevel::LOG_LVL_ERROR, "Account creation failed.", checkAccountName);
                    return false;
                }
                std::unique_ptr<QueryResult> verifyAccountQR = LoginDatabase.Query(accountQuerySQL.c_str());
                if (verifyAccountQR)
                {
                    Field* fields = verifyAccountQR->Fetch();
                    nier_id = fields[0].GetUInt32();
                }
                if (nier_id > 0)
                {
                    std::ostringstream sqlStream;
                    sqlStream << "INSERT INTO nier (nier_id, master_id, account_name, account_id, character_id, target_level, target_race, target_class, target_specialty) VALUES (" << nier_id << ", " << pMasterId << ", '" << checkAccountName << "', " << nier_id << ", " << 0 << ", " << 0 << ", " << targetRace << ", " << pClass << ", " << 1 << ")";
                    std::string sql = sqlStream.str();
                    CharacterDatabase.DirectExecute(sql.c_str());

                    Nier_Base* nb = nullptr;
                    switch (pClass)
                    {
                    case CLASS_WARRIOR:
                    {
                        nb = new Nier_Warrior();
                        break;
                    }
                    case CLASS_PALADIN:
                    {
                        nb = new Nier_Paladin();
                        break;
                    }
                    case CLASS_HUNTER:
                    {
                        nb = new Nier_Hunter();
                        break;
                    }
                    case CLASS_ROGUE:
                    {
                        nb = new Nier_Rogue();
                        break;
                    }
                    case CLASS_PRIEST:
                    {
                        nb = new Nier_Priest();
                        break;
                    }
                    case CLASS_SHAMAN:
                    {
                        nb = new Nier_Shaman();
                        break;
                    }
                    case CLASS_MAGE:
                    {
                        nb = new Nier_Mage();
                        break;
                    }
                    case CLASS_WARLOCK:
                    {
                        nb = new Nier_Warlock();
                        break;
                    }
                    case CLASS_DRUID:
                    {
                        nb = new Nier_Druid();
                        break;
                    }
                    default:
                    {
                        break;
                    }
                    }
                    if (nb)
                    {
                        nb->nier_id = nier_id;
                        nb->master_id = pMasterId;
                        nb->account_name = checkAccountName;
                        nb->account_id = nier_id;
                        nb->character_id = 0;
                        nb->target_level = 0;
                        nb->target_race = targetRace;
                        nb->target_class = pClass;
                        nb->target_specialty = 1;
                        nb->isRobot = true;
                        nierMap[nier_id] = nb;
                    }

                    std::ostringstream replyStream;
                    replyStream << "nier " << checkAccountName << " created";
                    sWorld.SendServerMessage(ServerMessageType::SERVER_MSG_CUSTOM, replyStream.str().c_str());
                    sLog.Out(LogType::LOG_BASIC, LogLevel::LOG_LVL_BASIC, replyStream.str().c_str());
                }
                else
                {
                    sLog.Out(LogType::LOG_BASIC, LogLevel::LOG_LVL_ERROR, "Account creation failed.", checkAccountName);
                    return false;
                }
            }
        }
    }
    return true;
}

bool NierManager::LoginNiers(uint32 pMasterId)
{
    std::unique_ptr<QueryResult> nierQR = CharacterDatabase.PQuery("SELECT nier_id, master_id, account_name, account_id, character_id, target_level, target_race, target_class, target_specialty FROM nier where master_id = %d", pMasterId);
    if (nierQR)
    {
        Field* fields = nierQR->Fetch();
        uint32 nier_id = fields[0].GetUInt32();
        uint32 master_id = fields[1].GetUInt32();
        std::string account_name = fields[2].GetString();
        uint32 character_id = fields[3].GetUInt32();
        uint32 target_level = fields[4].GetUInt32();
        uint32 target_race = fields[5].GetUInt32();
        uint32 target_class = fields[6].GetUInt32();
        uint32 target_specialty = fields[7].GetUInt32();
        Nier_Base* nb = nullptr;
        if (nierMap.find(nier_id) == nierMap.end())
        {
            switch (target_class)
            {
            case CLASS_WARRIOR:
            {
                nb = new Nier_Warrior();
                break;
            }
            case CLASS_PALADIN:
            {
                nb = new Nier_Paladin();
                break;
            }
            case CLASS_HUNTER:
            {
                nb = new Nier_Hunter();
                break;
            }
            case CLASS_ROGUE:
            {
                nb = new Nier_Rogue();
                break;
            }
            case CLASS_PRIEST:
            {
                nb = new Nier_Priest();
                break;
            }
            case CLASS_SHAMAN:
            {
                nb = new Nier_Shaman();
                break;
            }
            case CLASS_MAGE:
            {
                nb = new Nier_Mage();
                break;
            }
            case CLASS_WARLOCK:
            {
                nb = new Nier_Warlock();
                break;
            }
            case CLASS_DRUID:
            {
                nb = new Nier_Druid();
                break;
            }
            default:
            {
                break;
            }
            }
            if (nb)
            {
                nb->nier_id = nier_id;
                nb->master_id = master_id;
                nb->account_name = account_name;
                nb->account_id = nier_id;
                nb->character_id = 0;
                nb->target_level = 0;
                nb->target_race = target_race;
                nb->target_class = target_class;
                nb->target_specialty = 1;
                nb->isRobot = true;
                nierMap[nier_id] = nb;
            }
        }
        else
        {
            nb = nierMap[nier_id];
        }
        if (nb)
        {
            if (nb->accountState == NierAccountState::NierAccountState_OffLine)
            {
                nb->accountState = NierAccountState::NierAccountState_Enter;
                nb->checkDelay = urand(1 * IN_MILLISECONDS, 3 * IN_MILLISECONDS);
            }
            std::ostringstream replyStream;
            replyStream << "nier " << nier_id << " to login";
            sWorld.SendServerMessage(ServerMessageType::SERVER_MSG_CUSTOM, replyStream.str().c_str());
            sLog.Out(LogType::LOG_BASIC, LogLevel::LOG_LVL_BASIC, replyStream.str().c_str());
        }
        else
        {
            std::ostringstream replyStream;
            replyStream << "nier " << nier_id << " has wrong data";
            sWorld.SendServerMessage(ServerMessageType::SERVER_MSG_CUSTOM, replyStream.str().c_str());
            sLog.Out(LogType::LOG_BASIC, LogLevel::LOG_LVL_ERROR, replyStream.str().c_str());
        }
    }

    return true;
}

bool NierManager::IsPolymorphed(Unit* pmTarget)
{
    if (pmTarget)
    {
        if (pmTarget->HasAura(118) || pmTarget->HasAura(12824) || pmTarget->HasAura(12825) || pmTarget->HasAura(12826))
        {
            return true;
        }
        if (pmTarget->HasAura(2637) || pmTarget->HasAura(18657) || pmTarget->HasAura(18658))
        {
            return true;
        }
        if (pmTarget->HasAura(339) || pmTarget->HasAura(1062) || pmTarget->HasAura(5195) || pmTarget->HasAura(5196) || pmTarget->HasAura(9852) || pmTarget->HasAura(9853) || pmTarget->HasAura(26989) || pmTarget->HasAura(53308))
        {
            return true;
        }
    }

    return false;
}

Position NierManager::PredictPosition(Unit* target)
{
    Position pos = target->GetPosition();

    float speed = target->GetSpeed(UnitMoveType::MOVE_RUN);
    float orientation = target->GetOrientation();

    if (target->m_movementInfo.HasMovementFlag(MovementFlags::MOVEFLAG_FORWARD))
    {
        pos.x += cos(orientation) * speed;
        pos.y += std::sin(orientation) * speed;
    }
    else if (target->m_movementInfo.HasMovementFlag(MovementFlags::MOVEFLAG_BACKWARD))
    {
        pos.x -= cos(orientation) * speed;
        pos.y -= std::sin(orientation) * speed;
    }

    if (target->m_movementInfo.HasMovementFlag(MovementFlags::MOVEFLAG_STRAFE_LEFT))
    {
        pos.x += cos(orientation + M_PI / 2.f) * speed;
        pos.y += std::sin(orientation + M_PI / 2.f) * speed;
    }
    else if (target->m_movementInfo.HasMovementFlag(MovementFlags::MOVEFLAG_STRAFE_RIGHT))
    {
        pos.x += cos(orientation - M_PI / 2.f) * speed;
        pos.y += std::sin(orientation - M_PI / 2.f) * speed;
    }

    return pos;
}

void NierManager::HandleNierChatCommand(Player* pCommander, std::string pContent)
{
    if (!pCommander)
    {
        return;
    }
    std::vector<std::string> pCommandVector = sMingManager->SplitString(pContent, " ", true);
    // todo : analysis command range 
    Player* targetPlayer = nullptr;
    uint32 nierId = targetPlayer->GetSession()->GetAccountId();
    HandleNierChatCommand(pCommander, pCommandVector, nierId);
}

void NierManager::HandleNierChatCommand(Player* pCommander, std::vector<std::string> pCommandVector, uint32 pNierId)
{
    if (nierMap.find(pNierId) != nierMap.end())
    {
        Nier_Base* nb = nierMap[pNierId];
        if (nb)
        {
            std::string commandName = pCommandVector.at(0);
            if (commandName == "role")
            {
                std::ostringstream replyStream;
                if (pCommandVector.size() > 1)
                {
                    std::string newRole = pCommandVector.at(1);
                    if (newRole == "tank")
                    {
                        nb->groupRole = NierGroupRole::NierGroupRole_Tank;
                    }
                    else if (newRole == "healer")
                    {
                        nb->groupRole = NierGroupRole::NierGroupRole_Healer;
                    }
                    else if (newRole == "dps")
                    {
                        nb->groupRole = NierGroupRole::NierGroupRole_DPS;
                    }
                }
                if (nb->groupRole == NierGroupRole::NierGroupRole_Tank)
                {
                    replyStream << "Role is tank";
                }
                else if (nb->groupRole == NierGroupRole::NierGroupRole_Healer)
                {
                    replyStream << "Role is healer";
                }
                else if (nb->groupRole == NierGroupRole::NierGroupRole_DPS)
                {
                    replyStream << "Role is dps";
                }
                if (nb->me)
                {
                    WhisperTo(pCommander, replyStream.str(), Language::LANG_UNIVERSAL, nb->me);
                }
                else
                {
                    sWorld.SendServerMessage(ServerMessageType::SERVER_MSG_CUSTOM, replyStream.str().c_str(), pCommander);
                }
            }
            else if (commandName == "who")
            {
                if (nb->isRobot)
                {
                    if (nb->me)
                    {
                        std::ostringstream replyStream;
                        replyStream << characterTalentTabNameMap[nb->me->GetClass()][nb->specialty];
                        WhisperTo(pCommander, replyStream.str(), Language::LANG_UNIVERSAL, nb->me);
                    }
                }
            }
            else if (commandName == "emote")
            {
                if (nb->me)
                {
                    std::string emoteContents = pCommandVector.at(1);
                    int emoteNumber = atoi(emoteContents.c_str());
                    nb->me->HandleEmoteCommand(emoteNumber);
                }
            }
            else if (commandName == "assemble")
            {
                std::ostringstream replyStream;
                if (pmTargetPlayer)
                {
                    if (pmTargetPlayer->isNier)
                    {
                        if (NierStrategy_Base* ns = pmTargetPlayer->nierStrategyMap[pmTargetPlayer->activeStrategyIndex])
                        {
                            if (!pmTargetPlayer->IsAlive())
                            {
                                ns->assembleDelay = 120000;
                                replyStream << "Corpserun 120 seconds";
                            }
                            else
                            {
                                ns->assembleDelay = 60000;
                                replyStream << "Assemble in 60 seconds";
                            }
                            WhisperTo(pCommander, replyStream.str(), Language::LANG_UNIVERSAL, pmTargetPlayer);
                        }
                    }
                }
                else if (pmTargetGroup)
                {
                    for (GroupReference* groupRef = pmTargetGroup->GetFirstMember(); groupRef != nullptr; groupRef = groupRef->next())
                    {
                        Player* member = groupRef->getSource();
                        if (member)
                        {
                            if (member->GetObjectGuid() != pCommander->GetObjectGuid())
                            {
                                HandleChatCommand(pCommander, pmContent, member, pmTargetGroup);
                            }
                        }
                    }
                }
            }
            else if (commandName == "join")
            {
                if (pCommandVector.size() > 1)
                {
                    std::string joinName = pCommandVector.at(1);
                    if (Player* targetPlayer = ObjectAccessor::FindPlayerByName(joinName.c_str()))
                    {
                        pCommander->TeleportTo(targetPlayer->GetMapId(), targetPlayer->GetPositionX(), targetPlayer->GetPositionY(), targetPlayer->GetPositionZ(), targetPlayer->GetOrientation());
                    }
                }
                else
                {
                    if (Player* targetPlayer = pCommander->GetSelectedPlayer())
                    {
                        if (targetPlayer->IsInSameGroupWith(pCommander))
                        {
                            pCommander->TeleportTo(targetPlayer->GetMapId(), targetPlayer->GetPositionX(), targetPlayer->GetPositionY(), targetPlayer->GetPositionZ(), targetPlayer->GetOrientation());
                        }
                    }
                }
            }
            else if (commandName == "leader")
            {
                if (pmTargetGroup)
                {
                    if (pmTargetGroup->GetLeaderGuid() != pCommander->GetObjectGuid())
                    {
                        bool change = true;
                        if (Player* leader = ObjectAccessor::FindPlayer(pmTargetGroup->GetLeaderGuid()))
                        {
                            if (WorldSession* leaderSession = leader->GetSession())
                            {
                                if (!leaderSession->isNier)
                                {
                                    change = false;
                                }
                            }
                        }
                        if (change)
                        {
                            pmTargetGroup->ChangeLeader(pCommander->GetObjectGuid());
                        }
                        else
                        {
                            sWorld.SendServerMessage(ServerMessageType::SERVER_MSG_CUSTOM, "Leader is valid", pCommander);
                        }
                    }
                    else
                    {
                        sWorld.SendServerMessage(ServerMessageType::SERVER_MSG_CUSTOM, "You are the leader", pCommander);
                    }
                }
                else
                {
                    sWorld.SendServerMessage(ServerMessageType::SERVER_MSG_CUSTOM, "You are not in a group", pCommander);
                }
            }
            else if (commandName == "nier")
            {
                if (pCommandVector.size() > 1)
                {
                    std::string nierAction = pCommandVector.at(1);
                    if (nierAction == "reset")
                    {
                        std::ostringstream replyStream;
                        bool allOffline = true;
                        for (std::unordered_set<NierEntity*>::iterator reIT = nierEntitySet.begin(); reIT != nierEntitySet.end(); reIT++)
                        {
                            if (NierEntity* eachRE = *reIT)
                            {
                                if (eachRE->entityState != NierEntityState::NierEntityState_None && eachRE->entityState != NierEntityState::NierEntityState_OffLine)
                                {
                                    allOffline = false;
                                    replyStream << "Not all niers are offline. Going offline first";
                                    LogoutNiers();
                                    break;
                                }
                            }
                        }
                        if (allOffline)
                        {
                            replyStream << "All niers are offline. Ready to delete";
                            DeleteNiers();
                        }
                        sWorld.SendServerMessage(ServerMessageType::SERVER_MSG_CUSTOM, replyStream.str().c_str(), pCommander);
                    }
                    else if (nierAction == "offline")
                    {
                        std::ostringstream replyStream;
                        replyStream << "All niers are going offline";
                        LogoutNiers();
                        sWorld.SendServerMessage(ServerMessageType::SERVER_MSG_CUSTOM, replyStream.str().c_str(), pCommander);
                    }
                    else if (nierAction == "online")
                    {
                        uint32 playerLevel = pCommander->GetLevel();
                        if (playerLevel < 10)
                        {
                            std::ostringstream replyStream;
                            replyStream << "You level is too low";
                            sWorld.SendServerMessage(ServerMessageType::SERVER_MSG_CUSTOM, replyStream.str().c_str(), pCommander);
                        }
                        else
                        {
                            uint32 nierCount = sNierConfig.NierCountEachLevel;
                            if (pCommandVector.size() > 2)
                            {
                                nierCount = atoi(pCommandVector.at(2).c_str());
                            }
                            if (nierCount > 0)
                            {
                                std::ostringstream replyTitleStream;
                                replyTitleStream << "nier count to go online : " << nierCount;
                                sWorld.SendServerMessage(ServerMessageType::SERVER_MSG_CUSTOM, replyTitleStream.str().c_str(), pCommander);
                                LoginNier(playerLevel, nierCount);
                            }
                        }
                    }
                    else if (nierAction == "home")
                    {
                        std::unordered_map<uint32, WorldSession*> allSessions = sWorld.GetAllSessions();
                        for (std::unordered_map<uint32, WorldSession*>::iterator wsIT = allSessions.begin(); wsIT != allSessions.end(); wsIT++)
                        {
                            if (WorldSession* eachWS = wsIT->second)
                            {
                                if (eachWS->isNier)
                                {
                                    if (Player* eachNier = eachWS->GetPlayer())
                                    {
                                        if (eachNier->IsInWorld())
                                        {
                                            eachNier->TeleportToHomebind();

                                            std::ostringstream replyTitleStream;
                                            replyTitleStream << "Teleport nier to homebind : " << eachNier->GetName();
                                            sWorld.SendServerMessage(ServerMessageType::SERVER_MSG_CUSTOM, replyTitleStream.str().c_str(), pCommander);
                                        }
                                    }
                                }
                            }
                        }
                    }
                    else if (nierAction == "relocate")
                    {
                        std::unordered_map<uint32, WorldSession*> allSessions = sWorld.GetAllSessions();
                        for (std::unordered_map<uint32, WorldSession*>::iterator wsIT = allSessions.begin(); wsIT != allSessions.end(); wsIT++)
                        {
                            if (WorldSession* eachWS = wsIT->second)
                            {
                                if (eachWS->isNier)
                                {
                                    if (Player* eachNier = eachWS->GetPlayer())
                                    {
                                        if (eachNier->IsInWorld())
                                        {
                                            if (NierStrategy_Base* ns = eachNier->nierStrategyMap[eachNier->activeStrategyIndex])
                                            {
                                                ns->randomTeleportDelay = urand(sNierConfig.RandomTeleportDelay_Min, sNierConfig.RandomTeleportDelay_Max);
                                                if (eachNier->nierAction->RandomTeleport())
                                                {
                                                    std::ostringstream replyTitleStream;
                                                    replyTitleStream << "Random teleport nier : " << eachNier->GetName();
                                                    sWorld.SendServerMessage(ServerMessageType::SERVER_MSG_CUSTOM, replyTitleStream.str().c_str(), pCommander);
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            else if (commandName == "engage")
            {
                if (pmTargetPlayer)
                {
                    if (NierStrategy_Base* ns = pmTargetPlayer->nierStrategyMap[pmTargetPlayer->activeStrategyIndex])
                    {
                        if (ns->basicStrategyType == BasicStrategyType::BasicStrategyType_Freeze || ns->basicStrategyType == BasicStrategyType::BasicStrategyType_Glue)
                        {
                            ns->basicStrategyType = BasicStrategyType::BasicStrategyType_Normal;
                        }
                        if (Unit* target = pCommander->GetSelectedUnit())
                        {
                            if (ns->Engage(target))
                            {
                                int engageLimit = DEFAULT_ACTION_LIMIT_DELAY;
                                if (pCommandVector.size() > 1)
                                {
                                    std::string checkStr = pCommandVector.at(1);
                                    engageLimit = atoi(checkStr.c_str());
                                }
                                ns->actionLimit = engageLimit;
                                ns->ogActionTarget = target->GetObjectGuid();
                                ns->actionType = ActionType::ActionType_Engage;
                                std::ostringstream replyStream;
                                replyStream << "Try to engage " << target->GetName();
                                WhisperTo(pCommander, replyStream.str(), Language::LANG_UNIVERSAL, pmTargetPlayer);
                            }
                        }
                    }
                }
                else if (pmTargetGroup)
                {
                    for (GroupReference* groupRef = pmTargetGroup->GetFirstMember(); groupRef != nullptr; groupRef = groupRef->next())
                    {
                        Player* member = groupRef->getSource();
                        if (member)
                        {
                            if (member->GetObjectGuid() != pCommander->GetObjectGuid())
                            {
                                HandleChatCommand(pCommander, pmContent, member);
                            }
                        }
                    }
                }
            }
            else if (commandName == "tank")
            {
                if (pmTargetPlayer)
                {
                    if (NierStrategy_Base* ns = pmTargetPlayer->nierStrategyMap[pmTargetPlayer->activeStrategyIndex])
                    {
                        if (Unit* target = pCommander->GetSelectedUnit())
                        {
                            if (ns->basicStrategyType == BasicStrategyType::BasicStrategyType_Freeze || ns->basicStrategyType == BasicStrategyType::BasicStrategyType_Glue)
                            {
                                ns->basicStrategyType = BasicStrategyType::BasicStrategyType_Normal;
                            }
                            if (pmTargetPlayer->groupRole == NierGroupRole::NierGroupRole_Tank)
                            {
                                if (ns->DoTank(target, false))
                                {
                                    if (Group* tankGroup = pmTargetPlayer->GetGroup())
                                    {
                                        tankGroup->SetTargetIcon(7, target->GetObjectGuid());
                                        for (GroupReference* groupRef = tankGroup->GetFirstMember(); groupRef != nullptr; groupRef = groupRef->next())
                                        {
                                            if (Player* member = groupRef->getSource())
                                            {
                                                if (member->GetObjectGuid() != pCommander->GetObjectGuid())
                                                {
                                                    if (member->GetSession()->isNier)
                                                    {
                                                        if (member->nierAction->ReadyTank(pmTargetPlayer))
                                                        {
                                                            if (NierStrategy_Base* nsAction = member->nierStrategyMap[pmTargetPlayer->activeStrategyIndex])
                                                            {
                                                                nsAction->ogActionTarget = pmTargetPlayer->GetObjectGuid();
                                                                nsAction->actionType = ActionType::ActionType_ReadyTank;
                                                                nsAction->actionLimit = 2000;
                                                            }
                                                            break;
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                    int engageLimit = DEFAULT_ACTION_LIMIT_DELAY;
                                    if (pCommandVector.size() > 1)
                                    {
                                        std::string checkStr = pCommandVector.at(1);
                                        engageLimit = atoi(checkStr.c_str());
                                    }
                                    ns->actionLimit = engageLimit;
                                    ns->ogActionTarget = target->GetObjectGuid();
                                    ns->actionType = ActionType::ActionType_Engage;
                                    std::ostringstream replyStream;
                                    replyStream << "Try to engage " << target->GetName();
                                    WhisperTo(pCommander, replyStream.str(), Language::LANG_UNIVERSAL, pmTargetPlayer);
                                }
                            }
                        }
                    }
                }
                else if (pmTargetGroup)
                {
                    for (GroupReference* groupRef = pmTargetGroup->GetFirstMember(); groupRef != nullptr; groupRef = groupRef->next())
                    {
                        Player* member = groupRef->getSource();
                        if (member)
                        {
                            if (member->GetObjectGuid() != pCommander->GetObjectGuid())
                            {
                                HandleChatCommand(pCommander, pmContent, member);
                            }
                        }
                    }
                }
            }
            else if (commandName == "freeze")
            {
                if (pmTargetPlayer)
                {
                    if (NierStrategy_Base* ns = pmTargetPlayer->nierStrategyMap[pmTargetPlayer->activeStrategyIndex])
                    {
                        ns->basicStrategyType = BasicStrategyType::BasicStrategyType_Freeze;
                        pmTargetPlayer->nierAction->nm->ResetMovement();
                        pmTargetPlayer->InterruptNonMeleeSpells(true);
                        pmTargetPlayer->AttackStop();
                        pmTargetPlayer->nierAction->PetStop();
                        std::ostringstream replyStream;
                        replyStream << "Freezed";
                        WhisperTo(pCommander, replyStream.str(), Language::LANG_UNIVERSAL, pmTargetPlayer);
                    }
                }
                else if (pmTargetGroup)
                {
                    for (GroupReference* groupRef = pmTargetGroup->GetFirstMember(); groupRef != nullptr; groupRef = groupRef->next())
                    {
                        Player* member = groupRef->getSource();
                        if (member)
                        {
                            if (member->GetObjectGuid() != pCommander->GetObjectGuid())
                            {
                                HandleChatCommand(pCommander, pmContent, member);
                            }
                        }
                    }
                }
            }
            else if (commandName == "rest")
            {
                if (pmTargetPlayer)
                {
                    if (NierStrategy_Base* ns = pmTargetPlayer->nierStrategyMap[pmTargetPlayer->activeStrategyIndex])
                    {
                        ns->Rest(true);
                        WhisperTo(pCommander, "Resting", Language::LANG_UNIVERSAL, pmTargetPlayer);
                    }
                }
                else if (pmTargetGroup)
                {
                    for (GroupReference* groupRef = pmTargetGroup->GetFirstMember(); groupRef != nullptr; groupRef = groupRef->next())
                    {
                        Player* member = groupRef->getSource();
                        if (member)
                        {
                            if (member->GetObjectGuid() != pCommander->GetObjectGuid())
                            {
                                HandleChatCommand(pCommander, pmContent, member);
                            }
                        }
                    }
                }
            }
            else if (commandName == "revive")
            {
                if (pmTargetPlayer)
                {
                    if (NierStrategy_Base* ns = pmTargetPlayer->nierStrategyMap[pmTargetPlayer->activeStrategyIndex])
                    {
                        if (Unit* target = pCommander->GetSelectedUnit())
                        {
                            if (ns->Revive(target))
                            {
                                ns->actionLimit = DEFAULT_ACTION_LIMIT_DELAY;
                                ns->ogActionTarget = target->GetObjectGuid();
                                ns->actionType = ActionType::ActionType_Revive;
                                std::ostringstream replyStream;
                                replyStream << "Try to do reviving";
                                WhisperTo(pCommander, replyStream.str(), Language::LANG_UNIVERSAL, pmTargetPlayer);
                            }
                        }
                    }
                }
                else if (pmTargetGroup)
                {
                    for (GroupReference* groupRef = pmTargetGroup->GetFirstMember(); groupRef != nullptr; groupRef = groupRef->next())
                    {
                        Player* member = groupRef->getSource();
                        if (member)
                        {
                            if (member->GetObjectGuid() != pCommander->GetObjectGuid())
                            {
                                HandleChatCommand(pCommander, pmContent, member);
                            }
                        }
                    }
                }
            }
        }
    }
}

void NierManager::HandlePacket(const WorldSession* pmSession, WorldPacket pmPacket)
{
    switch (pmPacket.GetOpcode())
    {
    case SMSG_CHAR_ENUM:
    {
        std::unordered_set<uint32> myCharacterIdSet;
        QueryResult* characterQR = CharacterDatabase.PQuery("SELECT guid FROM characters where account = %d", pmSession->GetAccountId());
        if (characterQR)
        {
            Field* characterFields = characterQR->Fetch();
            uint32 character_id = characterFields[0].GetUInt32();
            if (character_id > 0)
            {
                myCharacterIdSet.insert(character_id);
            }
        }
        delete characterQR;
        for (std::unordered_set<NierEntity*>::iterator reIT = sNierManager->nierEntitySet.begin(); reIT != sNierManager->nierEntitySet.end(); reIT++)
        {
            if (NierEntity* re = *reIT)
            {
                if (myCharacterIdSet.find(re->character_id) != myCharacterIdSet.end())
                {
                    re->entityState = NierEntityState::NierEntityState_DoLogin;
                }
            }
        }
        break;
    }
    case SMSG_SPELL_FAILURE:
    {
        break;
    }
    case SMSG_SPELL_DELAYED:
    {
        break;
    }
    case SMSG_GROUP_INVITE:
    {
        if (Player* receiver = pmSession->GetPlayer())
        {
            if (!pmSession->GetPlayer())
            {
                break;
            }
            else if (!receiver->IsInWorld())
            {
                break;
            }
            else if (!receiver->nierAction)
            {
                break;
            }
            if (Group* myGroup = receiver->GetGroup())
            {
                receiver->RemoveFromGroup();
                Player::BoundInstancesMap& binds = receiver->GetBoundInstances();
                for (Player::BoundInstancesMap::iterator itr = binds.begin(); itr != binds.end(); itr++)
                {
                    receiver->UnbindInstance(itr);
                }
            }
            if (Group* grp = receiver->GetGroupInvite())
            {
                Player::BoundInstancesMap& binds = receiver->GetBoundInstances();
                for (Player::BoundInstancesMap::iterator itr = binds.begin(); itr != binds.end(); itr++)
                {
                    receiver->UnbindInstance(itr);
                }
                WorldPacket wpAccept(CMSG_GROUP_ACCEPT, 4);
                wpAccept << uint32(0);
                receiver->GetSession()->HandleGroupAcceptOpcode(wpAccept);
                std::ostringstream replyStream_Talent;
                receiver->nierAction->Reset();
                replyStream_Talent << sNierManager->characterTalentTabNameMap[receiver->GetClass()][receiver->nierAction->specialty];
                if (Player* inviter = ObjectAccessor::FindPlayer(grp->GetLeaderGuid()))
                {
                    WhisperTo(inviter, replyStream_Talent.str(), Language::LANG_UNIVERSAL, receiver);
                }
                if (receiver->GetClass() == Classes::CLASS_ROGUE)
                {
                    if (Nier_Rogue* nar = (Nier_Rogue*)receiver->nierAction)
                    {
                        nar->CancelAura(nar->spell_Stealth);
                    }
                }
            }
        }
        break;
    }
    case BUY_ERR_NOT_ENOUGHT_MONEY:
    {
        break;
    }
    case BUY_ERR_REPUTATION_REQUIRE:
    {
        break;
    }
    case MSG_RAID_READY_CHECK:
    {
        break;
    }
    case SMSG_GROUP_SET_LEADER:
    {
        //std::string leaderName = "";
        //pmPacket >> leaderName;
        //Player* newLeader = ObjectAccessor::FindPlayerByName(leaderName);
        //if (newLeader)
        //{
        //    if (newLeader->GetObjectGuid() == me->GetObjectGuid())
        //    {
        //        WorldPacket data(CMSG_GROUP_SET_LEADER, 8);
        //        data << master->GetObjectGuid().WriteAsPacked();
        //        me->GetSession()->HandleGroupSetLeaderOpcode(data);
        //    }
        //    else
        //    {
        //        if (!newLeader->isnier)
        //        {
        //            master = newLeader;
        //        }
        //    }
        //}
        break;
    }
    case SMSG_RESURRECT_REQUEST:
    {
        if (Player* receiver = pmSession->GetPlayer())
        {
            if (!receiver)
            {
                break;
            }
            else if (!receiver->IsInWorld())
            {
                break;
            }
            else if (!receiver->nierAction)
            {
                break;
            }
            if (receiver->IsRessurectRequested())
            {
                receiver->ResurectUsingRequestData();
                receiver->ClearInCombat();
                receiver->nierAction->ClearTarget();
                receiver->nierAction->nm->ResetMovement();
            }
        }
        break;
    }
    case SMSG_INVENTORY_CHANGE_FAILURE:
    {
        break;
    }
    case SMSG_TRADE_STATUS:
    {
        break;
    }
    case SMSG_LOOT_RESPONSE:
    {
        break;
    }
    case SMSG_ITEM_PUSH_RESULT:
    {
        break;
    }
    case SMSG_PARTY_COMMAND_RESULT:
    {
        break;
    }
    case SMSG_DUEL_REQUESTED:
    {
        if (Player* receiver = pmSession->GetPlayer())
        {
            if (!receiver)
            {
                break;
            }
            if (!receiver->duel)
            {
                break;
            }
            receiver->DuelComplete(DuelCompleteType::DUEL_INTERRUPTED);
            WhisperTo(receiver->duel->opponent, "Not interested", Language::LANG_UNIVERSAL, receiver);
        }
        break;
    }
    default:
    {
        break;
    }
    }
}

void NierManager::WhisperTo(Player* pmTarget, std::string pmContent, Language pmLanguage, Player* pmSender)
{
    if (pmSender && pmTarget)
    {
        WorldPacket data;
        ChatHandler::BuildChatPacket(data, CHAT_MSG_WHISPER, pmContent.c_str(), Language::LANG_UNIVERSAL, 0, pmSender->GetObjectGuid(), pmSender->GetName(), pmTarget->GetObjectGuid(), pmTarget->GetName());
        pmTarget->GetSession()->SendPacket(&data);
    }
}

bool NierManager::HasAura(Unit* pmTarget, uint32 pmSpellId, Unit* pmCaster)
{
    if (!pmTarget)
    {
        return false;
    }
    if (pmCaster)
    {
        std::multimap< uint32, SpellAuraHolder*> sahMap = pmTarget->GetSpellAuraHolderMap();
        for (std::multimap< uint32, SpellAuraHolder*>::iterator sahIT = sahMap.begin(); sahIT != sahMap.end(); sahIT++)
        {
            if (pmSpellId == sahIT->first)
            {
                if (SpellAuraHolder* eachSAH = sahIT->second)
                {
                    if (eachSAH->GetCasterGuid() == pmCaster->GetObjectGuid())
                    {
                        return true;
                    }
                }
            }
        }
    }
    else
    {
        if (pmTarget->HasAura(pmSpellId))
        {
            return true;
        }
    }

    return false;
}

bool NierManager::MissingAura(Unit* pmTarget, uint32 pmSpellId, Unit* pmCaster)
{
    if (!pmTarget)
    {
        return false;
    }
    bool castOnSelf = false;
    if (pmTarget->GetObjectGuid() == pmCaster->GetObjectGuid())
    {
        castOnSelf = true;
    }
    if (const SpellEntry* pS = sSpellMgr.GetSpellEntry(pmSpellId))
    {
        if (pmTarget->IsImmuneToSpell(pS, castOnSelf))
        {
            return false;
        }
    }
    if (pmCaster)
    {
        std::multimap< uint32, SpellAuraHolder*> sahMap = pmTarget->GetSpellAuraHolderMap();
        for (std::multimap< uint32, SpellAuraHolder*>::iterator sahIT = sahMap.begin(); sahIT != sahMap.end(); sahIT++)
        {
            if (pmSpellId == sahIT->first)
            {
                if (SpellAuraHolder* eachSAH = sahIT->second)
                {
                    if (eachSAH->GetCasterGuid() == pmCaster->GetObjectGuid())
                    {
                        return false;
                    }
                }
            }
        }
    }
    else
    {
        if (pmTarget->HasAura(pmSpellId))
        {
            return false;
        }
    }

    return true;
}

uint32 NierManager::GetAuraDuration(Unit* pmTarget, uint32 pmSpellId, Unit* pmCaster)
{
    if (!pmTarget)
    {
        return false;
    }
    uint32 duration = 0;
    if (pmCaster)
    {
        std::multimap< uint32, SpellAuraHolder*> sahMap = pmTarget->GetSpellAuraHolderMap();
        for (std::multimap< uint32, SpellAuraHolder*>::iterator sahIT = sahMap.begin(); sahIT != sahMap.end(); sahIT++)
        {
            if (pmSpellId == sahIT->first)
            {
                if (SpellAuraHolder* eachSAH = sahIT->second)
                {
                    if (eachSAH->GetCasterGuid() == pmCaster->GetObjectGuid())
                    {
                        duration = eachSAH->GetAuraDuration();
                    }
                }
            }
        }
    }
    else
    {
        if (Aura* destAura = pmTarget->GetAura(pmSpellId, SpellEffectIndex::EFFECT_INDEX_0))
        {
            duration = destAura->GetAuraDuration();
        }
    }

    return duration;
}

uint32 NierManager::GetAuraStack(Unit* pmTarget, uint32 pmSpellId, Unit* pmCaster)
{
    uint32 auraStack = 0;
    if (!pmTarget)
    {
        return false;
    }
    if (pmCaster)
    {
        std::multimap< uint32, SpellAuraHolder*> sahMap = pmTarget->GetSpellAuraHolderMap();
        for (std::multimap< uint32, SpellAuraHolder*>::iterator sahIT = sahMap.begin(); sahIT != sahMap.end(); sahIT++)
        {
            if (pmSpellId == sahIT->first)
            {
                if (SpellAuraHolder* eachSAH = sahIT->second)
                {
                    if (eachSAH->GetCasterGuid() == pmCaster->GetObjectGuid())
                    {
                        auraStack = eachSAH->GetStackAmount();
                    }
                }
            }
        }
    }
    else
    {
        if (Aura* destAura = pmTarget->GetAura(pmSpellId, SpellEffectIndex::EFFECT_INDEX_0))
        {
            auraStack = destAura->GetStackAmount();
        }
    }

    return auraStack;
}

std::unordered_set<Creature*> NierManager::GetCreatureSetInRange(Unit* pSearcher, uint32 pCreatureEntry, float pRange)
{
    std::unordered_set<Creature*> result;
    result.clear();

    std::list<Creature*> searchedList;
    CellPair pair(MaNGOS::ComputeCellPair(pSearcher->GetPositionX(), pSearcher->GetPositionY()));
    Cell cell(pair);
    cell.SetNoCreate();

    AllCreaturesOfEntryInRange_Nier check(pSearcher, pCreatureEntry, pRange);
    MaNGOS::CreatureListSearcher<AllCreaturesOfEntryInRange_Nier> searcher(searchedList, check);
    TypeContainerVisitor<MaNGOS::CreatureListSearcher<AllCreaturesOfEntryInRange_Nier>, GridTypeMapContainer> visitor(searcher);

    cell.Visit(pair, visitor, *(pSearcher->GetMap()), *pSearcher, pRange);

    for (std::list<Creature*>::iterator searchedIT = searchedList.begin(); searchedIT != searchedList.end(); searchedIT++)
    {
        result.insert(*searchedIT);
    }

    return result;
}
