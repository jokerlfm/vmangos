#include "Nier_Warlock.h"

Nier_Warlock::Nier_Warlock(Player* pmMe) :Nier_Base(pmMe)
{
    curseType = WarlockCurseType::WarlockCurseType_Weakness;
    curseDelay = 0;
    manaCheckDelay = 0;
    soulstoneDelay = 0;
    soulLinkDelay = 0;
    felArmorDelay = 0;
    wardDelay = 0;
    summonDelay = 0;
    soulHarvestDelay = 0;
    soulburnDelay = 0;
    soulFireDelay = 0;
    soulshatterDelay = 0;
    shadowfuryDelay = 0;
    conflagrateDelay = 0;
    immolateDelay = 0;
    shadowburnDelay = 0;
    chaosBoltDelay = 0;
    baneOfHavocDelay = 0;
    empoweredImpDelay = 0;
}
