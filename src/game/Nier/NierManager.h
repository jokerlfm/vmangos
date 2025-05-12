#ifndef NIER_MANAGER_H
#define NIER_MANAGER_H

#include"Nier_Base.h"

#include <string>
#include <iostream>
#include <sstream>

#include "NierConfig.h"

class Nier_Base;

class NierManager
{
    NierManager();
    NierManager(NierManager const&) = delete;
    NierManager& operator=(NierManager const&) = delete;
    ~NierManager() = default;

public:
    void InitializeManager();
    void Update(uint32 pDiff);
    void LogoutNiers(bool pmInstant = false);
    void DeleteNiers();
    bool CreateNier(uint32 pMasterId, uint32 pClass, uint32 pRace);
    bool LoginNiers(uint32 pMasterId);

    Nier_Base* GetNier(uint32 pNierId);

    bool IsPolymorphed(Unit* pmTarget);

    bool HasAura(Unit* pTarget, uint32 pSpellId, Unit* pCaster = NULL);
    uint32 GetAuraDuration(Unit* pTarget, uint32 pSpellId, Unit* pCaster = NULL);
    uint32 GetAuraStack(Unit* pTarget, uint32 pSpellId, Unit* pCaster = NULL);

    void HandleChatCommand(Player* pCommander, std::string pCommand, Player* pTarget);
    void HandlePacket(const WorldSession* pSession, WorldPacket pPacket);

    void WhisperTo(Player* pTarget, std::string pContent, Player* pSender);

    std::vector<std::string> SplitString(std::string srcStr, std::string delimStr, bool repeatedCharIgnored);
    std::string TrimString(std::string srcStr);

    static NierManager* instance();

public:
    std::unordered_map<uint32, Nier_Base*> nierMap;
    std::unordered_map<uint32, std::unordered_map<uint32, uint32>> allianceRaces;
    std::unordered_map<uint32, std::unordered_map<uint32, uint32>> hordeRaces;
    uint32 nameIndex;
    std::unordered_map<uint32, std::string> nierNameMap;
    std::unordered_map<uint32, std::unordered_map<uint32, std::string>> characterTalentTabNameMap;
    std::unordered_set<uint32> instanceEncounterEntrySet;

private:
    uint64 timeValue;
};
#define sNierManager NierManager::instance()

#endif
