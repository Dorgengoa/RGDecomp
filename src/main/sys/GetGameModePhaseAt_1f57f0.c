#include "types.h"

extern s32 D_004B51E0[];

s32 GetGameModePhaseAt_1f57f0(s32 p0)
{
    if (p0 < 0) {
        goto fail;
    }
    if (p0 < 0x10) {
        goto ok;
    }
fail:
    return -1;
ok:
    return D_004B51E0[p0];
}
