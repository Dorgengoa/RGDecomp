#include "types.h"

/* Write the small-data s32 D_004821C8.  The value arrives in $a0: the object pointer most setters here take is absent, so the value IS the first parameter. */

extern s32 D_004821C8;

void GameFlowSetChainTargetKind_285ef0(s32 value)
{
    D_004821C8 = value;
}
