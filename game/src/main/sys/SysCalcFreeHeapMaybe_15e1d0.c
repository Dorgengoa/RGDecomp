/* rgp:protos */
#define RGP_SELF_SysCalcFreeHeapMaybe_15e1d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_common_subs off
/*rgp*/
/*rgp*/
extern u8 D_00030000[];
extern u8 D_00528200[];

s32 SysCalcFreeHeapMaybe_15e1d0(void)
{
    s32 a;
    s32 t;

    a = -0x2000 - (s32)D_00030000 - (s32)D_00528200;
    t = a + 0x2000000;
    Free_130e30(((s32)Malloc_130dd8(t - 0x10)));
    Free_130e30(((s32)Malloc_130dd8(0x01900000)));
    return t - 0x10;
}
