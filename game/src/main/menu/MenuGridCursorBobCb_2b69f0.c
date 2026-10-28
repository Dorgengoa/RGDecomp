/* rgp:protos */
#define RGP_SELF_MenuGridCursorBobCb_2b69f0 1
#include "port/game_protos.h"
#line 1
/* MATCH (main s22): [[mwcc-const-sdata-load-hoist]] -- the gp float load
   retail schedules ABOVE the prologue's `sq $sN,K($sp)` stores.  Fires on a
   READ-ONLY extern (the barrier is the $sp stores, not a write), and it is
   PER-EXTERN: const the symbol whose load is misplaced, not every gp float
   the unit reads. */
/* PARK: same length as retail, 4 bad words: a rotate-by-1-word residue
   (verified via objdump) -- retail schedules the D_0047D3B8 lwc1 load
   BEFORE the arg0/arg1 callee-saved register moves in the prologue, ours
   schedules it after. Register-scheduling artifact, not a value/type bug.
   Not re-tried. */
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern f32 D_0047D3B8 __attribute__((section(".sdata")));
extern f32 D_00482544;

s32 MenuGridCursorBobCb_2b69f0(s32 arg0, s32 arg1)
{
    s32 sp3C;
    s32 sp38;

    PhaseAdvanceWrapPi_28b630(&D_00482544, D_0047D3B8);
    GetGridCellPosOffset_28ecd0(arg0, &sp3C, &sp38, (s32) ((8.0f * Sinf_128fd0(D_00482544)) - 14.0f), -4);
    UiMoveWidgetUniform_290f50(arg1, 0x183, sp3C, sp38, 0.25f, 0);
    return 1;
}
