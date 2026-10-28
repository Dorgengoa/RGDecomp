/* rgp:protos */
#define RGP_SELF_EffTexUvParamSetCellSize_198a50 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma optimization_level 3

extern f32 D_0047D3E8 __attribute__((section(".sdata")));
void EffTexUvParamSetCellSize_198a50(void *arg0, f32 fparg0, f32 fparg1) {
    if (fparg0 <= D_0047D3E8 || !(fparg0 <= 1.0f)) return;
    if (fparg1 <= D_0047D3E8 || !(fparg1 <= 1.0f)) return;
    *(f32 *)(0x8 + (u8 *)arg0) = fparg0;
    *(f32 *)((u8 *)arg0 + 0xC) = fparg1;
    *(s32 *)((u8 *)arg0 + 0x10) = (s32)(D_0047D3E8 + (1.0f / fparg0));
    *(s32 *)((u8 *)arg0 + 0x14) = (s32)(D_0047D3E8 + (1.0f / fparg1));
}
