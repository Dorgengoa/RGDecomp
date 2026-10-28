/* rgp:protos */
#define RGP_SELF_ClearGameReqHold_1f5880 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Zero the small-data u8 D_004819A8. */

extern u8 D_004819A8;

void ClearGameReqHold_1f5880(void)
{
    D_004819A8 = 0;
}
