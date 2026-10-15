#include "types.h"

extern s32 D_004B51A0[];

s32 GetGameModeAt_1f5830(s32 p0)
{
    if (p0 >= 0) {
        if (p0 < 0x10) {
            goto ok;
        }
    }
    return 1;
ok:
    return D_004B51A0[p0];
}
