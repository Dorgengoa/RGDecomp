/* rgp:protos */
#define RGP_SELF_MenuGridCursorBobCb_3545a0 1
#include "port/game_protos.h"
#line 1
/* HARD unit: raw asm read to recover a scalar-FPU accumulator sequence
   (adda.s/madd.s) m2c could not decode; UiMoveWidgetUniform_290f50's true arg count past
   the 6th (D_00482360, 0x1A6, computed s32, arg0->unk2+mult, 0, 1.0f-bits
   float) is UNVERIFIED -- m2c guessed 8 params but only 6 could be traced
   to real register/float-register state at the call site. Attempt only,
   not confirmed against a working prototype. */
#include "types.h"
#pragma opt_dead_assignments off

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern f32 D_0047D288;
extern f32 D_0047D3B8 __attribute__((section(".sdata")));
extern s32 D_00482360;
extern f32 D_00482F08;

s32 MenuGridCursorBobCb_3545a0(u8 *arg0) {
    f32 temp_f12;
    f32 temp_f20;
    f32 result;

    PhaseAdvanceWrapPi_28b630(&D_00482F08, D_0047D3B8);
    result = Sinf_128fd0(D_00482F08);
    temp_f20 = (1.0f + result) / 4.0f;
    UiMoveWidgetUniform_290f50(D_00482360, 0x1A6, (s32) ((f32) *(s16 *)(arg0 + 0) + 8.0f * result), *(s16 *)(arg0 + 2) + (*(s16 *)(arg0 + 0x12) * *(s16 *)(arg0 + 6)), 0.25f, 0


);
    temp_f12 = 1.0f + temp_f20;
    UiSetWidgetColor_2905b0(D_00482360, 0xC6, temp_f12, temp_f12, temp_f12, D_0047D288);
    return 1;
}
