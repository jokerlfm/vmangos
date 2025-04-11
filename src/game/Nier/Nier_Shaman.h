#ifndef NIER_ACTION_SHAMAN_H
#define NIER_ACTION_SHAMAN_H

#include "Nier_Base.h"

enum ShamanEarthTotemType :uint32
{
    ShamanEarthTotemType_EarthbindTotem = 0,
    ShamanEarthTotemType_StoneskinTotem,
    ShamanEarthTotemType_StoneclawTotem,
    ShamanEarthTotemType_StrengthOfEarthTotem
};

class Nier_Shaman :public Nier_Base
{
public:
    Nier_Shaman();
    void Prepare();

    uint32 earthTotemType;
};
#endif
