#ifndef MING_MANAGER_H
#define MING_MANAGER_H

#ifndef MING_OWNER_ACCOUNT_NAME
#define MING_OWNER_ACCOUNT_NAME "MING"
#endif

#ifndef MING_OWNER_CHARACTER_NAME
#define MING_OWNER_CHARACTER_NAME "ming"
#endif

#include <string>
#include "Log.h"
#include "AuctionHouse/AuctionHouseMgr.h"
#include "Item.h"

#include "MingConfig.h"

class MingManager
{
    MingManager();
    MingManager(MingManager const&) = delete;
    MingManager& operator=(MingManager const&) = delete;
    ~MingManager() = default;

public:
    void InitializeManager();
    void Clean();
    bool UpdateMing(uint32 pDiff);

    bool StringEndWith(const std::string& str, const std::string& tail);
    bool StringStartWith(const std::string& str, const std::string& head);
    std::vector<std::string> SplitString(std::string srcStr, std::string delimStr, bool repeatedCharIgnored);
    std::string TrimString(std::string srcStr);

    static MingManager* instance();

private:
    bool UpdateSeller(uint32 pDiff);
    bool UpdateBuyer(uint32 pDiff);
    void ResetSellableItems();

public:
    std::unordered_set<uint32> vendorUnlimitItemSet;

    int32 buyerRefillDelay;
    int32 sellerRefillDelay;

    /// <summary>
    /// class, subclass, inventory, level, entry set
    /// </summary>
    std::unordered_map < uint32, std::unordered_map<uint32, std::unordered_map<uint32, std::unordered_map<uint32, std::unordered_set<uint32>>>>> equipsMap;

private:
    std::unordered_set<uint32> exceptionEntrySet;
    std::unordered_map<uint32, uint32> sellableItemIdMap;

    std::unordered_set<uint32> toSellItemIdSet;
    std::unordered_set<uint32> toBuyAuctionIdSet;
    uint32 boughtCount;
    std::set<uint32> auctionHouseIDSet;

};

#define sMingManager MingManager::instance()

#endif
