/* rgp:protos */
#define RGP_SELF_GetGameModeAt_1f5830 1
#include "port/game_protos.h"
#line 1
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
