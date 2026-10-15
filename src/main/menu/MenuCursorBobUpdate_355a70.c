/* MATCH (s41m). Stale pre-match note follows -- PARK improved in main s22 by [[mwcc-const-sdata-load-hoist]] (const +
   .sdata on this unit's READ-ONLY gp float externs): 34 -> 28 bad.  Real progress,
   not a close -- the rest of the residue is a different class. */
#include "types.h"

f32 Sinf_128fd0(f32);                              /* extern */
s32 PhaseAdvanceWrapPi_28b630(f32 *, f32);                         /* extern */
s32 UiMoveWidgetUniform_290f50(s32, s32, s32, s32, s32, f32);             /* extern */
s32 UiSetWidgetPos_290f60(s32, s32, s32, s32);                   /* extern */
extern const f32 D_0047D3B8 __attribute__((section(".sdata")));
extern s32 D_00482360;
extern f32 D_00482F08;

s32 MenuCursorBobUpdate_355a70(u8 *arg0, s32 pd1, s32 arg2, s32 arg3, s32 arg4) {
    s32 temp_6;
    f32 t;
    s32 temp_7;

    PhaseAdvanceWrapPi_28b630(&D_00482F08, D_0047D3B8);
    t = 12.0f * Sinf_128fd0(D_00482F08);
    temp_6 = (s32) ((f32) arg2 + (t + (f32) ((*(s16 *)((u8 *)arg0 + 0x0)) + ((*(s16 *)((u8 *)arg0 + 0x10)) * 0x82))));
    temp_7 = arg3 + ((*(s16 *)((u8 *)arg0 + 0x2)) + ((*(s16 *)((u8 *)arg0 + 0x12)) * (*(s16 *)((u8 *)arg0 + 0x6))));
    if (arg4 != 0) {
        UiSetWidgetPos_290f60(D_00482360, 0x1A6, temp_6, temp_7);
    } else {
        UiMoveWidgetUniform_290f50(D_00482360, 0x1A6, temp_6, temp_7, 0, 0.25f);
    }
    return 1;
}
