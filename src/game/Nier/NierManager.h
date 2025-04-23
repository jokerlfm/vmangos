#ifndef NIER_MANAGER_H
#define NIER_MANAGER_H

#ifndef NIER_MANAGER_CHECK_DELAY
#define NIER_MANAGER_CHECK_DELAY 500
#endif

#include <string>
#include <iostream>
#include <sstream>

#include "MingManager.h"

#include "NierConfig.h"
#include "Nier_Base.h"

enum ShapeshiftSpell :uint32
{
    CatForm = 768,
    DireBearForm = 9634,
    BearForm = 5487,
    MoonkinForm = 24858
};

class Nier_Base;

class NierManager
{
    NierManager();
    NierManager(NierManager const&) = delete;
    NierManager& operator=(NierManager const&) = delete;
    ~NierManager() = default;

public:
    void InitializeManager();
    void UpdateNier(uint32 pDiff);
    void LogoutNiers(bool pmInstant = false);
    void DeleteNiers();
    bool CreateNier(uint32 pMasterId, uint32 pClass, uint32 pRace);
    bool LoginNiers(uint32 pMasterId);

    Nier_Base* GetNier(uint32 pNierId);

    bool IsPolymorphed(Unit* pmTarget);

    bool HasAura(Unit* pmTarget, uint32 pmSpellId, Unit* pmCaster = NULL);
    bool MissingAura(Unit* pmTarget, uint32 pmSpellId, Unit* pmCaster = NULL);
    uint32 GetAuraDuration(Unit* pmTarget, uint32 pmSpellId, Unit* pmCaster = NULL);
    uint32 GetAuraStack(Unit* pmTarget, uint32 pmSpellId, Unit* pmCaster = NULL);

    Position PredictPosition(Unit* target);

    void HandleNierChatCommand(Player* pCommander, std::vector<std::string> pCommandVector, int pNierId);
    void HandlePacket(const WorldSession* pSession, WorldPacket pPacket);

    void WhisperTo(Player* pmTarget, std::string pmContent, Language pmLanguage, Player* pmSender);

    std::unordered_set<Creature*> GetCreatureSetInRange(Unit* pSearcher, uint32 pCreatureEntry, float pRange);

    static NierManager* instance();

public:
    std::unordered_map<uint32, Nier_Base*> nierMap;
    std::unordered_map<uint32, std::unordered_map<uint32, uint32>> allianceRaces;
    std::unordered_map<uint32, std::unordered_map<uint32, uint32>> hordeRaces;
    uint32 nameIndex;
    std::unordered_map<uint32, std::string> nierNameMap;
    std::unordered_map<uint32, std::unordered_map<uint32, std::string>> characterTalentTabNameMap;
    std::unordered_set<uint32> instanceEncounterEntrySet;

    // inventorytype - sub class - required level - item index, item entry
    std::unordered_map<uint32, std::unordered_map<uint32, std::unordered_map<uint32, std::unordered_map<uint32, uint32>>>> equipsMap;

private:

};

class AllCreaturesOfEntryInRange_Nier
{
public:
    AllCreaturesOfEntryInRange_Nier(WorldObject const* pObject, uint32 uiEntry, float fMaxRange) : m_pObject(pObject), m_uiEntry(uiEntry), m_fRange(fMaxRange) {}
    bool operator() (Unit* pUnit)
    {
        if (m_uiEntry > 0)
        {
            if (pUnit->GetEntry() != m_uiEntry)
            {
                return false;
            }
        }
        if (!m_pObject->IsWithinDist(pUnit, m_fRange, false))
        {
            return false;
        }

        return true;
    }

private:
    WorldObject const* m_pObject;
    uint32 m_uiEntry;
    float m_fRange;
};

#define sNierManager NierManager::instance()

#endif
