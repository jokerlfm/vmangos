#ifndef NIER_ACTION_TARGET_H
#define NIER_ACTION_TARGET_H

#include "Unit.h"

class NierActionTarget
{
public:
    NierActionTarget();
    void Reset();

public:
    uint32 duration;
    uint32 timeLimit;

    Unit* targetUnit;
    Position targetPos;
};
#endif
