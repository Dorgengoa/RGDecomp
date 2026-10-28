/* rgp:protos */
#define RGP_SELF_MesItemCodeFromIndex_2772b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern s32 D_0044EBCC[];

s32 MesItemCodeFromIndex_2772b0(s32 i)
{
    if (i <= 0) goto zero;
    if (i <= 16) goto ok;
zero:
    return 0;
ok:
    return D_0044EBCC[i] + 0xFB00;
}
