/* MATCH (main s22): the gp `lwc1 $f12, D_0047D3B8` that retail schedules
   BEFORE the prologue's stack store is the load-hoist lever
   [[mwcc-const-sdata-load-hoist]] -- and it fires on a READ-ONLY extern
   here, contra that note's "read/write only" caveat: the alias barrier
   being removed is the PROLOGUE's $sp stores, not a write to the symbol.
   `const` alone is +1 word (lui-addressed); the `.sdata` attribute alone
   is byte-identical to base.  Both halves are load-bearing. */
#include "types.h"

#pragma usefloatacc off

extern f32 Sinf_128fd0(f32);
extern void PhaseAdvanceWrapPi_28b630(f32 *, f32);
extern void UiMoveWidgetUniform_290f50(s32, s32, s32, s32, s32, f32);
extern const f32 D_0047D3B8 __attribute__((section(".sdata")));
extern s32 D_00482360;
extern f32 D_004824C8;
extern s8 D_004824CC;

s32 MenuCursorBobUpdate_2a9c00(void)
{
    f32 product;
    f32 castExpr;

    PhaseAdvanceWrapPi_28b630(&D_004824C8, D_0047D3B8);
    product = 8.0f * Sinf_128fd0(D_004824C8);
    castExpr = (f32)(D_004824CC * 0x50 + 0x52);
    UiMoveWidgetUniform_290f50(D_00482360, 0xAB, (s32)(product + castExpr), 0x88, 0, 0.25f);
    return 1;
}
