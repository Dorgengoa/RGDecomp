#include "types.h"

extern f32 Sinf_128fd0(f32 arg0);
extern void PhaseAdvanceWrapPi_28b630(f32 *arg0, f32 arg1);
extern void UiSelFrameAnimStep_28d820(void *arg0, s32 arg1);
extern void GetGridCellPosOffset_28ecd0(s32 arg0, s32 *arg1, s32 *arg2, s32 arg3, s32 arg4);
extern void GetGridCellPos_28ed30(s32 arg0, s32 *arg1, s32 *arg2);
extern void UiMoveWidgetUniform_290f50(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, f32 arg5);
extern const f32 D_0047D3B8 __attribute__((section(".sdata")));
extern const f32 D_0047D3F8 __attribute__((section(".sdata")));
extern f32 D_0048323C;
extern f32 D_00483240;
extern const void * D_00484740 __attribute__((section(".sdata")));
extern u8 D_004E9230[0x400];

s32 MenuGridCursorBobCb_37f6d0(s32 arg0, s32 arg1)
{
    s32 sp4C;
    s32 sp48;
    s32 sp44;
    s32 sp40;
    f32 temp_f20;
    f32 temp_f20_2;
    s32 t;

    PhaseAdvanceWrapPi_28b630(&D_0048323C, D_0047D3B8);
    temp_f20 = 6.0f * Sinf_128fd0(D_0048323C);
    GetGridCellPosOffset_28ecd0(arg0, &sp4C, &sp48, (s32)temp_f20, 0);
    if (sp48 > 0x100) {
        sp48 = 0x100;
    }
    t = (s32)((f32)sp48 + temp_f20);
    if (*(s8 *)((u8 *)D_00484740 + 0x1C) != 0) {
        PhaseAdvanceWrapPi_28b630(&D_00483240, D_0047D3F8);
        temp_f20_2 = 6.0f * Sinf_128fd0(D_00483240);
        GetGridCellPos_28ed30(arg0, &sp44, &sp40);
        UiMoveWidgetUniform_290f50(arg1, 0x7607, sp44 + 0x33, (s32)((f32)(sp40 + 0x11) + temp_f20_2), 0, 0.25f);
        UiMoveWidgetUniform_290f50(arg1, 0x7632, sp44 - 0x11, (s32)(-56.0f + (38.0f + ((f32)sp40 + temp_f20_2))), 0, 0.25f);
    } else {
        UiMoveWidgetUniform_290f50(arg1, 0x7632, sp4C, t, 0, 0.25f);
    }
    UiSelFrameAnimStep_28d820(&(*(u8 *)D_004E9230), 0x7604);
    return 1;
}
