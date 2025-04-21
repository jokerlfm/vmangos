#include "NierActionTarget.h"

NierActionTarget::NierActionTarget()
{
    duration = 0;
    timeLimit = 0;
    targetUnit = nullptr;
}

void NierActionTarget::Reset()
{
    duration = 0;
    timeLimit = 0;
    targetUnit = nullptr;    
}