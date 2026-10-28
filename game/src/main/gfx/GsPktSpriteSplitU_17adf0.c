/* rgp:protos */
#define RGP_SELF_GsPktSpriteSplitU_17adf0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma divbyzerocheck on

/*rgp*/
/*rgp*/

void GsPktSpriteSplitU_17adf0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8)
{
    s32 dx;
    s32 dy;
    s32 n;
    s32 i;

    dx = arg3 - arg1;
    dy = arg7 - arg5;
    n = dy / 512;
    if (dy % 512 != 0) {
        n++;
    }
    for (i = 0; i < n; i++) {
        GsPktSetUVFixed_13ed90(arg0, arg5 + (i * dy) / n, arg6);
        GsPktSetXYZ_13ef10(arg0, arg1 + (i * dx) / n, arg2, 0);
        GsPktSetUVFixed_13ed90(arg0, arg5 + ((i + 1) * dy) / n, arg8);
        GsPktSetXYZ_13ef10(arg0, arg1 + ((i + 1) * dx) / n, arg4, 0);
    }
}
