/* rgp:protos */
#define RGP_SELF_MenuGridCursorBobCb_34fba0 1
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
extern f32 D_0047D3B8 __attribute__((section(".sdata")));
extern s32 D_00482360;
extern f32 D_00482EB0;

s32 MenuGridCursorBobCb_34fba0(s32 arg0) {
    s32 sp2C;
    s32 sp28;
    s32 t;
    f32 v;

    v = D_0047D3B8;
    PhaseAdvanceWrapPi_28b630(&D_00482EB0, v);
    t = (s32)(6.0f * Sinf_128fd0(D_00482EB0));
    GetGridCellPosOffset_28ecd0(arg0, &sp2C, &sp28, t, t);
    UiMoveWidgetUniform_290f50(D_00482360, 0x1CB, sp2C, sp28, 0.25f, 0);
    return 1;
}
