/* rgp:protos */
#define RGP_SELF_MenuCursorBobToCell_2b0170 1
#include "port/game_protos.h"
#line 1
/* MATCH (main s22): [[mwcc-const-sdata-load-hoist]] -- the gp float load
   retail schedules ABOVE the prologue's `sq $sN,K($sp)` stores.  Fires on a
   READ-ONLY extern (the barrier is the $sp stores, not a write), and it is
   PER-EXTERN: const the symbol whose load is misplaced, not every gp float
   the unit reads. */
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern f32 D_0047D3B8 __attribute__((section(".sdata")));
extern s32 D_00482360;
extern f32 D_004824C8;

s32 MenuCursorBobToCell_2b0170(s32 arg0, s32 arg1, s32 arg2) {
    s32 sp4C;
    s32 sp48;
    f32 temp_f2;

    PhaseAdvanceWrapPi_28b630(&D_004824C8, D_0047D3B8);
    temp_f2 = 6.0f * Sinf_128fd0(D_004824C8);
    GetGridCellPosOffset_28ecd0(arg0, &sp4C, &sp48, (s32)((f32)arg1 + temp_f2), (s32)((f32)arg2 + temp_f2));
    UiMoveWidgetUniform_290f50(D_00482360, 0x227, sp4C, sp48, 0.25f, 0);
    return 1;
}
