#include "NierManager.h"
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

#include "Group.h"
#include "SpellAuras.h"
#include "AccountMgr.h"
#include "Chat.h"

NierManager::NierManager()
{
    allianceRaces.clear();
    hordeRaces.clear();
    nameIndex = 0;
    nierMap.clear();
    nierNameMap.clear();
    characterTalentTabNameMap.clear();
    timeValue = 0;
}

void NierManager::InitializeManager()
{
    if (sNierConfig.Enable == 0)
    {
        return;
    }

    sLog.Out(LogType::LOG_BASIC, LogLevel::LOG_LVL_BASIC, "Initialize nier");

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

void NierManager::Update(uint32 pDiff)
{
    if (sNierConfig.Enable == 0)
    {
        return;
    }
    timeValue += pDiff;
    for (std::unordered_map<uint32, Nier_Base*>::iterator reIT = nierMap.begin(); reIT != nierMap.end(); reIT++)
    {
        if (reIT->second)
        {
            reIT->second->Update(timeValue);
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
                ObjectGuid playerGuid = ObjectGuid(HighGuid::HIGHGUID_PLAYER, reIT->second->character_id);
                if (Player* eachPlayer = ObjectAccessor::FindPlayer(playerGuid))
                {
                    sLog.Out(LogType::LOG_BASIC, LogLevel::LOG_LVL_BASIC, "Logout nier : %s", eachPlayer->GetName());
                    eachPlayer->GetSession()->LogoutPlayer(true);
                }
            }
            else
            {
                reIT->second->accountState = NierAccountState::NierAccountState_DoLogout;
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
    std::unique_ptr<QueryResult> nierAccountQR = LoginDatabase.Query(accountQuerySQL);
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

bool NierManager::CreateNier(uint32 pMasterCharacterId, uint32 pClass, uint32 pRace)
{
    ObjectGuid masterGuid = ObjectGuid(HighGuid::HIGHGUID_PLAYER, pMasterCharacterId);
    if (Player* master = ObjectAccessor::FindPlayer(masterGuid))
    {
        if (master->IsInWorld())
        {
            if (master->GetLevel() >= 10)
            {
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
                std::ostringstream sqlStream;
                sqlStream << "INSERT INTO nier (nier_id, master_character_id, account_name, account_id, character_id, target_level, target_race, target_class, target_specialty) VALUES (" << maxId << ", " << pMasterCharacterId << ", '" << checkAccountName << "', 0, 0, 0, " << targetRace << ", " << pClass << ", " << 1 << ")";
                std::string sql = sqlStream.str();
                CharacterDatabase.DirectExecute(sql.c_str());

                std::ostringstream replyStream;
                replyStream << "nier " << checkAccountName << " - " << targetRace << " - " << pClass << " created";
                sWorld.SendServerMessage(ServerMessageType::SERVER_MSG_CUSTOM, replyStream.str().c_str());
            }
        }
    }
    return true;
}

bool NierManager::LoginNiers(uint32 pMasterCharacterId)
{
    std::ostringstream queryStream;
    queryStream << "SELECT nier_id, master_character_id, account_name, account_id, character_id, target_level, target_race, target_class, target_specialty FROM nier where master_character_id = " << pMasterCharacterId;
    std::unique_ptr<QueryResult> nierQR = CharacterDatabase.Query(queryStream.str());
    if (nierQR)
    {
        do
        {
            Field* fields = nierQR->Fetch();
            uint32 nier_id = fields[0].GetUInt32();
            uint32 master_character_id = fields[1].GetUInt32();
            std::string account_name = fields[2].GetString();
            uint32 account_id = fields[3].GetUInt32();
            uint32 character_id = fields[4].GetUInt32();
            uint32 target_level = fields[5].GetUInt32();
            uint32 target_race = fields[6].GetUInt32();
            uint32 target_class = fields[7].GetUInt32();
            uint32 target_specialty = fields[8].GetUInt32();
            Nier_Base* nb = nullptr;
            if (nierMap.find(nier_id) != nierMap.end())
            {
                nb = nierMap[nier_id];
            }
            else
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
                    nb = new Nier_Base();
                    break;
                }
                }
                nb->nier_id = nier_id;
                nb->master_character_id = master_character_id;
                nb->account_name = account_name;
                nb->account_id = nier_id;
                nb->character_id = 0;
                nb->target_level = 0;
                nb->target_race = target_race;
                nb->target_class = target_class;
                nb->target_specialty = 1;
                nb->accountState = NierAccountState::NierAccountState_OffLine;
                nierMap[nier_id] = nb;
            }
            if (nb)
            {
                if (nb->accountState == NierAccountState::NierAccountState_OffLine)
                {
                    nb->accountState = NierAccountState::NierAccountState_Enter;
                    nb->checkDelay = urand(1 * IN_MILLISECONDS, 5 * IN_MILLISECONDS);
                }
                std::ostringstream replyStream;
                replyStream << "nier " << nier_id << " - " << account_name << " to login";
                sWorld.SendServerMessage(ServerMessageType::SERVER_MSG_CUSTOM, replyStream.str().c_str());
            }
            else
            {
                std::ostringstream replyStream;
                replyStream << "nier " << nier_id << " - " << account_name << " has wrong data";
                sWorld.SendServerMessage(ServerMessageType::SERVER_MSG_CUSTOM, replyStream.str().c_str());
            }
        } while (nierQR->NextRow());
    }

    return true;
}

Nier_Base* NierManager::GetNier(uint32 pNierId)
{
    if (pNierId > 0)
    {
        if (nierMap.find(pNierId) == nierMap.end())
        {
            nierMap[pNierId] = new Nier_Base();
            nierMap[pNierId]->nier_id = pNierId;
        }

        return nierMap[pNierId];
    }

    return nullptr;
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

void NierManager::HandleChatCommand(Player* pCommander, std::string pCommand, Player* pTarget)
{
    if (!pCommander)
    {
        return;
    }
    if (pCommander->nier)
    {
        return;
    }
    Player* chatTarget = pTarget;
    if (!chatTarget)
    {
        chatTarget = pCommander;
    }

    std::ostringstream replyStream;
    std::vector<std::string> commandVector = SplitString(pCommand, " ", true);
    std::string commandName = commandVector.at(0);
    if (commandName == "role")
    {
        if (commandVector.size() > 1)
        {
            std::string newRole = commandVector.at(1);
            if (newRole == "tank")
            {
                chatTarget->nierGroupRole = NierGroupRole::NierGroupRole_Tank;
            }
            else if (newRole == "healer")
            {
                chatTarget->nierGroupRole = NierGroupRole::NierGroupRole_Healer;
            }
            else if (newRole == "dps")
            {
                chatTarget->nierGroupRole = NierGroupRole::NierGroupRole_DPS;
            }
        }
        if (chatTarget->nierGroupRole == NierGroupRole::NierGroupRole_Tank)
        {
            replyStream << "Role is tank";
        }
        else if (chatTarget->nierGroupRole == NierGroupRole::NierGroupRole_Healer)
        {
            replyStream << "Role is healer";
        }
        else if (chatTarget->nierGroupRole == NierGroupRole::NierGroupRole_DPS)
        {
            replyStream << "Role is dps";
        }
    }
    else if (commandName == "join")
    {
        if (commandVector.size() > 1)
        {
            std::string joinName = commandVector.at(1);
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
    else if (commandName == "nier")
    {
        if (commandVector.size() > 1)
        {
            std::string nierAction = commandVector.at(1);
            if (nierAction == "login")
            {
                uint32 playerLevel = pCommander->GetLevel();
                if (playerLevel < 10)
                {
                    replyStream << "You level is too low";
                }
                else
                {
                    LoginNiers(pCommander->GetGUIDLow());
                }
            }
            if (nierAction == "logout")
            {
                LogoutNiers();
            }
            else if (nierAction == "create")
            {
                uint32 playerLevel = pCommander->GetLevel();
                if (playerLevel < 10)
                {
                    replyStream << "You level is too low";
                }
                else
                {
                    if (commandVector.size() > 2)
                    {
                        uint32 targetClass = atoi(commandVector.at(2).c_str());
                        CreateNier(pCommander->GetGUIDLow(), targetClass, Races::RACE_HUMAN);
                    }
                    else
                    {
                        std::unordered_set<uint32> nierClassSet;
                        nierClassSet.insert(Classes::CLASS_DRUID);
                        //nierClassSet.insert(Classes::CLASS_WARRIOR);
                        nierClassSet.insert(Classes::CLASS_MAGE);
                        nierClassSet.insert(Classes::CLASS_ROGUE);
                        nierClassSet.insert(Classes::CLASS_PRIEST);
                        nierClassSet.insert(Classes::CLASS_WARLOCK);
                        nierClassSet.insert(Classes::CLASS_HUNTER);

                        for (std::unordered_set<uint32>::iterator classIT = nierClassSet.begin(); classIT != nierClassSet.end(); classIT++)
                        {
                            CreateNier(pCommander->GetGUIDLow(), *classIT, Races::RACE_HUMAN);
                        }
                    }
                }
            }
        }
    }
    else if (commandName == "who")
    {

    }
    else if (commandName == "emote")
    {
        std::string emoteContents = commandVector.at(1);
        int emoteNumber = atoi(emoteContents.c_str());
        chatTarget->HandleEmoteCommand(emoteNumber);
    }
    else if (commandName == "equip")
    {
        if (chatTarget->nier)
        {
            if (chatTarget->IsInWorld())
            {
                if (chatTarget->IsAlive())
                {
                    if (!chatTarget->IsInCombat())
                    {
                        if (commandVector.size() > 1)
                        {
                            std::string reset = commandVector.at(1);
                            if (reset == "reset")
                            {
                                chatTarget->nier->RemoveEquipments();
                            }
                        }
                        for (uint32 equipSlot = EquipmentSlots::EQUIPMENT_SLOT_HEAD; equipSlot < EquipmentSlots::EQUIPMENT_SLOT_TABARD; equipSlot++)
                        {
                            chatTarget->nier->EquipRandomItem(equipSlot);
                        }
                    }
                    else
                    {
                        replyStream << "in combat";
                    }
                }
                else
                {
                    replyStream << "dead";
                }
            }
            else
            {
                replyStream << "not in world";
            }
        }
    }
    else if (commandName == "assemble")
    {
        if (chatTarget->nier)
        {
            if (chatTarget->IsInWorld())
            {
                chatTarget->nier->actionState = NierActionState::NierActionState_Assemble;
                chatTarget->nier->actionTimeLimit = urand(10000, 20000);
                chatTarget->nier->actionTargetUnit = pCommander;
                int assembleSeconds = chatTarget->nier->actionTimeLimit / 1000;
                replyStream << "assemble in " << assembleSeconds << " seconds";
            }
            else
            {
                replyStream << "not in world";
            }
        }
    }
    else if (commandName == "formation")
    {
        if (chatTarget->nier)
        {
            if (chatTarget->IsInWorld())
            {
                if (chatTarget->IsAlive())
                {
                    if (commandVector.size() > 1)
                    {
                        std::string formation = commandVector.at(1);
                        if (formation == "point")
                        {
                            chatTarget->nier->actionState = NierActionState::NierActionState_Formation;
                            chatTarget->nier->actionTimeLimit = 5000;
                            chatTarget->nier->actionTargetUnit = pCommander;
                            chatTarget->nier->actionTargetPos = pCommander->GetPosition();
                        }
                        replyStream << "formation";
                    }
                }
                else
                {
                    replyStream << "dead";
                }
            }
            else
            {
                replyStream << "not in world";
            }
        }
    }
    else if (commandName == "leader")
    {
        chatTarget = pCommander;
        if (Group* targetGroup = pCommander->GetGroup())
        {
            if (targetGroup->GetLeaderGuid() != pCommander->GetObjectGuid())
            {
                targetGroup->ChangeLeader(pCommander->GetObjectGuid());
                replyStream << "You are the leader";
            }
        }
        else
        {
            replyStream << "You are not in a group";
        }
    }
    else if (commandName == "engage")
    {
        if (chatTarget->nier)
        {
            if (chatTarget->IsInWorld())
            {
                if (chatTarget->nier->actionState == NierActionState::NierActionState_Freeze)
                {
                    chatTarget->nier->ClearAction();
                }
                if (chatTarget->IsAlive())
                {
                    if (Unit* target = pCommander->GetSelectedUnit())
                    {
                        switch (chatTarget->nierGroupRole)
                        {
                        case NierGroupRole::NierGroupRole_Tank:
                        {
                            if (chatTarget->nier->Tank(target))
                            {
                                chatTarget->nier->actionState = NierActionState::NierActionState_Tank;
                                chatTarget->nier->actionTargetUnit = target;
                                chatTarget->nier->actionDuration = 0;
                                chatTarget->nier->actionTargetPos = target->GetPosition();
                                chatTarget->nier->actionTimeLimit = 5000;
                            }
                            break;
                        }
                        case NierGroupRole::NierGroupRole_Healer:
                        {
                            break;
                        }
                        case NierGroupRole::NierGroupRole_DPS:
                        {
                            if (chatTarget->nier->Attack(target))
                            {
                                chatTarget->nier->actionState = NierActionState::NierActionState_Attack;
                                chatTarget->nier->actionTargetUnit = target;
                                chatTarget->nier->actionDuration = 0;
                                chatTarget->nier->actionTargetPos = target->GetPosition();
                                chatTarget->nier->actionTimeLimit = 5000;
                            }
                            break;
                        }
                        }
                    }
                }
                else
                {
                    replyStream << "dead";
                }
            }
            else
            {
                replyStream << "not in world";
            }
        }
    }
    else if (commandName == "dps")
    {
        if (chatTarget->nier)
        {
            if (chatTarget->IsInWorld())
            {
                if (chatTarget->nier->actionState == NierActionState::NierActionState_Freeze)
                {
                    chatTarget->nier->ClearAction();
                }
                if (chatTarget->IsAlive())
                {
                    if (Unit* target = pCommander->GetSelectedUnit())
                    {
                        switch (chatTarget->nierGroupRole)
                        {
                        case NierGroupRole::NierGroupRole_Tank:
                        {
                            break;
                        }
                        case NierGroupRole::NierGroupRole_Healer:
                        {
                            break;
                        }
                        case NierGroupRole::NierGroupRole_DPS:
                        {
                            if (chatTarget->nier->Attack(target))
                            {
                                chatTarget->nier->actionState = NierActionState::NierActionState_Attack;
                                chatTarget->nier->actionTargetUnit = target;
                                chatTarget->nier->actionDuration = 0;
                                chatTarget->nier->actionTargetPos = target->GetPosition();
                                chatTarget->nier->actionTimeLimit = 5000;
                            }
                            break;
                        }
                        }
                    }
                }
                else
                {
                    replyStream << "dead";
                }
            }
            else
            {
                replyStream << "not in world";
            }
        }
    }
    else if (commandName == "tank")
    {
        if (chatTarget->nier)
        {
            if (chatTarget->IsInWorld())
            {
                if (chatTarget->nier->actionState == NierActionState::NierActionState_Freeze)
                {
                    chatTarget->nier->ClearAction();
                }
                if (chatTarget->IsAlive())
                {
                    if (Unit* target = pCommander->GetSelectedUnit())
                    {
                        switch (chatTarget->nierGroupRole)
                        {
                        case NierGroupRole::NierGroupRole_Tank:
                        {
                            if (chatTarget->nier->Tank(target))
                            {
                                chatTarget->nier->actionState = NierActionState::NierActionState_Tank;
                                chatTarget->nier->actionTargetUnit = target;
                                chatTarget->nier->actionDuration = 0;
                                chatTarget->nier->actionTargetPos = target->GetPosition();
                                chatTarget->nier->actionTimeLimit = 5000;
                            }
                            break;
                        }
                        case NierGroupRole::NierGroupRole_Healer:
                        {
                            break;
                        }
                        case NierGroupRole::NierGroupRole_DPS:
                        {
                            break;
                        }
                        }
                    }
                }
                else
                {
                    replyStream << "dead";
                }
            }
            else
            {
                replyStream << "not in world";
            }
        }
    }
    else if (commandName == "freeze")
    {
        if (chatTarget->nier)
        {
            if (chatTarget->IsInWorld())
            {
                if (chatTarget->IsAlive())
                {
                    chatTarget->StopMoving();
                    chatTarget->GetMotionMaster()->Clear();
                    chatTarget->CombatStop(true);
                }
                chatTarget->nier->ClearAction();
                chatTarget->nier->actionState = NierActionState::NierActionState_Freeze;
                chatTarget->nier->actionTimeLimit = 3600000;
                replyStream << "freezing";
            }
            else
            {
                replyStream << "not in world";
            }
        }
    }
    else if (commandName == "follow")
    {
        if (chatTarget->nier)
        {
            if (chatTarget->IsInWorld())
            {
                if (chatTarget->IsAlive())
                {
                    chatTarget->nier->ClearAction();
                    chatTarget->nier->actionState = NierActionState::NierActionState_Follow;
                    chatTarget->nier->actionTimeLimit = 2000;
                    replyStream << "following";
                }
                else
                {
                    replyStream << "dead";
                }
            }
            else
            {
                replyStream << "not in world";
            }
        }
    }
    else if (commandName == "rest")
    {
        if (chatTarget->nier)
        {
            if (chatTarget->IsInWorld())
            {
                if (chatTarget->IsAlive())
                {
                    if (chatTarget->nier->Rest(true))
                    {
                        chatTarget->nier->actionState = NierActionState::NierActionState_Rest;
                        chatTarget->nier->actionTimeLimit = 15000;
                    }
                }
                else
                {
                    replyStream << "dead";
                }
            }
            else
            {
                replyStream << "not in world";
            }
        }
    }
    else if (commandName == "revive")
    {
        if (chatTarget->nier)
        {
            if (chatTarget->IsInWorld())
            {
                if (chatTarget->IsAlive())
                {
                    if (Unit* target = pCommander->GetSelectedUnit())
                    {
                        if (chatTarget->nier->Revive(target))
                        {
                            chatTarget->nier->actionState = NierActionState::NierActionState_Cast;
                            chatTarget->nier->actionTargetUnit = target;
                            chatTarget->nier->actionDuration = 0;
                            chatTarget->nier->actionTargetPos = target->GetPosition();
                            chatTarget->nier->actionTimeLimit = 5000;
                        }
                    }
                }
                else
                {
                    replyStream << "dead";
                }
            }
            else
            {
                replyStream << "not in world";
            }
        }
    }
    else if (commandName == "prepare")
    {
        if (chatTarget->nier)
        {
            if (chatTarget->IsInWorld())
            {
                if (chatTarget->IsAlive())
                {
                    chatTarget->nier->Prepare();
                }
                else
                {
                    replyStream << "dead";
                }
            }
            else
            {
                replyStream << "not in world";
            }
        }
    }

    std::string replayStr = replyStream.str();
    if (!replayStr.empty())
    {
        if (pCommander->GetObjectGuid() == chatTarget->GetObjectGuid())
        {
            sWorld.SendServerMessage(ServerMessageType::SERVER_MSG_CUSTOM, replayStr.c_str(), pCommander);
        }
        else
        {
            WhisperTo(pCommander, replayStr, pTarget);
        }
    }
}

void NierManager::HandlePacket(const WorldSession* pSession, WorldPacket pPacket)
{
    if (Nier_Base* nb = GetNier(pSession->nier_id))
    {
        switch (pPacket.GetOpcode())
        {
        case SMSG_CHAR_ENUM:
        {
            if (nb->accountState == NierAccountState::NierAccountState_CheckEnum)
            {
                nb->accountState = NierAccountState::NierAccountState_DoLogin;
                nb->checkDelay = urand(2 * IN_MILLISECONDS, 5 * IN_MILLISECONDS);
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
            if (Player* receiver = nb->me)
            {
                if (!receiver->IsInWorld())
                {
                    break;
                }
                if (Group* myGroup = receiver->GetGroup())
                {
                    receiver->RemoveFromGroup();
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
                    if (Player* inviter = ObjectAccessor::FindPlayer(grp->GetLeaderGuid()))
                    {
                        nb->Prepare();
                        WhisperTo(inviter, "Greetings! Master", receiver);
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
            if (Player* receiver = nb->me)
            {
                if (!receiver->IsInWorld())
                {
                    break;
                }
                if (receiver->IsRessurectRequested())
                {
                    receiver->ResurectUsingRequestData();
                    receiver->ClearInCombat();
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
            if (Player* receiver = nb->me)
            {
                receiver->DuelComplete(DuelCompleteType::DUEL_INTERRUPTED);
                WhisperTo(receiver->m_duel->opponent, "Not interested", receiver);
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

void NierManager::WhisperTo(Player* pTarget, std::string pContent, Player* pSender)
{
    if (pSender && pTarget)
    {
        WorldPacket data;
        ChatHandler::BuildChatPacket(data, CHAT_MSG_WHISPER, pContent.c_str(), Language::LANG_UNIVERSAL, 0, pSender->GetObjectGuid(), pSender->GetName(), pTarget->GetObjectGuid(), pTarget->GetName());
        pTarget->GetSession()->SendPacket(&data);
    }
}

bool NierManager::HasAura(Unit* pTarget, uint32 pSpellId, Unit* pCaster)
{
    if (!pTarget)
    {
        return false;
    }
    if (pCaster)
    {
        std::multimap< uint32, SpellAuraHolder*> sahMap = pTarget->GetSpellAuraHolderMap();
        for (std::multimap< uint32, SpellAuraHolder*>::iterator sahIT = sahMap.begin(); sahIT != sahMap.end(); sahIT++)
        {
            if (pSpellId == sahIT->first)
            {
                if (SpellAuraHolder* eachSAH = sahIT->second)
                {
                    if (eachSAH->GetCasterGuid() == pCaster->GetObjectGuid())
                    {
                        return true;
                    }
                }
            }
        }
    }
    else
    {
        if (pTarget->HasAura(pSpellId))
        {
            return true;
        }
    }

    return false;
}

uint32 NierManager::GetAuraDuration(Unit* pTarget, uint32 pSpellId, Unit* pCaster)
{
    if (pSpellId == 0)
    {
        return 0;
    }
    if (!pTarget)
    {
        return 0;
    }

    uint32 duration = 0;
    if (pCaster)
    {
        std::multimap< uint32, SpellAuraHolder*> sahMap = pTarget->GetSpellAuraHolderMap();
        for (std::multimap< uint32, SpellAuraHolder*>::iterator sahIT = sahMap.begin(); sahIT != sahMap.end(); sahIT++)
        {
            if (pSpellId == sahIT->first)
            {
                if (SpellAuraHolder* eachSAH = sahIT->second)
                {
                    if (eachSAH->GetCasterGuid() == pCaster->GetObjectGuid())
                    {
                        duration = eachSAH->GetAuraDuration();
                    }
                }
            }
        }
    }
    else
    {
        if (Aura* destAura = pTarget->GetAura(pSpellId, SpellEffectIndex::EFFECT_INDEX_0))
        {
            duration = destAura->GetAuraDuration();
        }
    }

    return duration;
}

uint32 NierManager::GetAuraStack(Unit* pTarget, uint32 pSpellId, Unit* pCaster)
{
    if (pSpellId == 0)
    {
        return 0;
    }
    if (!pTarget)
    {
        return 0;
    }
    uint32 auraStack = 0;
    if (pCaster)
    {
        std::multimap< uint32, SpellAuraHolder*> sahMap = pTarget->GetSpellAuraHolderMap();
        for (std::multimap< uint32, SpellAuraHolder*>::iterator sahIT = sahMap.begin(); sahIT != sahMap.end(); sahIT++)
        {
            if (pSpellId == sahIT->first)
            {
                if (SpellAuraHolder* eachSAH = sahIT->second)
                {
                    if (eachSAH->GetCasterGuid() == pCaster->GetObjectGuid())
                    {
                        auraStack = eachSAH->GetStackAmount();
                    }
                }
            }
        }
    }
    else
    {
        if (Aura* destAura = pTarget->GetAura(pSpellId, SpellEffectIndex::EFFECT_INDEX_0))
        {
            auraStack = destAura->GetStackAmount();
        }
    }
    return 0;
}

std::vector<std::string> NierManager::SplitString(std::string srcStr, std::string delimStr, bool repeatedCharIgnored)
{
    std::vector<std::string> resultStringVector;
    std::replace_if(srcStr.begin(), srcStr.end(), [&](const char& c) {if (delimStr.find(c) != std::string::npos) { return true; } else { return false; }}, delimStr.at(0));
    size_t pos = srcStr.find(delimStr.at(0));
    std::string addedString = "";
    while (pos != std::string::npos) {
        addedString = srcStr.substr(0, pos);
        if (!addedString.empty() || !repeatedCharIgnored) {
            resultStringVector.push_back(addedString);
        }
        srcStr.erase(srcStr.begin(), srcStr.begin() + pos + 1);
        pos = srcStr.find(delimStr.at(0));
    }
    addedString = srcStr;
    if (!addedString.empty() || !repeatedCharIgnored) {
        resultStringVector.push_back(addedString);
    }
    return resultStringVector;
}

std::string NierManager::TrimString(std::string srcStr)
{
    std::string result = srcStr;
    if (!result.empty())
    {
        result.erase(0, result.find_first_not_of(" "));
        result.erase(result.find_last_not_of(" ") + 1);
    }

    return result;
}
