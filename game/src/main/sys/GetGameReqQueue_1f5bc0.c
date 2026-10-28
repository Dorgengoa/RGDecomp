/* rgp:protos */
#define RGP_SELF_GetGameReqQueue_1f5bc0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Address of the small-data object D_004819A0.  Declared as the 4-byte scalar the %gp_rel addressing requires; the real object behind it may be wider. */

extern s32 D_004819A0;

void *GetGameReqQueue_1f5bc0(void)
{
    return &D_004819A0;
}
