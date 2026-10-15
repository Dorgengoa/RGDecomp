#include "types.h"

/* Address of the small-data object D_004821E0.  Declared as the 4-byte scalar the %gp_rel addressing requires; the real object behind it may be wider. */

extern s32 D_004821E0;

void *GameReqGetWarpArgs_285f80(void)
{
    return &D_004821E0;
}
