#include "types.h"

/* Write the small-data s16 D_004821C2.  The value arrives in $a0: the object pointer most setters here take is absent, so the value IS the first parameter. */

extern s16 D_004821C2;

void GameFlowSetChainTargetId_285f00(s16 value)
{
    D_004821C2 = value;
}
