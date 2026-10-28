/* rgp:protos */
#define RGP_SELF_GetGameReqHold_1f5870 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Read the small-data u8 D_004819A8. */

extern u8 D_004819A8;

u8 GetGameReqHold_1f5870(void)
{
    return D_004819A8;
}
