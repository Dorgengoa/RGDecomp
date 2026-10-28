/* rgp:protos */
#define RGP_SELF_MenuGridCursorBobCb_2af590 1
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

typedef struct {
    u8 pad0[0x12];
    s16 unk12;
} Obj002AF590;

/*rgp*/                              /* extern */
/*rgp*/                      /* extern */
/*rgp*/ /* extern */
/*rgp*/    /* extern */
extern f32 D_0047D3B8 __attribute__((section(".sdata")));
extern s32 D_00482360;
extern f32 D_004824C8;

s32 MenuGridCursorBobCb_2af590(Obj002AF590 *arg0) {
    s32 sp2C;
    s32 sp28;
    f32 temp_f1;

    PhaseAdvanceWrapPi_28b630(&D_004824C8, D_0047D3B8);
    temp_f1 = 6.0f * Sinf_128fd0(D_004824C8);
    GetGridCellPosOffset_28ecd0(arg0, &sp2C, &sp28, (s32) (98.0f + temp_f1), (s32) (73.0f + temp_f1));
    if (arg0->unk12 == 0) {
        sp2C += 0x32;
    }
    UiMoveWidgetUniform_290f50(D_00482360, 0x227, sp2C, sp28, 0.25f, 0);
    return 1;
}
