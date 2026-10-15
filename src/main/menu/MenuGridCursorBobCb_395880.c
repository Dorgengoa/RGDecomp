#include "types.h"

extern f32 Sinf_128fd0(f32 arg0);
extern void GetGridCellPosOffset_28ecd0(s32 arg0, s32 *arg1, s32 *arg2, s32 arg3, s32 arg4);
extern void UiMoveWidgetUniform_290f50(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, f32 arg5);
extern const f32 D_0047D1FC __attribute__((section(".sdata")));
extern const f32 D_0047D3D0 __attribute__((section(".sdata")));
extern f32 D_00483510;
extern u8 D_004E95C0[0x400];

s32 MenuGridCursorBobCb_395880(s32 arg0)
{
    s32 sp2C;
    s32 sp28;
    f32 temp_f1;

    temp_f1 = D_00483510 + D_0047D3D0;
    D_00483510 = temp_f1;
    if (!(temp_f1 <= 0.0f)) {
        D_00483510 = temp_f1 - D_0047D1FC;
    }
    GetGridCellPosOffset_28ecd0(arg0, &sp2C, &sp28, (s32)(6.0f * Sinf_128fd0(D_00483510)), 0);
    UiMoveWidgetUniform_290f50(&(*(u8 *)D_004E95C0), 0x7546, sp2C, sp28, 0, 0.5f);
    return 1;
}
