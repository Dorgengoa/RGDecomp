/* rgp:protos */
#define RGP_SELF_MenuGridCursorBobCb_346910 1
#include "port/game_protos.h"
#line 1
/* MATCH (main s22): the gp `lwc1 $f12, D_0047D3B8` that retail schedules
   BEFORE the prologue's stack store is the load-hoist lever
   [[mwcc-const-sdata-load-hoist]] -- and it fires on a READ-ONLY extern
   here, contra that note's "read/write only" caveat: the alias barrier
   being removed is the PROLOGUE's $sp stores, not a write to the symbol.
   `const` alone is +1 word (lui-addressed); the `.sdata` attribute alone
   is byte-identical to base.  Both halves are load-bearing. */
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

extern f32 D_0047D3B8 __attribute__((section(".sdata")));
extern s32 D_00482360;
extern f32 D_00482E3C;
extern u8 D_004DB430[];

s32 MenuGridCursorBobCb_346910(s32 arg0)
{
    s32 sp2C;
    s32 sp28;
    f32 temp_f1;

    PhaseAdvanceWrapPi_28b630(&D_00482E3C, D_0047D3B8);
    temp_f1 = 6.0f * Sinf_128fd0(D_00482E3C);
    GetGridCellPosOffset_28ecd0(arg0, &sp2C, &sp28, (s32) (temp_f1 - 18.0f), (s32) (24.0f + temp_f1));
    UiMoveWidgetUniform_290f50(D_00482360, 0x227, sp2C, sp28, 0.25f, 0);
    UiSelFrameAnimStep_28d820(D_004DB430, 0x78);
    return 1;
}
