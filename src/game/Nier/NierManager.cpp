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

    QueryResult* nierQR = CharacterDatabase.Query("SELECT nier_id, account_name, character_id, target_level, target_race, target_class, target_specialty FROM nier");
    if (nierQR)
    {
        do
        {
            Field* fields = nierQR->Fetch();
            NierEntity* re = new NierEntity();
            re->nier_id = fields[0].GetUInt32();
            re->account_name = fields[1].GetString();
            re->character_id = fields[2].GetUInt32();
            re->target_level = fields[3].GetUInt32();
            re->target_race = fields[4].GetUInt32();
            re->target_class = fields[5].GetUInt32();
            re->target_specialty = fields[6].GetUInt32();
            nierEntitySet.insert(re);
        } while (nierQR->NextRow());
    }
    delete nierQR;

    nameIndex = 0;
    QueryResult* nierNameQR = WorldDatabase.Query("SELECT name FROM nier_names order by rand()");
    if (nierNameQR)
    {
        do
        {
            Field* fields = nierNameQR->Fetch();
            std::string eachName = fields[0].GetString();
            nierNameMap[nierNameMap.size()] = eachName;
        } while (nierNameQR->NextRow());
    }
    delete nierNameQR;

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
        checkDelay = sNierConfig.ManagerCheckDelay;
        std::unordered_set<uint32> onlinePlayerLevelSet;
        onlinePlayerLevelSet.clear();
        std::unordered_map<uint32, WorldSession*> allSessions = sWorld.GetAllSessions();
        for (std::unordered_map<uint32, WorldSession*>::iterator wsIT = allSessions.begin(); wsIT != allSessions.end(); wsIT++)
        {
            if (WorldSession* eachWS = wsIT->second)
            {
                if (!eachWS->isNier)
                {
                    if (Player* eachPlayer = eachWS->GetPlayer())
                    {
                        //NierCheck(eachPlayer);
                        uint32 eachLevel = eachPlayer->GetLevel();
                        if (onlinePlayerLevelSet.find(eachLevel) == onlinePlayerLevelSet.end())
                        {
                            onlinePlayerLevelSet.insert(eachLevel);
                        }
                    }
                }
            }
        }
        for (std::unordered_set<uint32>::iterator levelIT = onlinePlayerLevelSet.begin(); levelIT != onlinePlayerLevelSet.end(); levelIT++)
        {
            uint32 eachLevel = *levelIT;
            LoginNier(eachLevel, sNierConfig.NierCountEachLevel);
        }
    }
}

bool NierManager::NierCheck(Player* master)
{
    return true;
}

void NierManager::UpdateNierEntities(uint32 pmDiff)
{
    for (std::unordered_set<NierEntity*>::iterator reIT = nierEntitySet.begin(); reIT != nierEntitySet.end(); reIT++)
    {
        (*reIT)->Update(pmDiff);
    }
}

void NierManager::LogoutNiers(bool pmInstant)
{
    for (std::unordered_set<NierEntity*>::iterator reIT = nierEntitySet.begin(); reIT != nierEntitySet.end(); reIT++)
    {
        if (NierEntity* eachNier = *reIT)
        {
            if (pmInstant)
            {
                ObjectGuid playerGuid = ObjectGuid(HIGHGUID_PLAYER, eachNier->character_id);
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
                eachNier->entityState = NierEntityState::NierEntityState_DoLogoff;
                eachNier->checkDelay = 10;
            }
        }
    }
}

void NierManager::DeleteNiers()
{
    QueryResult* nierQR = CharacterDatabase.Query("SELECT account_id FROM nier");
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
    delete nierQR;

    CharacterDatabase.DirectExecute("delete from nier");

    std::ostringstream accountQueryStream;
    accountQueryStream << "SELECT id FROM account where username like '" << NIER_MARK << "%'";
    std::string accountQuerySQL = accountQueryStream.str();
    QueryResult* nierAccountQR = LoginDatabase.Query(accountQuerySQL.c_str());
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
    delete nierAccountQR;
}

bool NierManager::LoginNier(uint32 pmLevel, uint32 pmCount)
{
    if (pmLevel >= 20)
    {
        uint32 currentCount = 0;
        QueryResult* levelNierQR = CharacterDatabase.PQuery("SELECT count(*) FROM nier where target_level = %d", pmLevel);
        if (levelNierQR)
        {
            Field* fields = levelNierQR->Fetch();
            currentCount = fields[0].GetUInt32();
        }
        delete levelNierQR;
        if (currentCount < pmCount)
        {
            uint32 addCount = pmCount - currentCount;
            uint32 allianceCount = addCount / 2;
            uint32 hordeCount = addCount - allianceCount;
            int checkCount = allianceCount;
            int tankA = 0;
            int tankH = 0;

            int healerA = 2;
            int healerH = 0;
            while (checkCount > 0)
            {
                uint32 groupRole = GroupRole::GroupRole_DPS;
                if (tankA > 0)
                {
                    groupRole = GroupRole::GroupRole_Tank;
                    tankA--;
                }
                else if (healerA > 0)
                {
                    groupRole = GroupRole::GroupRole_Healer;
                    healerA--;
                }
                CreateNier(pmLevel, true, groupRole);
                checkCount--;
            }
            checkCount = hordeCount;
            while (checkCount > 0)
            {
                uint32 groupRole = GroupRole::GroupRole_DPS;
                if (tankH > 0)
                {
                    groupRole = GroupRole::GroupRole_Tank;
                    tankH--;
                }
                else if (healerH > 0)
                {
                    groupRole = GroupRole::GroupRole_Healer;
                    healerH--;
                }
                CreateNier(pmLevel, false, groupRole);
                checkCount--;
            }
        }
        uint32 onlineCount = 0;
        for (std::unordered_set<NierEntity*>::iterator reIT = nierEntitySet.begin(); reIT != nierEntitySet.end(); reIT++)
        {
            if (NierEntity* eachRE = *reIT)
            {
                if (eachRE->target_level == pmLevel)
                {
                    if (eachRE->entityState != NierEntityState::NierEntityState_OffLine && eachRE->entityState != NierEntityState::NierEntityState_None)
                    {
                        onlineCount++;
                    }
                }
            }
        }
        int toOnline = 0;
        if (pmCount > onlineCount)
        {
            toOnline = pmCount - onlineCount;
        }
        if (toOnline > 0)
        {
            for (std::unordered_set<NierEntity*>::iterator reIT = nierEntitySet.begin(); reIT != nierEntitySet.end(); reIT++)
            {
                if (NierEntity* eachRE = *reIT)
                {
                    if (eachRE->target_level == pmLevel)
                    {
                        if (eachRE->entityState == NierEntityState::NierEntityState_OffLine)
                        {
                            eachRE->checkDelay = urand(5 * IN_MILLISECONDS, 5 * MINUTE * IN_MILLISECONDS);
                            eachRE->entityState = NierEntityState::NierEntityState_Enter;
                            toOnline--;
                            if (toOnline <= 0)
                            {
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
    return true;
}

void NierManager::CreateNier(uint32 pmLevel, bool pmAlliance, uint32 pmGroupRole)
{
    uint32 currentNierCount = 0;
    QueryResult* nierQR = CharacterDatabase.Query("SELECT count(*) FROM nier");
    if (nierQR)
    {
        Field* fields = nierQR->Fetch();
        currentNierCount = fields[0].GetUInt32();
    }
    delete nierQR;
    std::ostringstream accountNameStream;
    accountNameStream << NIER_MARK << currentNierCount;
    std::string checkAccountName = accountNameStream.str();
    std::ostringstream querySQLStream;
    querySQLStream << "SELECT * FROM account where username ='" << checkAccountName << "'";
    std::string querySQL = querySQLStream.str();
    QueryResult* accountNameQR = LoginDatabase.Query(querySQL.c_str());
    if (accountNameQR)
    {
        sLog.Out(LogType::LOG_BASIC, LogLevel::LOG_LVL_BASIC, "Account already %s exists.", checkAccountName);
    }
    else
    {
        uint32 target_class = Classes::CLASS_HUNTER;
        uint32 target_specialty = 1;
        uint32 classRand = urand(1, 100);
        if (pmGroupRole == GroupRole::GroupRole_Tank)
        {
            //target_class = Classes::CLASS_WARRIOR;
            //target_specialty = 2;
            // 
            // rogue only 
            target_class = Classes::CLASS_ROGUE;
            target_specialty = 1;
            if (pmAlliance)
            {
                target_class = Classes::CLASS_PALADIN;
                target_specialty = 1;
                // lfm debug priest only 
                target_class = Classes::CLASS_PRIEST;
                target_specialty = 1;
            }
        }
        else if (pmGroupRole == GroupRole::GroupRole_Healer)
        {
            target_class = Classes::CLASS_PRIEST;
            target_specialty = 1;
        }
        else
        {
            if (classRand < 60)
            {
                target_class = Classes::CLASS_ROGUE;
                target_specialty = 1;
            }
            else if (classRand < 80)
            {
                target_class = Classes::CLASS_DRUID;
                target_specialty = 0;
            }
            //else if (classRand < 60)
            //{
            //	target_class = Classes::CLASS_HUNTER;
            //	target_specialty = 1;
            //}
            else if (classRand < 200)
            {
                target_class = Classes::CLASS_MAGE;
                target_specialty = 2;
            }

            // rogue only 
            target_class = Classes::CLASS_ROGUE;
            target_specialty = 1;

            //if (pmAlliance)
            //{
            //	if (urand(0, 100) > 50)
            //	{
            //		target_class = Classes::CLASS_PALADIN;
            //		target_specialty = 2;
            //	}
            //}
        }

        uint32 target_race = 0;
        if (pmAlliance)
        {
            uint32 raceIndex = urand(0, allianceRaces[target_class].size() - 1);
            target_race = allianceRaces[target_class][raceIndex];
        }
        else
        {
            uint32 raceIndex = urand(0, hordeRaces[target_class].size() - 1);
            target_race = hordeRaces[target_class][raceIndex];
        }
        if (target_race == 0)
        {
            bool breakPoint = true;
        }
        std::ostringstream sqlStream;
        sqlStream << "INSERT INTO nier (nier_id, account_id, account_name, character_id, target_level, target_race, target_class, target_specialty) VALUES (" << currentNierCount << ", 0, '" << checkAccountName << "', 0, " << pmLevel << ", " << target_race << ", " << target_class << ", " << target_specialty << ")";
        std::string sql = sqlStream.str();
        CharacterDatabase.DirectExecute(sql.c_str());
        NierEntity* re = new NierEntity();
        re->nier_id = currentNierCount;
        re->account_id = 0;
        re->account_name = checkAccountName;
        re->character_id = 0;
        re->target_level = pmLevel;
        re->target_race = target_race;
        re->target_class = target_class;
        re->target_specialty = target_specialty;
        nierEntitySet.insert(re);
        std::ostringstream replyStream;
        replyStream << "nier " << checkAccountName << " created";
        sWorld.SendServerMessage(ServerMessageType::SERVER_MSG_CUSTOM, replyStream.str().c_str());
    }
    delete accountNameQR;
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

void NierManager::HandleChatCommand(Player* pmCommander, std::string pmContent, Player* pmTargetPlayer, Group* pmTargetGroup)
{
    if (!pmCommander)
    {
        return;
    }
    std::vector<std::string> commandVector = sMingManager->SplitString(pmContent, " ", true);
    std::string commandName = commandVector.at(0);
    if (commandName == "role")
    {
        if (pmTargetGroup)
        {
            for (GroupReference* groupRef = pmTargetGroup->GetFirstMember(); groupRef != nullptr; groupRef = groupRef->next())
            {
                Player* member = groupRef->getSource();
                if (member)
                {
                    if (member->GetObjectGuid() != pmCommander->GetObjectGuid())
                    {
                        HandleChatCommand(pmCommander, pmContent, member);
                    }
                }
            }
        }
        else
        {
            Player* targetPlayer = pmTargetPlayer;
            if (!targetPlayer)
            {
                targetPlayer = pmCommander;
            }
            std::ostringstream replyStream;
            if (commandVector.size() > 1)
            {
                std::string newRole = commandVector.at(1);
                if (newRole == "tank")
                {
                    targetPlayer->groupRole = GroupRole::GroupRole_Tank;
                }
                else if (newRole == "healer")
                {
                    targetPlayer->groupRole = GroupRole::GroupRole_Healer;
                }
                else if (newRole == "dps")
                {
                    targetPlayer->groupRole = GroupRole::GroupRole_DPS;
                }
            }
            if (targetPlayer->groupRole == GroupRole::GroupRole_Tank)
            {
                replyStream << "Role is tank";
            }
            else if (targetPlayer->groupRole == GroupRole::GroupRole_Healer)
            {
                replyStream << "Role is healer";
            }
            else if (targetPlayer->groupRole == GroupRole::GroupRole_DPS)
            {
                replyStream << "Role is dps";
            }
            if (pmTargetPlayer)
            {
                WhisperTo(pmCommander, replyStream.str(), Language::LANG_UNIVERSAL, pmTargetPlayer);
            }
            else
            {
                sWorld.SendServerMessage(ServerMessageType::SERVER_MSG_CUSTOM, replyStream.str().c_str(), pmCommander);
            }
        }
    }
    else if (commandName == "who")
    {
        if (pmTargetGroup)
        {
            for (GroupReference* groupRef = pmTargetGroup->GetFirstMember(); groupRef != nullptr; groupRef = groupRef->next())
            {
                Player* member = groupRef->getSource();
                if (member)
                {
                    if (member->GetObjectGuid() != pmCommander->GetObjectGuid())
                    {
                        HandleChatCommand(pmCommander, pmContent, member);
                    }
                }
            }
        }
        else if (pmTargetPlayer)
        {
            std::ostringstream replyStream;
            replyStream << characterTalentTabNameMap[pmTargetPlayer->GetClass()][pmTargetPlayer->nierAction->specialty];
            WhisperTo(pmCommander, replyStream.str(), Language::LANG_UNIVERSAL, pmTargetPlayer);
        }
    }
    else if (commandName == "emote")
    {
        if (pmTargetGroup)
        {
            for (GroupReference* groupRef = pmTargetGroup->GetFirstMember(); groupRef != nullptr; groupRef = groupRef->next())
            {
                Player* member = groupRef->getSource();
                if (member)
                {
                    if (member->GetObjectGuid() != pmCommander->GetObjectGuid())
                    {
                        HandleChatCommand(pmCommander, pmContent, member);
                    }
                }
            }
        }
        else if (pmTargetPlayer)
        {
            Player* targetPlayer = pmTargetPlayer;
            if (!targetPlayer)
            {
                targetPlayer = pmCommander;
            }
            if (commandVector.size() > 1)
            {
                std::string emoteContents = commandVector.at(1);
                int emoteNumber = atoi(emoteContents.c_str());
                targetPlayer->HandleEmoteCommand(emoteNumber);
            }
        }
        else
        {
            if (commandVector.size() > 1)
            {
                std::string emoteContents = commandVector.at(1);
                int emoteNumber = atoi(emoteContents.c_str());
                pmCommander->HandleEmoteCommand(emoteNumber);
            }
        }
    }
    else if (commandName == "arrangement")
    {
        std::ostringstream replyStream;
        if (pmTargetGroup)
        {
            if (pmTargetGroup->GetLeaderGuid() == pmCommander->GetObjectGuid())
            {
                pmTargetGroup->activeStrategyIndex = 0;
                pmTargetGroup->nierGroupStrategyMap.clear();
                pmTargetGroup->nierGroupStrategyMap[pmTargetGroup->activeStrategyIndex] = new GroupStrategy_Base();
                pmTargetGroup->nierGroupStrategyMap[pmTargetGroup->activeStrategyIndex]->me = pmTargetGroup;
                pmTargetGroup->nierGroupStrategyMap[pmTargetGroup->activeStrategyIndex]->Reset();

                ObjectGuid ogTank = ObjectGuid();
                ObjectGuid ogHealer = ObjectGuid();
                int rti = 0;
                for (GroupReference* groupRef = pmTargetGroup->GetFirstMember(); groupRef != nullptr; groupRef = groupRef->next())
                {
                    if (Player* member = groupRef->getSource())
                    {
                        uint32 mapId = member->GetMapId();
                        if (mapId == StrategyIndex::StrategyIndex_The_Underbog)
                        {
                            member->activeStrategyIndex = StrategyIndex::StrategyIndex_The_Underbog;
                        }
                        else if (mapId == 269)
                        {
                            member->activeStrategyIndex = StrategyIndex::StrategyIndex_The_Black_Morass;
                        }
                        else if (mapId == 585)
                        {
                            member->activeStrategyIndex = 585;
                        }
                        else if (mapId == 601)
                        {
                            member->activeStrategyIndex = 601;
                        }
                        member->groupRole = GroupRole::GroupRole_DPS;
                        switch (member->GetClass())
                        {
                        case Classes::CLASS_WARRIOR:
                        {
                            member->groupRole = GroupRole::GroupRole_Tank;
                            ogTank = member->GetObjectGuid();
                            replyStream << "og tank is : " << ogTank.GetCounter() << " " << member->GetName();
                            break;
                        }
                        case Classes::CLASS_PALADIN:
                        {
                            member->groupRole = GroupRole::GroupRole_Tank;
                            ogTank = member->GetObjectGuid();
                            replyStream << "og tank is : " << ogTank.GetCounter() << " " << member->GetName();
                            break;
                        }
                        case Classes::CLASS_HUNTER:
                        {
                            break;
                        }
                        case Classes::CLASS_MAGE:
                        {
                            break;
                        }
                        case Classes::CLASS_DRUID:
                        {
                            break;
                        }
                        case Classes::CLASS_ROGUE:
                        {
                            break;
                        }
                        case Classes::CLASS_PRIEST:
                        {
                            member->groupRole = GroupRole::GroupRole_Healer;
                            ogHealer = member->GetObjectGuid();
                            replyStream << "og healer is : " << ogHealer.GetCounter() << " " << member->GetName();
                            break;
                        }
                        default:
                        {
                            break;
                        }
                        }
                        if (NierStrategy_Base* ns = member->nierStrategyMap[member->activeStrategyIndex])
                        {
                            ns->Reset();
                            ns->rti = rti;
                            rti++;
                        }
                        if (member->nierAction)
                        {
                            member->nierAction->Prepare();
                        }
                    }
                }

                // roles and report 
                for (GroupReference* groupRef = pmTargetGroup->GetFirstMember(); groupRef != nullptr; groupRef = groupRef->next())
                {
                    if (Player* member = groupRef->getSource())
                    {
                        if (member->GetObjectGuid() == pmCommander->GetObjectGuid())
                        {
                            continue;
                        }
                        if (NierStrategy_Base* ns = member->nierStrategyMap[member->activeStrategyIndex])
                        {
                            ns->ogTank = ogTank;
                            replyStream << "og tank for member " << member->GetName() << " is : " << ns->ogTank.GetCounter();
                            ns->ogHealer = ogHealer;
                            replyStream << "og healer for member " << member->GetName() << " is : " << ns->ogHealer.GetCounter();
                            ns->Report();
                        }
                    }
                }
                replyStream << "Arranged";
            }
            else
            {
                replyStream << "You are not leader";
            }
        }
        else
        {
            replyStream << "Not in a group";
        }
        sWorld.SendServerMessage(ServerMessageType::SERVER_MSG_CUSTOM, replyStream.str().c_str(), pmCommander);
    }
    else if (commandName == "instance")
    {
        std::ostringstream replyStream;
        if (pmTargetPlayer)
        {
            if (pmTargetPlayer->GetSession()->isNier)
            {
                Player::BoundInstancesMap& binds = pmTargetPlayer->GetBoundInstances();
                for (Player::BoundInstancesMap::iterator itr = binds.begin(); itr != binds.end(); itr++)
                {
                    pmTargetPlayer->UnbindInstance(itr);
                }
                replyStream << "Instance unbond";
                WhisperTo(pmCommander, replyStream.str(), Language::LANG_UNIVERSAL, pmTargetPlayer);
            }
        }
        else if (pmTargetGroup)
        {
            for (GroupReference* groupRef = pmTargetGroup->GetFirstMember(); groupRef != nullptr; groupRef = groupRef->next())
            {
                Player* member = groupRef->getSource();
                if (member)
                {
                    if (member->GetObjectGuid() != pmCommander->GetObjectGuid())
                    {
                        HandleChatCommand(pmCommander, pmContent, member, pmTargetGroup);
                    }
                }
            }
        }
    }
    else if (commandName == "updateentry")
    {
        if (Unit* target = pmCommander->GetSelectedUnit())
        {
            if (Creature* targetC = (Creature*)target)
            {
                if (commandVector.size() > 1)
                {
                    std::string checkEntry = commandVector.at(1);
                    uint32 entry = atoi(checkEntry.c_str());
                    targetC->UpdateEntry(entry);
                }
            }
        }
    }
    else if (commandName == "vimgol")
    {
        if (pmTargetGroup)
        {
            std::list<Creature*> visualList;
            pmCommander->GetCreatureListWithEntryInGrid(visualList, 23040, VISIBILITY_DISTANCE_NORMAL);
            std::unordered_set<ObjectGuid> ogGoingSet;
            for (GroupReference* groupRef = pmTargetGroup->GetFirstMember(); groupRef != nullptr; groupRef = groupRef->next())
            {
                if (Player* member = groupRef->getSource())
                {
                    if (member->GetObjectGuid() != pmCommander->GetObjectGuid())
                    {
                        for (auto& eachVisual : visualList)
                        {
                            if (ogGoingSet.find(eachVisual->GetObjectGuid()) == ogGoingSet.end())
                            {
                                if (NierStrategy_Base* ns = member->nierStrategyMap[member->activeStrategyIndex])
                                {
                                    ns->basicStrategyType = BasicStrategyType::BasicStrategyType_Hold;
                                    ns->restLimit = 0;
                                    ns->actionType = ActionType::ActionType_Move;
                                    ns->actionLimit = 30000;
                                    member->nierAction->nm->Point(eachVisual->GetPosition(), ns->actionLimit);
                                    //std::ostringstream replyStream;
                                    //replyStream << "Goting to visual : " << eachVisual->GetObjectGuid().GetCounter();
                                    //member->Say(replyStream.str(), Language::LANG_UNIVERSAL);
                                    ogGoingSet.insert(eachVisual->GetObjectGuid());
                                }
                                break;
                            }
                        }
                    }
                }
            }
        }
        else
        {
            HandleChatCommand(pmCommander, pmContent, pmCommander, pmTargetGroup);
        }
    }
    else if (commandName == "distance")
    {
        if (pmTargetPlayer)
        {
            if (Unit* distanceTarget = pmCommander->GetSelectedUnit())
            {
                float distance = pmTargetPlayer->GetDistance(distanceTarget);
                std::ostringstream replyStream0;
                replyStream0 << "base : " << distance;
                pmTargetPlayer->Say(replyStream0.str().c_str(), Language::LANG_UNIVERSAL);
            }
            else
            {
                std::ostringstream replyStream;
                replyStream << "No target";
                pmTargetPlayer->Say(replyStream.str().c_str(), Language::LANG_UNIVERSAL);
            }
        }
        else if (pmTargetGroup)
        {
            for (GroupReference* groupRef = pmTargetGroup->GetFirstMember(); groupRef != nullptr; groupRef = groupRef->next())
            {
                Player* member = groupRef->getSource();
                if (member)
                {
                    if (member->GetObjectGuid() != pmCommander->GetObjectGuid())
                    {
                        HandleChatCommand(pmCommander, pmContent, member, pmTargetGroup);
                    }
                }
            }
        }
        else
        {
            HandleChatCommand(pmCommander, pmContent, pmCommander, pmTargetGroup);
        }
    }
    else if (commandName == "apexis")
    {
        std::ostringstream replyStream;
        if (pmTargetPlayer)
        {
            if (commandVector.size() > 1)
            {
                std::string color = commandVector.at(1);
                uint32 entry = 0;
                if (color == "red")
                {
                    entry = 185794;
                }
                else if (color == "yellow")
                {
                    entry = 185792;
                }
                else if (color == "blue")
                {
                    entry = 185795;
                }
                else if (color == "green")
                {
                    entry = 185793;
                }
                if (entry > 0)
                {
                    if (GameObject* pGo = pmTargetPlayer->FindNearestGameObject(entry, INTERACTION_DISTANCE))
                    {
                        pGo->Use(pmTargetPlayer);
                        replyStream << "Use GO : " << pGo->GetObjectGuid().GetCounter();
                    }
                }
                else
                {
                    replyStream << "No color";
                }
            }
            else
            {
                replyStream << "No color";
            }
            pmTargetPlayer->Say(replyStream.str().c_str(), Language::LANG_UNIVERSAL);
        }
        else if (pmTargetGroup)
        {
            for (GroupReference* groupRef = pmTargetGroup->GetFirstMember(); groupRef != nullptr; groupRef = groupRef->next())
            {
                Player* member = groupRef->getSource();
                if (member)
                {
                    if (member->GetObjectGuid() != pmCommander->GetObjectGuid())
                    {
                        HandleChatCommand(pmCommander, pmContent, member, pmTargetGroup);
                    }
                }
            }
        }
        else
        {
            HandleChatCommand(pmCommander, pmContent, pmCommander);
        }
    }
    else if (commandName == "display")
    {
        if (Unit* target = pmCommander->GetSelectedUnit())
        {
            if (commandVector.size() > 1)
            {
                std::string idStr = commandVector.at(1);
                uint32 displayId = atoi(idStr.c_str());
                target->SetDisplayId(displayId);
            }
        }
    }
    else if (commandName == "ndisplay")
    {
        if (Unit* target = pmCommander->GetSelectedUnit())
        {
            if (commandVector.size() > 1)
            {
                std::string idStr = commandVector.at(1);
                uint32 displayId = atoi(idStr.c_str());
                target->SetNativeDisplayId(displayId);
            }
        }
    }
    else if (commandName == "vip")
    {
        if (pmTargetPlayer)
        {
            if (NierStrategy_Base* ns = pmTargetPlayer->nierStrategyMap[pmTargetPlayer->activeStrategyIndex])
            {
                if (commandVector.size() > 1)
                {
                    std::string nameStr = commandVector.at(1);
                    for (uint32 i = 0; i < sCreatureStorage.GetMaxEntry(); ++i)
                    {
                        if (CreatureInfo const* cInfo = sCreatureStorage.LookupEntry<CreatureInfo>(i))
                        {
                            if (cInfo->name == nameStr)
                            {
                                ns->vipEntry = cInfo->entry;
                            }
                        }
                    }
                }
                std::ostringstream replyStream;
                replyStream << "vip - " << ns->vipEntry;
                WhisperTo(pmCommander, replyStream.str(), Language::LANG_UNIVERSAL, pmTargetPlayer);
            }
        }
        else if (pmTargetGroup)
        {
            for (GroupReference* groupRef = pmTargetGroup->GetFirstMember(); groupRef != nullptr; groupRef = groupRef->next())
            {
                Player* member = groupRef->getSource();
                if (member)
                {
                    if (member->GetObjectGuid() != pmCommander->GetObjectGuid())
                    {
                        HandleChatCommand(pmCommander, pmContent, member);
                    }
                }
            }
        }
    }
    else if (commandName == "nearpoint")
    {
        std::ostringstream replyStream;
        if (pmTargetPlayer)
        {
            if (Unit* distanceTarget = pmCommander->GetSelectedUnit())
            {
                float distance = 10.0f;
                if (commandVector.size() > 1)
                {
                    std::string checkStr = commandVector.at(1);
                    distance = atof(checkStr.c_str());
                }
                pmTargetPlayer->nierAction->nm->Chase(distanceTarget, distance, 0.0f);
                replyStream << "chasing : " << distanceTarget->GetName();
                pmTargetPlayer->Say(replyStream.str().c_str(), Language::LANG_UNIVERSAL);
            }
            else
            {
                replyStream << "No target";
            }
            pmTargetPlayer->Say(replyStream.str().c_str(), Language::LANG_UNIVERSAL);
        }
        else if (pmTargetGroup)
        {
            for (GroupReference* groupRef = pmTargetGroup->GetFirstMember(); groupRef != nullptr; groupRef = groupRef->next())
            {
                Player* member = groupRef->getSource();
                if (member)
                {
                    if (member->GetObjectGuid() != pmCommander->GetObjectGuid())
                    {
                        HandleChatCommand(pmCommander, pmContent, member, pmTargetGroup);
                    }
                }
            }
        }
        else
        {
            HandleChatCommand(pmCommander, pmContent, pmCommander);
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
                    WhisperTo(pmCommander, replyStream.str(), Language::LANG_UNIVERSAL, pmTargetPlayer);
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
                    if (member->GetObjectGuid() != pmCommander->GetObjectGuid())
                    {
                        HandleChatCommand(pmCommander, pmContent, member, pmTargetGroup);
                    }
                }
            }
        }
    }
    else if (commandName == "join")
    {
        if (commandVector.size() > 1)
        {
            std::string joinName = commandVector.at(1);
            if (Player* targetPlayer = ObjectAccessor::FindPlayerByName(joinName.c_str()))
            {
                pmCommander->TeleportTo(targetPlayer->GetMapId(), targetPlayer->GetPositionX(), targetPlayer->GetPositionY(), targetPlayer->GetPositionZ(), targetPlayer->GetOrientation());
            }
        }
        else
        {
            if (Player* targetPlayer = pmCommander->GetSelectedPlayer())
            {
                if (targetPlayer->IsInSameGroupWith(pmCommander))
                {
                    pmCommander->TeleportTo(targetPlayer->GetMapId(), targetPlayer->GetPositionX(), targetPlayer->GetPositionY(), targetPlayer->GetPositionZ(), targetPlayer->GetOrientation());
                }
            }
        }
    }
    else if (commandName == "leader")
    {
        if (pmTargetGroup)
        {
            if (pmTargetGroup->GetLeaderGuid() != pmCommander->GetObjectGuid())
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
                    pmTargetGroup->ChangeLeader(pmCommander->GetObjectGuid());
                }
                else
                {
                    sWorld.SendServerMessage(ServerMessageType::SERVER_MSG_CUSTOM, "Leader is valid", pmCommander);
                }
            }
            else
            {
                sWorld.SendServerMessage(ServerMessageType::SERVER_MSG_CUSTOM, "You are the leader", pmCommander);
            }
        }
        else
        {
            sWorld.SendServerMessage(ServerMessageType::SERVER_MSG_CUSTOM, "You are not in a group", pmCommander);
        }
    }
    else if (commandName == "nier")
    {
        if (commandVector.size() > 1)
        {
            std::string nierAction = commandVector.at(1);
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
                sWorld.SendServerMessage(ServerMessageType::SERVER_MSG_CUSTOM, replyStream.str().c_str(), pmCommander);
            }
            else if (nierAction == "offline")
            {
                std::ostringstream replyStream;
                replyStream << "All niers are going offline";
                LogoutNiers();
                sWorld.SendServerMessage(ServerMessageType::SERVER_MSG_CUSTOM, replyStream.str().c_str(), pmCommander);
            }
            else if (nierAction == "online")
            {
                uint32 playerLevel = pmCommander->GetLevel();
                if (playerLevel < 10)
                {
                    std::ostringstream replyStream;
                    replyStream << "You level is too low";
                    sWorld.SendServerMessage(ServerMessageType::SERVER_MSG_CUSTOM, replyStream.str().c_str(), pmCommander);
                }
                else
                {
                    uint32 nierCount = sNierConfig.NierCountEachLevel;
                    if (commandVector.size() > 2)
                    {
                        nierCount = atoi(commandVector.at(2).c_str());
                    }
                    if (nierCount > 0)
                    {
                        std::ostringstream replyTitleStream;
                        replyTitleStream << "nier count to go online : " << nierCount;
                        sWorld.SendServerMessage(ServerMessageType::SERVER_MSG_CUSTOM, replyTitleStream.str().c_str(), pmCommander);
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
                                    sWorld.SendServerMessage(ServerMessageType::SERVER_MSG_CUSTOM, replyTitleStream.str().c_str(), pmCommander);
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
                                            sWorld.SendServerMessage(ServerMessageType::SERVER_MSG_CUSTOM, replyTitleStream.str().c_str(), pmCommander);
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
                if (Unit* target = pmCommander->GetSelectedUnit())
                {
                    if (ns->Engage(target))
                    {
                        int engageLimit = DEFAULT_ACTION_LIMIT_DELAY;
                        if (commandVector.size() > 1)
                        {
                            std::string checkStr = commandVector.at(1);
                            engageLimit = atoi(checkStr.c_str());
                        }
                        ns->actionLimit = engageLimit;
                        ns->ogActionTarget = target->GetObjectGuid();
                        ns->actionType = ActionType::ActionType_Engage;
                        std::ostringstream replyStream;
                        replyStream << "Try to engage " << target->GetName();
                        WhisperTo(pmCommander, replyStream.str(), Language::LANG_UNIVERSAL, pmTargetPlayer);
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
                    if (member->GetObjectGuid() != pmCommander->GetObjectGuid())
                    {
                        HandleChatCommand(pmCommander, pmContent, member);
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
                if (Unit* target = pmCommander->GetSelectedUnit())
                {
                    if (ns->basicStrategyType == BasicStrategyType::BasicStrategyType_Freeze || ns->basicStrategyType == BasicStrategyType::BasicStrategyType_Glue)
                    {
                        ns->basicStrategyType = BasicStrategyType::BasicStrategyType_Normal;
                    }
                    if (pmTargetPlayer->groupRole == GroupRole::GroupRole_Tank)
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
                                        if (member->GetObjectGuid() != pmCommander->GetObjectGuid())
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
                            if (commandVector.size() > 1)
                            {
                                std::string checkStr = commandVector.at(1);
                                engageLimit = atoi(checkStr.c_str());
                            }
                            ns->actionLimit = engageLimit;
                            ns->ogActionTarget = target->GetObjectGuid();
                            ns->actionType = ActionType::ActionType_Engage;
                            std::ostringstream replyStream;
                            replyStream << "Try to engage " << target->GetName();
                            WhisperTo(pmCommander, replyStream.str(), Language::LANG_UNIVERSAL, pmTargetPlayer);
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
                    if (member->GetObjectGuid() != pmCommander->GetObjectGuid())
                    {
                        HandleChatCommand(pmCommander, pmContent, member);
                    }
                }
            }
        }
    }
    else if (commandName == "hold")
    {
        if (pmTargetPlayer)
        {
            bool doAction = true;
            if (commandVector.size() > 1)
            {
                std::string role = commandVector.at(1);
                if (role == "tank")
                {
                    if (pmTargetPlayer->groupRole != GroupRole::GroupRole_Tank)
                    {
                        doAction = false;
                    }
                }
                else if (role == "healer")
                {
                    if (pmTargetPlayer->groupRole != GroupRole::GroupRole_Healer)
                    {
                        doAction = false;
                    }
                }
                else if (role == "dps")
                {
                    if (pmTargetPlayer->groupRole != GroupRole::GroupRole_DPS)
                    {
                        doAction = false;
                    }
                }
                else if (role == "melee")
                {
                    uint32 myClass = pmTargetPlayer->GetClass();
                    if (myClass != Classes::CLASS_WARRIOR && myClass != Classes::CLASS_ROGUE && myClass != Classes::CLASS_PALADIN)
                    {
                        doAction = false;
                    }
                }
            }
            if (doAction)
            {
                if (NierStrategy_Base* ns = pmTargetPlayer->nierStrategyMap[pmTargetPlayer->activeStrategyIndex])
                {
                    ns->basicStrategyType = BasicStrategyType::BasicStrategyType_Hold;
                    pmTargetPlayer->StopMoving();
                    pmTargetPlayer->GetMotionMaster()->Clear();
                    std::ostringstream replyStream;
                    replyStream << "Holding";
                    WhisperTo(pmCommander, replyStream.str(), Language::LANG_UNIVERSAL, pmTargetPlayer);
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
                    if (member->GetObjectGuid() != pmCommander->GetObjectGuid())
                    {
                        HandleChatCommand(pmCommander, pmContent, member);
                    }
                }
            }
        }
    }
    else if (commandName == "caution")
    {
        if (pmTargetPlayer)
        {
            if (NierStrategy_Base* ns = pmTargetPlayer->nierStrategyMap[pmTargetPlayer->activeStrategyIndex])
            {
                if (commandVector.size() > 1)
                {
                    std::string cautionTypeStr = commandVector.at(1);
                    if (commandVector.size() > 2)
                    {
                        std::ostringstream nameStream;
                        nameStream << commandVector.at(2);
                        for (int nameIndex = 3; nameIndex < commandVector.size(); nameIndex++)
                        {
                            nameStream << " " << commandVector.at(nameIndex);
                        }
                        std::string spellNameStr = nameStream.str();
                        if (cautionTypeStr == "add")
                        {
                            std::ostringstream queryStream;
                            queryStream << "SELECT Id FROM spell_template where SpellName = '" << spellNameStr << "'";
                            QueryResult* spellQR = WorldDatabase.Query(queryStream.str().c_str());
                            if (spellQR)
                            {
                                do
                                {
                                    Field* fields = spellQR->Fetch();
                                    uint32 eachId = fields[0].GetUInt32();
                                    if (ns->cautionSpellMap.find(spellNameStr) == ns->cautionSpellMap.end())
                                    {
                                        ns->cautionSpellMap[spellNameStr].insert(eachId);
                                    }
                                    else
                                    {
                                        std::unordered_set<uint32> eachIDSet = ns->cautionSpellMap.find(spellNameStr)->second;
                                        if (eachIDSet.find(eachId) == eachIDSet.end())
                                        {
                                            ns->cautionSpellMap[spellNameStr].insert(eachId);
                                        }
                                    }
                                } while (spellQR->NextRow());
                            }
                            delete spellQR;
                        }
                        else if (cautionTypeStr == "remove")
                        {
                            ns->cautionSpellMap.erase(spellNameStr);
                        }
                    }
                    else if (cautionTypeStr == "clear")
                    {
                        ns->cautionSpellMap.clear();
                    }
                }
                for (std::unordered_map<std::string, std::unordered_set<uint32>>::iterator nameIT = ns->cautionSpellMap.begin(); nameIT != ns->cautionSpellMap.end(); nameIT++)
                {
                    for (std::unordered_set<uint32>::iterator idIT = nameIT->second.begin(); idIT != nameIT->second.end(); idIT++)
                    {
                        std::ostringstream detailsStream;
                        detailsStream << "Caution : " << nameIT->first << " - " << *idIT;
                        WhisperTo(pmCommander, detailsStream.str(), Language::LANG_UNIVERSAL, pmTargetPlayer);
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
                    if (member->GetObjectGuid() != pmCommander->GetObjectGuid())
                    {
                        HandleChatCommand(pmCommander, pmContent, member);
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
                WhisperTo(pmCommander, replyStream.str(), Language::LANG_UNIVERSAL, pmTargetPlayer);
            }
        }
        else if (pmTargetGroup)
        {
            for (GroupReference* groupRef = pmTargetGroup->GetFirstMember(); groupRef != nullptr; groupRef = groupRef->next())
            {
                Player* member = groupRef->getSource();
                if (member)
                {
                    if (member->GetObjectGuid() != pmCommander->GetObjectGuid())
                    {
                        HandleChatCommand(pmCommander, pmContent, member);
                    }
                }
            }
        }
    }
    else if (commandName == "prepare")
    {
        if (pmTargetPlayer)
        {
            pmTargetPlayer->nierAction->Prepare();
        }
        else if (pmTargetGroup)
        {
            for (GroupReference* groupRef = pmTargetGroup->GetFirstMember(); groupRef != nullptr; groupRef = groupRef->next())
            {
                Player* member = groupRef->getSource();
                if (member)
                {
                    if (member->GetObjectGuid() != pmCommander->GetObjectGuid())
                    {
                        HandleChatCommand(pmCommander, pmContent, member);
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
                WhisperTo(pmCommander, "Resting", Language::LANG_UNIVERSAL, pmTargetPlayer);
            }
        }
        else if (pmTargetGroup)
        {
            for (GroupReference* groupRef = pmTargetGroup->GetFirstMember(); groupRef != nullptr; groupRef = groupRef->next())
            {
                Player* member = groupRef->getSource();
                if (member)
                {
                    if (member->GetObjectGuid() != pmCommander->GetObjectGuid())
                    {
                        HandleChatCommand(pmCommander, pmContent, member);
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
                if (Unit* target = pmCommander->GetSelectedUnit())
                {
                    if (ns->Revive(target))
                    {
                        ns->actionLimit = DEFAULT_ACTION_LIMIT_DELAY;
                        ns->ogActionTarget = target->GetObjectGuid();
                        ns->actionType = ActionType::ActionType_Revive;
                        std::ostringstream replyStream;
                        replyStream << "Try to do reviving";
                        WhisperTo(pmCommander, replyStream.str(), Language::LANG_UNIVERSAL, pmTargetPlayer);
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
                    if (member->GetObjectGuid() != pmCommander->GetObjectGuid())
                    {
                        HandleChatCommand(pmCommander, pmContent, member);
                    }
                }
            }
        }
    }
    else if (commandName == "follow")
    {
        if (pmTargetPlayer)
        {
            if (NierStrategy_Base* ns = pmTargetPlayer->nierStrategyMap[pmTargetPlayer->activeStrategyIndex])
            {
                std::ostringstream replyStream;
                if (commandVector.size() > 1)
                {
                    std::string cmdDistanceStr = commandVector.at(1);
                    float cmdDistance = atof(cmdDistanceStr.c_str());
                    if (cmdDistance >= 0.0f && cmdDistance <= NIER_MAX_DISTANCE)
                    {
                        ns->followDistance = cmdDistance;
                        replyStream << "Follow distance - " << ns->followDistance;
                    }
                    else
                    {
                        replyStream << "Distance is not valid";
                    }
                }
                else
                {
                    ns->basicStrategyType = BasicStrategyType::BasicStrategyType_Normal;
                    ns->restLimit = 0;
                    ns->actionLimit = 0;
                    replyStream << "Following - " << ns->followDistance;
                }
                WhisperTo(pmCommander, replyStream.str(), Language::LANG_UNIVERSAL, pmTargetPlayer);
            }
        }
        else if (pmTargetGroup)
        {
            for (GroupReference* groupRef = pmTargetGroup->GetFirstMember(); groupRef != nullptr; groupRef = groupRef->next())
            {
                Player* member = groupRef->getSource();
                if (member)
                {
                    if (member->GetObjectGuid() != pmCommander->GetObjectGuid())
                    {
                        HandleChatCommand(pmCommander, pmContent, member);
                    }
                }
            }
        }
    }
    else if (commandName == "debug")
    {
        if (pmTargetPlayer)
        {
            if (NierStrategy_Base* ns = pmTargetPlayer->nierStrategyMap[pmTargetPlayer->activeStrategyIndex])
            {
                std::ostringstream replyStream;
                if (commandVector.size() > 1)
                {
                    std::string debugContents = commandVector.at(1);
                    if (debugContents == "follow")
                    {
                        if (pmTargetPlayer->nierAction->nm->ogFollowTarget.IsEmpty())
                        {
                            replyStream << "follow target og is empty";
                        }
                        else
                        {
                            if (Player* ft = ObjectAccessor::FindPlayer(pmTargetPlayer->nierAction->nm->ogFollowTarget))
                            {
                                replyStream << "follow target is " << ft->GetName();
                            }
                            else
                            {
                                replyStream << "follow target not found : " << pmTargetPlayer->nierAction->nm->ogFollowTarget.GetCounter();
                            }
                        }
                    }
                }
                WhisperTo(pmCommander, replyStream.str(), Language::LANG_UNIVERSAL, pmTargetPlayer);
            }
        }
        else if (pmTargetGroup)
        {
            for (GroupReference* groupRef = pmTargetGroup->GetFirstMember(); groupRef != nullptr; groupRef = groupRef->next())
            {
                Player* member = groupRef->getSource();
                if (member)
                {
                    if (member->GetObjectGuid() != pmCommander->GetObjectGuid())
                    {
                        HandleChatCommand(pmCommander, pmContent, member);
                    }
                }
            }
        }
    }
    else if (commandName == "chase")
    {
        if (pmTargetPlayer)
        {
            if (NierStrategy_Base* ns = pmTargetPlayer->nierStrategyMap[pmTargetPlayer->activeStrategyIndex])
            {
                std::ostringstream replyStream;
                if (commandVector.size() > 1)
                {
                    std::string cmdDistanceStr = commandVector.at(1);
                    float cmdDistance = atof(cmdDistanceStr.c_str());
                    if (cmdDistance >= CONTACT_DISTANCE && cmdDistance <= NIER_MAX_DISTANCE)
                    {
                        ns->dpsDistance = cmdDistance;
                    }
                    else
                    {
                        replyStream << "Distance is not valid";
                    }
                }
                replyStream << "Chase distance - " << ns->dpsDistance;
                WhisperTo(pmCommander, replyStream.str(), Language::LANG_UNIVERSAL, pmTargetPlayer);
            }
        }
        else if (pmTargetGroup)
        {
            for (GroupReference* groupRef = pmTargetGroup->GetFirstMember(); groupRef != nullptr; groupRef = groupRef->next())
            {
                Player* member = groupRef->getSource();
                if (member)
                {
                    if (member->GetObjectGuid() != pmCommander->GetObjectGuid())
                    {
                        HandleChatCommand(pmCommander, pmContent, member);
                    }
                }
            }
        }
    }
    else if (commandName == "gather")
    {
        if (pmTargetPlayer)
        {
            if (NierStrategy_Base* ns = pmTargetPlayer->nierStrategyMap[pmTargetPlayer->activeStrategyIndex])
            {
                std::ostringstream replyStream;
                if (pmTargetPlayer->IsAlive())
                {
                    if (pmCommander->GetDistance(pmTargetPlayer) < VISIBILITY_DISTANCE_LARGE)
                    {
                        ns->restLimit = 0;
                        ns->actionType = ActionType::ActionType_Move;
                        ns->actionLimit = 3 * IN_MILLISECONDS;
                        pmTargetPlayer->nierAction->nm->Point(pmCommander->GetPosition(), ns->actionLimit);
                        replyStream << "Moving to you";
                    }
                    else
                    {
                        replyStream << "I am too far away";
                    }
                }
                else
                {
                    replyStream << "I am dead";
                }
                WhisperTo(pmCommander, replyStream.str(), Language::LANG_UNIVERSAL, pmTargetPlayer);
            }
        }
        else if (pmTargetGroup)
        {
            for (GroupReference* groupRef = pmTargetGroup->GetFirstMember(); groupRef != nullptr; groupRef = groupRef->next())
            {
                Player* member = groupRef->getSource();
                if (member)
                {
                    if (member->GetObjectGuid() != pmCommander->GetObjectGuid())
                    {
                        HandleChatCommand(pmCommander, pmContent, member);
                    }
                }
            }
        }
    }
    else if (commandName == "move")
    {
        if (pmTargetPlayer)
        {
            std::ostringstream replyStream;
            if (pmTargetPlayer->IsAlive())
            {
                if (commandVector.size() > 1)
                {
                    bool doAction = true;
                    std::string direction = commandVector.at(1);
                    uint32 directionType = NierMovementDirection::NierMovementDirection_Forward;
                    if (direction == "forward")
                    {
                        directionType = NierMovementDirection::NierMovementDirection_Forward;
                    }
                    else if (direction == "back")
                    {
                        directionType = NierMovementDirection::NierMovementDirection_Back;
                    }
                    else if (direction == "left")
                    {
                        directionType = NierMovementDirection::NierMovementDirection_Left;
                    }
                    else if (direction == "right")
                    {
                        directionType = NierMovementDirection::NierMovementDirection_Right;
                    }
                    else
                    {
                        doAction = false;
                        replyStream << "Direction invalid";
                    }
                    if (doAction)
                    {
                        if (commandVector.size() > 2)
                        {
                            std::string role = commandVector.at(2);
                            if (role == "all")
                            {
                                doAction = true;
                            }
                            else if (role == "tank")
                            {
                                if (pmTargetPlayer->groupRole != GroupRole::GroupRole_Tank)
                                {
                                    doAction = false;
                                }
                            }
                            else if (role == "healer")
                            {
                                if (pmTargetPlayer->groupRole != GroupRole::GroupRole_Healer)
                                {
                                    doAction = false;
                                }
                            }
                            else if (role == "dps")
                            {
                                if (pmTargetPlayer->groupRole != GroupRole::GroupRole_DPS)
                                {
                                    doAction = false;
                                }
                            }
                            else if (role == "melee")
                            {
                                uint32 myClass = pmTargetPlayer->GetClass();
                                if (myClass != Classes::CLASS_WARRIOR && myClass != Classes::CLASS_ROGUE && myClass != Classes::CLASS_PALADIN)
                                {
                                    doAction = false;
                                }
                            }
                            else
                            {
                                doAction = false;
                                replyStream << "Role invalid";
                            }
                        }
                        else
                        {
                            doAction = false;
                            replyStream << "No role";
                        }
                        if (doAction)
                        {
                            if (NierStrategy_Base* ns = pmTargetPlayer->nierStrategyMap[pmTargetPlayer->activeStrategyIndex])
                            {
                                uint32 distance = 5;
                                if (commandVector.size() > 3)
                                {
                                    std::string distanceStr = commandVector.at(3);
                                    distance = std::atoi(distanceStr.c_str());
                                }
                                uint32 actionLimit = distance / 5;
                                actionLimit = actionLimit * IN_MILLISECONDS;
                                if (pmTargetPlayer->nierAction->nm->Direction(pmCommander, directionType, actionLimit, distance))
                                {
                                    ns->basicStrategyType = BasicStrategyType::BasicStrategyType_Hold;
                                    ns->restLimit = 0;
                                    ns->actionType = ActionType::ActionType_Move;
                                    ns->actionLimit = actionLimit;
                                    replyStream << direction;
                                }
                                WhisperTo(pmCommander, replyStream.str(), Language::LANG_UNIVERSAL, pmTargetPlayer);
                            }
                        }
                    }
                }
                else
                {
                    replyStream << "No direction";
                }
            }
            else
            {
                replyStream << "I am dead";
            }
        }
        else if (pmTargetGroup)
        {
            for (GroupReference* groupRef = pmTargetGroup->GetFirstMember(); groupRef != nullptr; groupRef = groupRef->next())
            {
                Player* member = groupRef->getSource();
                if (member)
                {
                    if (member->GetObjectGuid() != pmCommander->GetObjectGuid())
                    {
                        HandleChatCommand(pmCommander, pmContent, member);
                    }
                }
            }
        }
    }
    else if (commandName == "cast")
    {
        if (pmTargetPlayer)
        {
            std::ostringstream replyStream;
            if (Unit* targetU = pmCommander->GetSelectedUnit())
            {
                if (commandVector.size() > 1)
                {
                    uint32 spellId = std::stoi(commandVector.at(1));
                    if (pmTargetPlayer->HasActiveSpell(spellId))
                    {
                        pmTargetPlayer->InterruptNonMeleeSpells(true);
                        SpellCastResult scr = pmTargetPlayer->CastSpell(targetU, spellId, false);
                        replyStream << "Cast spell : " << scr;
                    }
                }
                else
                {
                    replyStream << "Spell name missing";
                }
            }
            else
            {
                replyStream << "No target";
            }
            WhisperTo(pmCommander, replyStream.str(), Language::LANG_UNIVERSAL, pmTargetPlayer);
        }
        else if (pmTargetGroup)
        {
            for (GroupReference* groupRef = pmTargetGroup->GetFirstMember(); groupRef != nullptr; groupRef = groupRef->next())
            {
                Player* member = groupRef->getSource();
                if (member)
                {
                    if (member->GetObjectGuid() != pmCommander->GetObjectGuid())
                    {
                        HandleChatCommand(pmCommander, pmContent, member);
                    }
                }
            }
        }
    }
    else if (commandName == "unaura")
    {
        if (Unit* targetU = pmCommander->GetSelectedUnit())
        {
            if (commandVector.size() > 1)
            {
                uint32 spellId = std::stoi(commandVector.at(1));
                targetU->RemoveAurasDueToSpell(spellId);
            }
        }
    }
    else if (commandName == "aura")
    {
        std::ostringstream replyStream;
        if (Unit* targetU = pmCommander->GetSelectedUnit())
        {
            if (commandVector.size() > 1)
            {
                uint32 spellId = std::stoi(commandVector.at(1));
                if (targetU->HasAura(spellId))
                {
                    replyStream << "Yes";
                }
                else
                {
                    replyStream << "No";
                }
            }
            else
            {
                replyStream << "No id";
            }
        }
        else
        {
            replyStream << "No target";
        }
        sWorld.SendServerMessage(ServerMessageType::SERVER_MSG_CUSTOM, replyStream.str().c_str(), pmCommander);
    }
    else if (commandName == "tcast")
    {
        std::ostringstream replyStream;
        if (Unit* targetU = pmCommander->GetSelectedUnit())
        {
            if (commandVector.size() > 1)
            {
                uint32 spellId = std::stoi(commandVector.at(1));
                SpellCastResult scr = targetU->CastSpell(targetU, spellId, false);
                replyStream << "Cast result : " << scr;
            }
            else
            {
                replyStream << "No spell";
            }
        }
        else
        {
            replyStream << "No t";
        }
        sWorld.SendServerMessage(ServerMessageType::SERVER_MSG_CUSTOM, replyStream.str().c_str(), pmCommander);
    }
    else if (commandName == "castt")
    {
        std::ostringstream replyStream;
        if (Unit* targetU = pmCommander->GetSelectedUnit())
        {
            if (commandVector.size() > 1)
            {
                uint32 spellId = std::stoi(commandVector.at(1));
                SpellCastResult scr = pmCommander->CastSpell(targetU, spellId, false);
                replyStream << "Cast result : " << scr;
            }
            else
            {
                replyStream << "No spell";
            }
        }
        else
        {
            replyStream << "No t";
        }
        sWorld.SendServerMessage(ServerMessageType::SERVER_MSG_CUSTOM, replyStream.str().c_str(), pmCommander);
    }
    else if (commandName == "delay")
    {
        if (pmTargetPlayer)
        {
            if (NierStrategy_Base* ns = pmTargetPlayer->nierStrategyMap[pmTargetPlayer->activeStrategyIndex])
            {
                std::ostringstream replyStream;
                if (commandVector.size() > 1)
                {
                    int delayMS = std::stoi(commandVector.at(1));
                    ns->dpsDelay = delayMS;
                    replyStream << "DPS delay set to : " << delayMS;
                }
                else
                {
                    replyStream << "DPS delay is : " << ns->dpsDelay;
                }
                WhisperTo(pmCommander, replyStream.str(), Language::LANG_UNIVERSAL, pmTargetPlayer);
            }
        }
        else if (pmTargetGroup)
        {
            for (GroupReference* groupRef = pmTargetGroup->GetFirstMember(); groupRef != nullptr; groupRef = groupRef->next())
            {
                Player* member = groupRef->getSource();
                if (member)
                {
                    if (member->GetObjectGuid() != pmCommander->GetObjectGuid())
                    {
                        HandleChatCommand(pmCommander, pmContent, member);
                    }
                }
            }
        }
    }
    else if (commandName == "cure")
    {
        if (pmTargetPlayer)
        {
            if (NierStrategy_Base* ns = pmTargetPlayer->nierStrategyMap[pmTargetPlayer->activeStrategyIndex])
            {
                std::ostringstream replyStream;
                if (commandVector.size() > 1)
                {
                    std::string cureCMD = commandVector.at(1);
                    if (cureCMD == "on")
                    {
                        ns->cure = true;
                    }
                    else if (cureCMD == "off")
                    {
                        ns->cure = false;
                    }
                    else
                    {
                        replyStream << "Unknown state";
                    }
                }
                if (ns->cure)
                {
                    replyStream << "auto cure is on";
                }
                else
                {
                    replyStream << "auto cure is off";
                }
                WhisperTo(pmCommander, replyStream.str(), Language::LANG_UNIVERSAL, pmTargetPlayer);
            }
        }
        else if (pmTargetGroup)
        {
            for (GroupReference* groupRef = pmTargetGroup->GetFirstMember(); groupRef != nullptr; groupRef = groupRef->next())
            {
                Player* member = groupRef->getSource();
                if (member)
                {
                    if (member->GetObjectGuid() != pmCommander->GetObjectGuid())
                    {
                        HandleChatCommand(pmCommander, pmContent, member);
                    }
                }
            }
        }
    }
    else if (commandName == "petting")
    {
        if (pmTargetPlayer)
        {
            if (NierStrategy_Base* ns = pmTargetPlayer->nierStrategyMap[pmTargetPlayer->activeStrategyIndex])
            {
                std::ostringstream replyStream;
                if (commandVector.size() > 1)
                {
                    std::string switchCMD = commandVector.at(1);
                    if (switchCMD == "on")
                    {
                        ns->petting = true;
                    }
                    else if (switchCMD == "off")
                    {
                        ns->petting = false;
                    }
                    else if (switchCMD == "reset")
                    {
                        if (pmTargetPlayer->GetClass() == Classes::CLASS_HUNTER)
                        {
                            if (Nier_Hunter* naHunter = (Nier_Hunter*)pmTargetPlayer->nierAction)
                            {
                                if (naHunter->Petting(ns->petting, true))
                                {
                                    replyStream << "Pet abandoned. ";
                                }
                                else
                                {
                                    replyStream << "reset failed";
                                }
                            }
                        }
                    }
                    else
                    {
                        replyStream << "Unknown state";
                    }
                }
                if (ns->petting)
                {
                    replyStream << "Petting is on";
                }
                else
                {
                    replyStream << "Petting is off";
                }
                WhisperTo(pmCommander, replyStream.str(), Language::LANG_UNIVERSAL, pmTargetPlayer);
            }
        }
        else if (pmTargetGroup)
        {
            for (GroupReference* groupRef = pmTargetGroup->GetFirstMember(); groupRef != nullptr; groupRef = groupRef->next())
            {
                Player* member = groupRef->getSource();
                if (member)
                {
                    if (member->GetObjectGuid() != pmCommander->GetObjectGuid())
                    {
                        HandleChatCommand(pmCommander, pmContent, member);
                    }
                }
            }
        }
    }
    else if (commandName == "aoe")
    {
        if (pmTargetPlayer)
        {
            if (NierStrategy_Base* ns = pmTargetPlayer->nierStrategyMap[pmTargetPlayer->activeStrategyIndex])
            {
                std::ostringstream replyStream;
                //if (commandVector.size() > 1)
                //{
                //	std::string roleCMD = commandVector.at(1);
                //	bool onoff = false;
                //	if (commandVector.size() > 2)
                //	{
                //		std::string switchCMD = commandVector.at(2);
                //		if (switchCMD == "on")
                //		{
                //			onoff = true;
                //		}
                //		if (roleCMD == "tank")
                //		{
                //			if (pmTargetPlayer->groupRole == GroupRole::GroupRole_Tank)
                //			{
                //				ns->aoe = onoff;
                //			}
                //		}
                //		else if (roleCMD == "dps")
                //		{
                //			if (pmTargetPlayer->groupRole == GroupRole::GroupRole_DPS)
                //			{
                //				ns->aoe = onoff;
                //			}
                //		}
                //	}
                //}
                //if (ns->aoe)
                //{
                //	replyStream << "AOE is on";
                //}
                //else
                //{
                //	replyStream << "AOE is off";
                //}
                WhisperTo(pmCommander, replyStream.str(), Language::LANG_UNIVERSAL, pmTargetPlayer);
            }
        }
        else if (pmTargetGroup)
        {
            for (GroupReference* groupRef = pmTargetGroup->GetFirstMember(); groupRef != nullptr; groupRef = groupRef->next())
            {
                Player* member = groupRef->getSource();
                if (member)
                {
                    if (member->GetObjectGuid() != pmCommander->GetObjectGuid())
                    {
                        HandleChatCommand(pmCommander, pmContent, member);
                    }
                }
            }
        }
    }
    else if (commandName == "rti")
    {
        if (pmTargetPlayer)
        {
            if (NierStrategy_Base* ns = pmTargetPlayer->nierStrategyMap[pmTargetPlayer->activeStrategyIndex])
            {
                std::ostringstream replyStream;
                int targetIcon = -1;
                if (commandVector.size() > 1)
                {
                    std::string iconIndex = commandVector.at(1);
                    targetIcon = atoi(iconIndex.c_str());
                }
                if (targetIcon >= 0 && targetIcon < TARGET_ICON_COUNT)
                {
                    ns->rti = targetIcon;
                }
                replyStream << "RTI is " << ns->rti;
                WhisperTo(pmCommander, replyStream.str(), Language::LANG_UNIVERSAL, pmTargetPlayer);
            }
        }
        else if (pmTargetGroup)
        {
            for (GroupReference* groupRef = pmTargetGroup->GetFirstMember(); groupRef != nullptr; groupRef = groupRef->next())
            {
                Player* member = groupRef->getSource();
                if (member)
                {
                    if (member->GetObjectGuid() != pmCommander->GetObjectGuid())
                    {
                        HandleChatCommand(pmCommander, pmContent, member);
                    }
                }
            }
        }
    }
    else if (commandName == "portal")
    {
        if (pmTargetPlayer)
        {
            if (pmTargetPlayer->GetClass() == Classes::CLASS_MAGE)
            {
                if (pmTargetPlayer->GetSession()->isNier)
                {
                    if (commandVector.size() > 1)
                    {
                        std::string city = commandVector.at(1);
                        if (Nier_Mage* nam = (Nier_Mage*)pmTargetPlayer->nierAction)
                        {
                            uint32 portalSpell = 0;
                            if (city == "Dalaran")
                            {
                                portalSpell = nam->spell_Portal_Dalaran;
                            }
                            else
                            {
                                uint32 playerRace = pmTargetPlayer->GetRace();
                                if (playerRace == Races::RACE_DWARF || playerRace == Races::RACE_GNOME || playerRace == Races::RACE_HUMAN || playerRace == Races::RACE_NIGHTELF)
                                {
                                    if (city == "stormwind")
                                    {
                                        portalSpell = nam->spell_Portal_Stormwind;
                                    }
                                    else if (city == "darnassus")
                                    {
                                        portalSpell = nam->spell_Portal_Darnassus;
                                    }
                                    else if (city == "ironforge")
                                    {
                                        portalSpell = nam->spell_Portal_Ironforge;
                                    }
                                    else if (city == "shattrath")
                                    {
                                        portalSpell = nam->spell_Portal_Shattrath_A;
                                    }
                                }
                                else
                                {
                                    if (city == "orgrimmar")
                                    {
                                        portalSpell = nam->spell_Portal_Orgrimmar;
                                    }
                                    else if (city == "thunderbluff")
                                    {
                                        portalSpell = nam->spell_Portal_ThunderBluff;
                                    }
                                    else if (city == "undercity")
                                    {
                                        portalSpell = nam->spell_Portal_Shattrath_H;
                                    }
                                }
                            }
                            if (portalSpell > 0)
                            {
                                std::ostringstream replyStream;
                                replyStream << "Portal to " << city;
                                pmTargetPlayer->Say(replyStream.str().c_str(), Language::LANG_UNIVERSAL);
                                nam->CastSpell(pmTargetPlayer, portalSpell);
                            }
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
                    if (member->GetObjectGuid() != pmCommander->GetObjectGuid())
                    {
                        HandleChatCommand(pmCommander, pmContent, member);
                    }
                }
            }
        }
    }
    else if (commandName == "home")
    {
        if (pmTargetPlayer)
        {
            if (pmTargetPlayer->GetSession()->isNier)
            {
                WhisperTo(pmCommander, "Going home", Language::LANG_UNIVERSAL, pmTargetPlayer);
                pmTargetPlayer->TeleportToHomebind();
            }
        }
        else if (pmTargetGroup)
        {
            for (GroupReference* groupRef = pmTargetGroup->GetFirstMember(); groupRef != nullptr; groupRef = groupRef->next())
            {
                Player* member = groupRef->getSource();
                if (member)
                {
                    if (member->GetObjectGuid() != pmCommander->GetObjectGuid())
                    {
                        HandleChatCommand(pmCommander, pmContent, member);
                    }
                }
            }
        }
    }
    else if (commandName == "instant")
    {
        if (pmTargetPlayer)
        {
            if (NierStrategy_Base* ns = pmTargetPlayer->nierStrategyMap[pmTargetPlayer->activeStrategyIndex])
            {
                std::ostringstream replyStream;
                if (commandVector.size() > 1)
                {
                    std::string instantType = commandVector.at(1);
                    if (instantType == "on")
                    {
                        ns->instantOnly = true;
                    }
                    else
                    {
                        ns->instantOnly = false;
                    }
                }
                replyStream << "Instant type is : ";
                if (ns->instantOnly)
                {
                    replyStream << "on";
                }
                else
                {
                    replyStream << "off";
                }
                WhisperTo(pmCommander, replyStream.str(), Language::LANG_UNIVERSAL, pmTargetPlayer);
            }
        }
        else if (pmTargetGroup)
        {
            for (GroupReference* groupRef = pmTargetGroup->GetFirstMember(); groupRef != nullptr; groupRef = groupRef->next())
            {
                Player* member = groupRef->getSource();
                if (member)
                {
                    if (member->GetObjectGuid() != pmCommander->GetObjectGuid())
                    {
                        HandleChatCommand(pmCommander, pmContent, member);
                    }
                }
            }
        }
    }
    else if (commandName == "glue")
    {
        if (pmTargetPlayer)
        {
            if (NierStrategy_Base* ns = pmTargetPlayer->nierStrategyMap[pmTargetPlayer->activeStrategyIndex])
            {
                std::ostringstream replyStream;
                ns->basicStrategyType = BasicStrategyType::BasicStrategyType_Glue;
                pmTargetPlayer->nierAction->nm->ResetMovement();
                replyStream << "bst : " << ns->basicStrategyType;
                WhisperTo(pmCommander, replyStream.str(), Language::LANG_UNIVERSAL, pmTargetPlayer);
            }
        }
        else if (pmTargetGroup)
        {
            for (GroupReference* groupRef = pmTargetGroup->GetFirstMember(); groupRef != nullptr; groupRef = groupRef->next())
            {
                Player* member = groupRef->getSource();
                if (member)
                {
                    if (member->GetObjectGuid() != pmCommander->GetObjectGuid())
                    {
                        HandleChatCommand(pmCommander, pmContent, member);
                    }
                }
            }
        }
    }
    else if (commandName == "innervate")
    {
        if (pmTargetPlayer)
        {
            if (pmTargetPlayer->GetClass() == Classes::CLASS_DRUID)
            {
                if (pmTargetPlayer->GetSession()->isNier)
                {
                    if (Nier_Druid* nad = (Nier_Druid*)pmTargetPlayer->nierAction)
                    {
                        if (nad->spell_Innervate > 0)
                        {
                            if (commandVector.size() > 1)
                            {
                                std::string roleName = commandVector.at(1);
                                if (roleName == "self")
                                {
                                    //if (nad->spell_MoonkinForm > 0)
                                    //{
                                    //    nad->CancelAura(nad->spell_MoonkinForm);
                                    //}
                                    if (nad->CastSpell(pmTargetPlayer, nad->spell_Innervate, true, false, true))
                                    {
                                        std::ostringstream replyStream;
                                        replyStream << "Innervate - " << pmTargetPlayer->GetName();
                                        pmTargetPlayer->Yell(replyStream.str().c_str(), Language::LANG_UNIVERSAL);
                                    }
                                }
                                else if (roleName == "healer")
                                {
                                    if (Group* targetGroup = pmTargetPlayer->GetGroup())
                                    {
                                        for (GroupReference* groupRef = targetGroup->GetFirstMember(); groupRef != nullptr; groupRef = groupRef->next())
                                        {
                                            if (Player* member = groupRef->getSource())
                                            {
                                                if (member->groupRole == GroupRole::GroupRole_Healer)
                                                {
                                                    if (member->IsAlive())
                                                    {
                                                        if (pmTargetPlayer->GetDistance(member) < NIER_FAR_DISTANCE)
                                                        {
                                                            //if (nad->spell_MoonkinForm > 0)
                                                            //{
                                                            //    nad->CancelAura(nad->spell_MoonkinForm);
                                                            //}
                                                            if (nad->CastSpell(member, nad->spell_Innervate, true, false, true))
                                                            {
                                                                std::ostringstream replyStream;
                                                                replyStream << "Innervate - " << member->GetName();
                                                                pmTargetPlayer->Yell(replyStream.str().c_str(), Language::LANG_UNIVERSAL);
                                                                break;
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
                    if (member->GetObjectGuid() != pmCommander->GetObjectGuid())
                    {
                        HandleChatCommand(pmCommander, pmContent, member);
                    }
                }
            }
        }
    }
    else if (commandName == "assist")
    {
        if (pmTargetPlayer)
        {
            if (NierStrategy_Base* ns = pmTargetPlayer->nierStrategyMap[pmTargetPlayer->activeStrategyIndex])
            {
                if (ns->rti >= 0)
                {
                    if (Group* targetGroup = pmTargetPlayer->GetGroup())
                    {
                        ObjectGuid ogRTI = targetGroup->GetGuidByTargetIcon(ns->rti);
                        Unit* rtiTarget = nullptr;
                        if (!ogRTI.IsEmpty())
                        {
                            rtiTarget = ObjectAccessor::GetUnit(*pmTargetPlayer, ogRTI);
                        }
                        else
                        {
                            if (pmTargetPlayer->IsInCombat())
                            {
                                bool marked = false;
                                std::set<Unit*> checkAttackers = pmTargetPlayer->GetAttackers();
                                for (std::set<Unit*>::iterator ait = checkAttackers.begin(); ait != checkAttackers.end(); ++ait)
                                {
                                    if (Unit* eachAttacker = *ait)
                                    {
                                        if (pmTargetPlayer->IsValidAttackTarget(eachAttacker))
                                        {
                                            if (targetGroup->GetTargetIconByGuid(eachAttacker->GetObjectGuid()) < 0)
                                            {
                                                if (pmTargetPlayer->nierAction->Mark(eachAttacker, ns->rti))
                                                {
                                                    marked = true;
                                                    break;
                                                }
                                            }
                                        }
                                    }
                                }
                                if (!marked)
                                {
                                    std::list<Creature*> creatureList;
                                    pmTargetPlayer->GetCreatureListWithEntryInGrid(creatureList, 0, VISIBILITY_DISTANCE_NORMAL);
                                    if (!creatureList.empty())
                                    {
                                        for (std::list<Creature*>::iterator itr = creatureList.begin(); itr != creatureList.end(); ++itr)
                                        {
                                            if (Creature* hostileCreature = *itr)
                                            {
                                                if (pmTargetPlayer->IsValidAttackTarget(hostileCreature))
                                                {
                                                    if (targetGroup->GetTargetIconByGuid(hostileCreature->GetObjectGuid()) < 0)
                                                    {
                                                        if (hostileCreature->IsInCombat())
                                                        {
                                                            if (pmTargetPlayer->nierAction->Mark(hostileCreature, ns->rti))
                                                            {
                                                                marked = true;
                                                                break;
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
                        if (rtiTarget)
                        {
                            pmTargetPlayer->nierAction->Assist(ns->rti);
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
                    if (member->GetObjectGuid() != pmCommander->GetObjectGuid())
                    {
                        HandleChatCommand(pmCommander, pmContent, member);
                    }
                }
            }
        }
    }
    else if (commandName == "equip")
    {
        if (pmTargetPlayer)
        {
            std::ostringstream replyStream;
            if (commandVector.size() > 1)
            {
                uint32 entry = 0;
                std::string equipTypeName = commandVector.at(1);
                if (equipTypeName == "name")
                {
                    if (commandVector.size() > 2)
                    {
                        std::string itemName = commandVector.at(2);
                        std::ostringstream queryStream;
                        queryStream << "SELECT entry FROM item_template where name = '" << itemName << "'";
                        QueryResult* itemQR = WorldDatabase.Query(queryStream.str().c_str());
                        if (itemQR)
                        {
                            do
                            {
                                Field* fields = itemQR->Fetch();
                                entry = fields[0].GetUInt32();
                                break;
                            } while (itemQR->NextRow());
                        }
                        delete itemQR;
                    }
                    else
                    {
                        replyStream << "Missing name";
                    }
                }
                else if (equipTypeName == "entry")
                {
                    if (commandVector.size() > 2)
                    {
                        std::string entryStr = commandVector.at(2);
                        entry = std::atoi(entryStr.c_str());
                    }
                    else
                    {
                        replyStream << "Missing entry";
                    }
                }
                if (entry > 0)
                {
                    std::ostringstream queryStream;
                    queryStream << "SELECT entry FROM item_template where entry = " << entry << "";
                    QueryResult* itemQR = WorldDatabase.Query(queryStream.str().c_str());
                    if (itemQR)
                    {
                        do
                        {
                            Field* fields = itemQR->Fetch();
                            uint32 entry = fields[0].GetUInt32();
                            if (const ItemPrototype* proto = sObjectMgr.GetItemPrototype(entry))
                            {
                                if (Item* pItem = Item::CreateItem(entry, 1))
                                {
                                    uint32 equipSlot = 0;
                                    switch (proto->InventoryType)
                                    {
                                    case INVTYPE_HEAD:
                                    {
                                        equipSlot = EQUIPMENT_SLOT_HEAD;
                                        break;
                                    }
                                    case INVTYPE_NECK:
                                    {
                                        equipSlot = EQUIPMENT_SLOT_NECK;
                                        break;
                                    }
                                    case INVTYPE_SHOULDERS:
                                    {
                                        equipSlot = EQUIPMENT_SLOT_SHOULDERS;
                                        break;
                                    }
                                    case INVTYPE_BODY:
                                    {
                                        equipSlot = EQUIPMENT_SLOT_BODY;
                                        break;
                                    }
                                    case INVTYPE_CHEST:
                                    {
                                        equipSlot = EQUIPMENT_SLOT_CHEST;
                                        break;
                                    }
                                    case INVTYPE_ROBE:
                                    {
                                        equipSlot = EQUIPMENT_SLOT_CHEST;
                                        break;
                                    }
                                    case INVTYPE_WAIST:
                                    {
                                        equipSlot = EQUIPMENT_SLOT_WAIST;
                                        break;
                                    }
                                    case INVTYPE_LEGS:
                                    {
                                        equipSlot = EQUIPMENT_SLOT_LEGS;
                                        break;
                                    }
                                    case INVTYPE_FEET:
                                    {
                                        equipSlot = EQUIPMENT_SLOT_FEET;
                                        break;
                                    }
                                    case INVTYPE_WRISTS:
                                    {
                                        equipSlot = EQUIPMENT_SLOT_WRISTS;
                                        break;
                                    }
                                    case INVTYPE_HANDS:
                                    {
                                        equipSlot = EQUIPMENT_SLOT_HANDS;
                                        break;
                                    }
                                    case INVTYPE_FINGER:
                                    {
                                        equipSlot = EQUIPMENT_SLOT_FINGER1;
                                        //viable_slots[1] = EQUIPMENT_SLOT_FINGER2;
                                        break;
                                    }
                                    case INVTYPE_TRINKET:
                                    {
                                        equipSlot = EQUIPMENT_SLOT_TRINKET1;
                                        //viable_slots[1] = EQUIPMENT_SLOT_TRINKET2;
                                        break;
                                    }
                                    case INVTYPE_CLOAK:
                                    {
                                        equipSlot = EQUIPMENT_SLOT_BACK;
                                        break;
                                    }
                                    case INVTYPE_WEAPON:
                                    {
                                        equipSlot = EQUIPMENT_SLOT_MAINHAND;
                                        //if (CanDualWield())
                                        //{										
                                        //	viable_slots[1] = EQUIPMENT_SLOT_OFFHAND;
                                        //}
                                        break;
                                    }
                                    case INVTYPE_SHIELD:
                                    {
                                        equipSlot = EQUIPMENT_SLOT_OFFHAND;
                                        break;
                                    }
                                    case INVTYPE_RANGED:
                                    {
                                        equipSlot = EQUIPMENT_SLOT_RANGED;
                                        break;
                                    }
                                    case INVTYPE_2HWEAPON:
                                    {
                                        equipSlot = EQUIPMENT_SLOT_MAINHAND;
                                        //if (CanDualWield() && CanTitanGrip())
                                        //{										
                                        //	viable_slots[1] = EQUIPMENT_SLOT_OFFHAND;
                                        //}
                                        break;
                                    }
                                    case INVTYPE_TABARD:
                                    {
                                        equipSlot = EQUIPMENT_SLOT_TABARD;
                                        break;
                                    }
                                    case INVTYPE_WEAPONMAINHAND:
                                    {
                                        equipSlot = EQUIPMENT_SLOT_MAINHAND;
                                        break;
                                    }
                                    case INVTYPE_WEAPONOFFHAND:
                                    {
                                        equipSlot = EQUIPMENT_SLOT_OFFHAND;
                                        break;
                                    }
                                    case INVTYPE_HOLDABLE:
                                    {
                                        equipSlot = EQUIPMENT_SLOT_OFFHAND;
                                        break;
                                    }
                                    case INVTYPE_THROWN:
                                    {
                                        equipSlot = EQUIPMENT_SLOT_RANGED;
                                        break;
                                    }
                                    case INVTYPE_RANGEDRIGHT:
                                    {
                                        equipSlot = EQUIPMENT_SLOT_RANGED;
                                        break;
                                    }
                                    case INVTYPE_BAG:
                                    {
                                        equipSlot = INVENTORY_SLOT_BAG_START + 0;
                                        //viable_slots[1] = INVENTORY_SLOT_BAG_START + 1;
                                        //viable_slots[2] = INVENTORY_SLOT_BAG_START + 2;
                                        //viable_slots[3] = INVENTORY_SLOT_BAG_START + 3;
                                        break;
                                    }
                                    case INVTYPE_RELIC:
                                    {
                                        //pClass = getClass();
                                        //if (pClass)
                                        //{
                                        //	switch (proto->SubClass)
                                        //	{
                                        //	case ITEM_SUBCLASS_ARMOR_LIBRAM:											
                                        //		if (pClass == CLASS_PALADIN)
                                        //		{
                                        //			equipSlot = EQUIPMENT_SLOT_RANGED;
                                        //		}
                                        //		break;
                                        //	case ITEM_SUBCLASS_ARMOR_IDOL:											
                                        //		if (pClass == CLASS_DRUID)
                                        //		{
                                        //			equipSlot = EQUIPMENT_SLOT_RANGED;
                                        //		}
                                        //		break;
                                        //	case ITEM_SUBCLASS_ARMOR_TOTEM:											
                                        //		if (pClass == CLASS_SHAMAN)
                                        //		{
                                        //			equipSlot = EQUIPMENT_SLOT_RANGED;
                                        //		}
                                        //		break;
                                        //	case ITEM_SUBCLASS_ARMOR_MISC:											
                                        //		if (pClass == CLASS_WARLOCK)
                                        //		{
                                        //			equipSlot = EQUIPMENT_SLOT_RANGED;
                                        //		}
                                        //		break;
                                        //	case ITEM_SUBCLASS_ARMOR_SIGIL:											
                                        //		if (pClass == CLASS_DEATH_KNIGHT)
                                        //		{
                                        //			equipSlot = EQUIPMENT_SLOT_RANGED;
                                        //		}
                                        //		break;
                                        //	default:											
                                        //		break;
                                        //	}
                                        //}
                                        break;
                                    }
                                    default:
                                    {
                                        break;
                                    }
                                    }
                                    if (Item* currentEquip = pmTargetPlayer->GetItemByPos(INVENTORY_SLOT_BAG_0, equipSlot))
                                    {
                                        if (const ItemPrototype* checkIT = currentEquip->GetProto())
                                        {
                                            pmTargetPlayer->DestroyItem(INVENTORY_SLOT_BAG_0, equipSlot, true);
                                        }
                                    }
                                    uint16 dest = 0;
                                    if (pmTargetPlayer->CanEquipItem(equipSlot, dest, pItem, false) == InventoryResult::EQUIP_ERR_OK)
                                    {
                                        pmTargetPlayer->EquipItem(dest, pItem, true);
                                        replyStream << "Equiped " << pItem->GetProto()->Name1;
                                    }
                                    else
                                    {
                                        replyStream << "Can not equip " << pItem->GetProto()->Name1;
                                    }
                                }
                            }
                            break;
                        } while (itemQR->NextRow());
                    }
                    else
                    {
                        replyStream << "Item not found : " << entry;
                    }
                    delete itemQR;
                }
                else
                {
                    replyStream << "Item entry not found : " << entry;
                }
            }
            else
            {
                for (std::unordered_set<NierEntity*>::iterator reIT = nierEntitySet.begin(); reIT != nierEntitySet.end(); reIT++)
                {
                    if (NierEntity* eachNier = *reIT)
                    {
                        if (eachNier->character_id == pmTargetPlayer->GetObjectGuid().GetCounter())
                        {
                            pmTargetPlayer->nierAction->InitializeEquipments(true);
                            eachNier->entityState = NierEntityState::NierEntityState_Equip;
                            eachNier->checkDelay = 100;
                            replyStream << "Equipments reset";
                            break;
                        }
                    }
                }
            }
            WhisperTo(pmCommander, replyStream.str(), Language::LANG_UNIVERSAL, pmTargetPlayer);
        }
        else if (pmTargetGroup)
        {
            for (GroupReference* groupRef = pmTargetGroup->GetFirstMember(); groupRef != nullptr; groupRef = groupRef->next())
            {
                Player* member = groupRef->getSource();
                if (member)
                {
                    if (member->GetObjectGuid() != pmCommander->GetObjectGuid())
                    {
                        HandleChatCommand(pmCommander, pmContent, member);
                    }
                }
            }
        }
        else
        {
            //HandleChatCommand(pmCommander, pmContent, pmCommander);
        }
    }
    else if (commandName == "rush")
    {
        if (pmTargetPlayer)
        {
            if (NierStrategy_Base* ns = pmTargetPlayer->nierStrategyMap[pmTargetPlayer->activeStrategyIndex])
            {
                if (ns->basicStrategyType == BasicStrategyType::BasicStrategyType_Freeze || ns->basicStrategyType == BasicStrategyType::BasicStrategyType_Glue)
                {
                    ns->basicStrategyType = BasicStrategyType::BasicStrategyType_Normal;
                }
                if (Unit* target = pmCommander->GetSelectedUnit())
                {
                    if (ns->Engage(target))
                    {
                        int engageLimit = DEFAULT_ACTION_LIMIT_DELAY;
                        if (commandVector.size() > 1)
                        {
                            std::string checkStr = commandVector.at(1);
                            engageLimit = atoi(checkStr.c_str());
                        }
                        ns->rushing = true;
                        ns->actionLimit = engageLimit;
                        ns->ogActionTarget = target->GetObjectGuid();
                        ns->actionType = ActionType::ActionType_Engage;
                        std::ostringstream replyStream;
                        replyStream << "Rush " << target->GetName();
                        WhisperTo(pmCommander, replyStream.str(), Language::LANG_UNIVERSAL, pmTargetPlayer);
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
                    if (member->GetObjectGuid() != pmCommander->GetObjectGuid())
                    {
                        HandleChatCommand(pmCommander, pmContent, member);
                    }
                }
            }
        }
    }
    else if (commandName == "talent")
    {
        if (pmTargetPlayer)
        {
            std::ostringstream replyStream;
            pmTargetPlayer->nierAction->ResetTalent();
            replyStream << "Talents reset";
            WhisperTo(pmCommander, replyStream.str(), Language::LANG_UNIVERSAL, pmTargetPlayer);
        }
        else if (pmTargetGroup)
        {
            for (GroupReference* groupRef = pmTargetGroup->GetFirstMember(); groupRef != nullptr; groupRef = groupRef->next())
            {
                Player* member = groupRef->getSource();
                if (member)
                {
                    if (member->GetObjectGuid() != pmCommander->GetObjectGuid())
                    {
                        HandleChatCommand(pmCommander, pmContent, member);
                    }
                }
            }
        }
    }
    else if (commandName == "pvp")
    {
        if (Player* target = pmCommander->GetSelectedPlayer())
        {
            target->SetPvP(true);
            target->UpdatePvP(true);
            target->pvpInfo.inPvPCombat = true;
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
