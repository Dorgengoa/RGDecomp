#include "types.h"

typedef struct S00482374 {
    u8 pad0[0x1C];
    s8 unk1C;
} S00482374;

extern f32 Sinf_128fd0(f32 arg0);
extern void PhaseAdvanceWrapPi_28b630(f32 *arg0, f32 arg1);
extern void GetGridCellPosOffset_28ecd0(s32 arg0, s32 *arg1, s32 *arg2, s32 arg3, s32 arg4);
extern void UiMoveWidgetUniform_290f50(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, f32 arg5);
extern const f32 D_0047D3B8 __attribute__((section(".sdata")));
extern const f32 D_0047D3F8 __attribute__((section(".sdata")));
extern S00482374 * D_00482374 ;
extern f32 D_004824C8;
extern f32 D_004824D0;

s32 MenuCursorBobToCell_2b3260(s32 arg0, s32 arg1, s32 arg2, s32 arg3)
{
    s32 sp6C;
    s32 sp68;
    s32 sp64;
    s32 sp60;
    f32 f20;
    s32 t;

    PhaseAdvanceWrapPi_28b630(&D_004824C8, D_0047D3B8);
    f20 = 6.0f * Sinf_128fd0(D_004824C8);
    GetGridCellPosOffset_28ecd0(arg0, &sp6C, &sp68, (s32)((f32)arg2 + f20), arg3);
    if (sp68 > 0x14A) {
        sp68 = 0x14A;
    }
    t = (s32)((f32)sp68 + f20);
    if (D_00482374->unk1C) {
        PhaseAdvanceWrapPi_28b630(&D_004824D0, D_0047D3F8);
        f20 = 6.0f * Sinf_128fd0(D_004824D0);
        GetGridCellPosOffset_28ecd0(arg0, &sp64, &sp60, -0x3C, -0x1A);
        UiMoveWidgetUniform_290f50(arg1, 0x7B, sp64, (s32)((f32)sp60 + f20), 0, 0.25f);
        UiMoveWidgetUniform_290f50(arg1, 0x227, sp64 + 0x1E, (s32)(38.0f + ((f32)sp60 + f20)), 0, 0.25f);
    } else {
        UiMoveWidgetUniform_290f50(arg1, 0x227, sp6C, t, 0, 0.25f);
    }
    return 1;
}
