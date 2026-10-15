#include "types.h"

/* Zero the small-data u8 D_004819A8. */

extern u8 D_004819A8;

void ClearGameReqHold_1f5880(void)
{
    D_004819A8 = 0;
}
