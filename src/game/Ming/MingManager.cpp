#include "MingManager.h"
#include "AuctionHouseMgr.h"
#include "AccountMgr.h"

MingManager::MingManager()
{
    buyerRefillDelay = 0;
    sellerRefillDelay = 0;
    auctionHouseIDSet.clear();
    vendorUnlimitItemSet.clear();
    toSellItemIdSet.clear();
    toBuyAuctionIdSet.clear();
    boughtCount = 0;
    sellableItemIdMap.clear();
    exceptionEntrySet.clear();
    equipsMap.clear();
}

MingManager* MingManager::instance()
{
    static MingManager instance;
    return &instance;
}

void MingManager::InitializeManager()
{
    sLog.Out(LOG_BASIC, LOG_LVL_BASIC, "Initialize ming manager");

    buyerRefillDelay = 1 * TimeConstants::HOUR * TimeConstants::IN_MILLISECONDS;
    sellerRefillDelay = 1 * TimeConstants::HOUR * TimeConstants::IN_MILLISECONDS;

    auctionHouseIDSet.clear();
    auctionHouseIDSet.insert(1);
    auctionHouseIDSet.insert(2);
    auctionHouseIDSet.insert(3);

    vendorUnlimitItemSet.clear();
    std::unique_ptr<QueryResult> vendorItemQR = WorldDatabase.Query("SELECT distinct item FROM npc_vendor where maxcount = 0");
    if (vendorItemQR)
    {
        do
        {
            Field* fields = vendorItemQR->Fetch();
            uint32 eachItemEntry = fields[0].GetUInt32();
            vendorUnlimitItemSet.insert(eachItemEntry);
        } while (vendorItemQR->NextRow());
    }
    exceptionEntrySet.clear();
    exceptionEntrySet.insert(24358);
    exceptionEntrySet.insert(5558);
    exceptionEntrySet.insert(20370);
    exceptionEntrySet.insert(20372);

    ResetSellableItems();

    if (sMingConfig.Reset > 0)
    {
        std::ostringstream sqlAccountStream;
        sqlAccountStream << "SELECT id FROM account where username = '" << MING_OWNER_ACCOUNT_NAME << "'";
        std::string sqlAccount = sqlAccountStream.str();
        std::unique_ptr<QueryResult> qrAccount = LoginDatabase.Query(sqlAccount.c_str());

        if (qrAccount)
        {
            do
            {
                Field* fields = qrAccount->Fetch();
                uint32 mingAccountId = fields[0].GetUInt32();
                sAccountMgr.DeleteAccount(mingAccountId);
            } while (qrAccount->NextRow());
        }
    }
}

void MingManager::Clean()
{
    sLog.Out(LOG_BASIC, LOG_LVL_BASIC, "Ready to clean ming");

    for (std::set<uint32>::iterator ahIDIT = auctionHouseIDSet.begin(); ahIDIT != auctionHouseIDSet.end(); ahIDIT++)
    {
        uint32 ahID = *ahIDIT;
        AuctionHouseEntry const* ahEntry = sAuctionHouseStore.LookupEntry(*ahIDIT);
        AuctionHouseObject* aho = sAuctionMgr.GetAuctionsMap(ahEntry);
        if (!aho)
        {
            sLog.Out(LOG_BASIC, LOG_LVL_ERROR, "AuctionHouseObject is null");
            return;
        }
        std::set<uint32> auctionIDSet;
        auctionIDSet.clear();
        std::map<uint32, AuctionEntry*>* aem = aho->GetAuctions();
        for (std::map<uint32, AuctionEntry*>::iterator aeIT = aem->begin(); aeIT != aem->end(); aeIT++)
        {
            auctionIDSet.insert(aeIT->first);
        }
        for (std::set<uint32>::iterator auctionIDIT = auctionIDSet.begin(); auctionIDIT != auctionIDSet.end(); auctionIDIT++)
        {
            AuctionEntry* eachAE = aho->GetAuction(*auctionIDIT);
            if (eachAE)
            {
                if (eachAE->owner == 0)
                {
                    eachAE->expireTime = time(nullptr) - 1 * TimeConstants::MINUTE;
                    sLog.Out(LOG_BASIC, LOG_LVL_BASIC, "Auction %d removed for auctionhouse %d", eachAE->itemTemplate, ahID);
                }
            }
        }
    }

    sLog.Out(LOG_BASIC, LOG_LVL_BASIC, "Ming cleaned");
}

bool MingManager::UpdateMing(uint32 pDiff)
{
    if (!sMingConfig.Enable)
    {
        return false;
    }
    UpdateSeller(pDiff);
    UpdateBuyer(pDiff);

    return true;
}

bool MingManager::UpdateSeller(uint32 pDiff)
{
    uint32 toSellCount = toSellItemIdSet.size();
    sellerRefillDelay -= pDiff;
    if (sellerRefillDelay < 0)
    {
        if (toSellCount < sMingConfig.SellingItemsMax)
        {
            // fill to sell item
            uint32 sellIndex = urand(0, sellableItemIdMap.size() - 1);
            uint32 sellEntry = sellableItemIdMap[sellIndex];
            toSellItemIdSet.insert(sellEntry);
        }
        else
        {
            sellerRefillDelay = 2 * TimeConstants::HOUR * TimeConstants::IN_MILLISECONDS;
        }
    }
    else
    {
        if (toSellCount > 0)
        {
            uint32 itemEntry = *toSellItemIdSet.begin();
            toSellItemIdSet.erase(itemEntry);
            if (const ItemPrototype* proto = sObjectMgr.GetItemPrototype(itemEntry))
            {
                for (std::set<uint32>::iterator ahIDIT = auctionHouseIDSet.begin(); ahIDIT != auctionHouseIDSet.end(); ahIDIT++)
                {
                    uint32 ahID = *ahIDIT;
                    AuctionHouseEntry const* ahEntry = sAuctionHouseStore.LookupEntry(*ahIDIT);
                    AuctionHouseObject* aho = sAuctionMgr.GetAuctionsMap(ahEntry);
                    if (!aho)
                    {
                        sLog.Out(LOG_BASIC, LOG_LVL_ERROR, "AuctionHouseObject is null");
                        return false;
                    }
                    uint32 stackCount = urand(1, proto->Stackable);
                    uint32 basePrice = 0;
                    if (proto->BuyPrice > 0)
                    {
                        basePrice = proto->BuyPrice;
                    }
                    else if (proto->SellPrice > 0)
                    {
                        basePrice = proto->SellPrice * 4;
                    }
                    else
                    {
                        basePrice = proto->Quality * 10000;
                    }
                    uint32 priceMultiple = urand(2, 5);
                    uint32 finalPrice = basePrice * priceMultiple;
                    if (finalPrice > 100)
                    {
                        if (Item* item = Item::CreateItem(proto->ItemId, stackCount, 0))
                        {
                            if (uint32 randomPropertyId = Item::GenerateItemRandomPropertyId(itemEntry))
                            {
                                item->SetItemRandomProperties(randomPropertyId);
                            }
                            if (finalPrice == 0)
                            {
                                break;
                            }

                            uint32 dep = sAuctionMgr.GetAuctionDeposit(ahEntry, 8 * TimeConstants::HOUR, item);
                            AuctionEntry* auctionEntry = new AuctionEntry;
                            auctionEntry->Id = sObjectMgr.GenerateAuctionID();
                            auctionEntry->auctionHouseEntry = ahEntry;
                            auctionEntry->itemGuidLow = item->GetGUIDLow();
                            auctionEntry->itemTemplate = item->GetEntry();
                            //auctionEntry->owner = mingCharacterId;
                            auctionEntry->owner = 0;
                            auctionEntry->startbid = finalPrice / 2;
                            auctionEntry->buyout = finalPrice;
                            auctionEntry->bidder = 0;
                            auctionEntry->bid = 0;
                            auctionEntry->deposit = dep;
                            auctionEntry->depositTime = time(nullptr);
                            auctionEntry->expireTime = (time_t)(8 * TimeConstants::HOUR) + time(nullptr);
                            item->SaveToDB();
                            sAuctionMgr.AddAItem(item);
                            aho->AddAuction(auctionEntry);
                            auctionEntry->SaveToDB();

                            sLog.Out(LOG_BASIC, LogLevel::LOG_LVL_DETAIL, "Auction %s added for auctionhouse %d", proto->Name1, ahID);
                        }
                    }
                }
            }
        }
    }

    return true;
}

bool MingManager::UpdateBuyer(uint32 pDiff)
{
    buyerRefillDelay -= pDiff;
    if (buyerRefillDelay < 0)
    {
        if (boughtCount < sMingConfig.BuyingItemsMax)
        {
            // fill to buy item 
            for (std::set<uint32>::iterator ahIDIT = auctionHouseIDSet.begin(); ahIDIT != auctionHouseIDSet.end(); ahIDIT++)
            {
                uint32 ahID = *ahIDIT;
                AuctionHouseEntry const* ahEntry = sAuctionHouseStore.LookupEntry(*ahIDIT);
                AuctionHouseObject* aho = sAuctionMgr.GetAuctionsMap(ahEntry);
                if (!aho)
                {
                    sLog.Out(LOG_BASIC, LOG_LVL_ERROR, "AuctionHouseObject is null");
                    return false;
                }
                std::map<uint32, AuctionEntry*>* aem = aho->GetAuctions();
                std::unordered_map<uint32, uint32> eachAHOPlayerAEMap;
                for (std::map<uint32, AuctionEntry*>::iterator aeIT = aem->begin(); aeIT != aem->end(); aeIT++)
                {
                    if (aeIT->second->owner == 0)
                    {
                        continue;
                    }
                    uint32 eachAuctionId = aeIT->first;
                    if (toBuyAuctionIdSet.find(eachAuctionId) != toBuyAuctionIdSet.end())
                    {
                        continue;
                    }

                    float viewPower = frand(0.0f, 1.0f);
                    sLog.Out(LOG_BASIC, LogLevel::LOG_LVL_BASIC, "buyer view check : %d - %f - %f", eachAuctionId, sMingConfig.BuyerViewRate, viewPower);
                    if (viewPower < sMingConfig.BuyerViewRate)
                    {
                        if (Item* checkItem = sAuctionMgr.GetAItem(aeIT->second->itemGuidLow))
                        {
                            if (const ItemPrototype* destIT = checkItem->GetProto())
                            {
                                if (!destIT)
                                {
                                    continue;
                                }
                                if (destIT->Quality < 1)
                                {
                                    continue;
                                }
                                if (destIT->Quality > 4)
                                {
                                    continue;
                                }
                                uint32 basePrice = 0;
                                if (destIT->BuyPrice > 0)
                                {
                                    basePrice = destIT->BuyPrice;
                                }
                                else if (destIT->SellPrice > 0)
                                {
                                    basePrice = destIT->SellPrice * 4;
                                }
                                else
                                {
                                    basePrice = destIT->Quality * 10000;
                                }
                                basePrice = basePrice * checkItem->GetCount();
                                float buyRate = sMingConfig.BuyerBuyRate;
                                if (vendorUnlimitItemSet.find(aeIT->second->itemTemplate) != vendorUnlimitItemSet.end())
                                {
                                    buyRate = buyRate / 2.0f;
                                }
                                if (destIT->Class == ItemClass::ITEM_CLASS_WEAPON || destIT->Class == ItemClass::ITEM_CLASS_ARMOR)
                                {
                                    buyRate = buyRate / 2.0f;
                                }
                                float priceRate = (float)basePrice / (float)aeIT->second->buyout;
                                priceRate = priceRate * priceRate;
                                buyRate = buyRate * priceRate;
                                float buyPower = frand(0.0f, 1.0f);
                                sLog.Out(LOG_BASIC, LogLevel::LOG_LVL_BASIC, "buy check : %s - %f - %f", destIT->Name1, buyRate, buyPower);
                                if (buyPower < buyRate)
                                {
                                    toBuyAuctionIdSet.insert(eachAuctionId);
                                    break;
                                }
                            }
                        }
                    }
                }
            }
            boughtCount++;
        }
        else
        {
            boughtCount = 0;
            buyerRefillDelay = 1 * TimeConstants::HOUR * TimeConstants::IN_MILLISECONDS;
        }
    }
    else
    {
        if (toBuyAuctionIdSet.size() > 0)
        {
            uint32 auctionEntry = *toBuyAuctionIdSet.begin();
            toBuyAuctionIdSet.erase(auctionEntry);
            AuctionEntry* destAE = nullptr;
            for (std::set<uint32>::iterator ahIDIT = auctionHouseIDSet.begin(); ahIDIT != auctionHouseIDSet.end(); ahIDIT++)
            {
                uint32 ahID = *ahIDIT;
                AuctionHouseEntry const* ahEntry = sAuctionHouseStore.LookupEntry(*ahIDIT);
                AuctionHouseObject* aho = sAuctionMgr.GetAuctionsMap(ahEntry);
                destAE = aho->GetAuction(auctionEntry);
                if (destAE)
                {
                    destAE->bid = destAE->buyout;
                    destAE->bidder = sMingConfig.BuyerId;
                    sAuctionMgr.SendAuctionSuccessfulMail(destAE);
                    sAuctionMgr.SendAuctionWonMail(destAE);
                    sAuctionMgr.RemoveAItem(destAE->itemGuidLow);
                    aho->RemoveAuction(destAE);
                    destAE->DeleteFromDB();
                    delete destAE;
                    sLog.Out(LOG_BASIC, LogLevel::LOG_LVL_BASIC, "Auction %d - %d was bought by ming buyer", auctionEntry, destAE->itemTemplate);
                    break;
                }
            }
        }
    }

    return true;
}

void MingManager::ResetSellableItems()
{
    sellableItemIdMap.clear();
    for (const auto& item : sObjectMgr.GetItemPrototypeMap())
    {
        ItemPrototype const* proto = &item.second;
        if (!proto)
        {
            continue;
        }
        if (vendorUnlimitItemSet.find(proto->ItemId) != vendorUnlimitItemSet.end())
        {
            continue;
        }
        if (exceptionEntrySet.find(proto->ItemId) != exceptionEntrySet.end())
        {
            continue;
        }
        if (proto->ItemLevel < 1)
        {
            continue;
        }
        if (proto->Quality < 1)
        {
            continue;
        }
        if (proto->Quality > 4)
        {
            continue;
        }
        if (proto->Bonding == ItemBondingType::BIND_WHEN_PICKED_UP)
        {
            continue;
        }
        bool sellThis = false;
        switch (proto->Class)
        {
        case ItemClass::ITEM_CLASS_CONSUMABLE:
        {
            sellThis = true;
            break;
        }
        case ItemClass::ITEM_CLASS_CONTAINER:
        {
            sellThis = true;
            break;
        }
        case ItemClass::ITEM_CLASS_WEAPON:
        {
            sellThis = true;
            break;
        }
        case ItemClass::ITEM_CLASS_GEM:
        {
            sellThis = true;
            break;
        }
        case ItemClass::ITEM_CLASS_ARMOR:
        {
            if (proto->Quality >= 2)
            {
                sellThis = true;
            }
            break;
        }
        case ItemClass::ITEM_CLASS_REAGENT:
        {
            sellThis = true;
            break;
        }
        case ItemClass::ITEM_CLASS_PROJECTILE:
        {
            if (proto->Quality >= 2)
            {
                sellThis = true;
            }
            break;
        }
        case ItemClass::ITEM_CLASS_TRADE_GOODS:
        {
            sellThis = true;
            break;
        }
        case ItemClass::ITEM_CLASS_GENERIC:
        {
            sellThis = true;
            break;
        }
        case ItemClass::ITEM_CLASS_RECIPE:
        {
            sellThis = true;
            break;
        }
        case ItemClass::ITEM_CLASS_MONEY:
        {
            break;
        }
        case ItemClass::ITEM_CLASS_QUIVER:
        {
            if (proto->Quality >= 2)
            {
                sellThis = true;
            }
            break;
        }
        case ItemClass::ITEM_CLASS_QUEST:
        {
            sellThis = true;
            break;
        }
        case ItemClass::ITEM_CLASS_KEY:
        {
            sellThis = true;
            break;
        }
        case ItemClass::ITEM_CLASS_PERMANENT:
        {
            break;
        }
        case ItemClass::ITEM_CLASS_JUNK:
        {
            if (proto->Quality > 0)
            {
                sellThis = true;
            }
            break;
        }
        default:
        {
            break;
        }
        }
        if (sellThis)
        {
            sellableItemIdMap[sellableItemIdMap.size()] = proto->ItemId;
        }
    }
}

bool MingManager::StringEndWith(const std::string& str, const std::string& tail)
{
    return str.compare(str.size() - tail.size(), tail.size(), tail) == 0;
}

bool MingManager::StringStartWith(const std::string& str, const std::string& head)
{
    return str.compare(0, head.size(), head) == 0;
}

std::vector<std::string> MingManager::SplitString(std::string srcStr, std::string delimStr, bool repeatedCharIgnored)
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

std::string MingManager::TrimString(std::string srcStr)
{
    std::string result = srcStr;
    if (!result.empty())
    {
        result.erase(0, result.find_first_not_of(" "));
        result.erase(result.find_last_not_of(" ") + 1);
    }

    return result;
}
