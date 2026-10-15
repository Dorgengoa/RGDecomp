#include "types.h"

extern const f32 D_0047D3B8 __attribute__((section(".sdata")));
extern f32 D_0048323C;
extern void *D_00484710;
extern u8 D_004E9230[];

extern void PhaseAdvanceWrapPi_28b630(f32 *p, f32 v);
extern f32  Sinf_128fd0(f32 v);
extern void GetGridCellPosOffset_28ecd0(void *o, s32 *x, s32 *y, s32 n, s32 z);
extern void UiMoveWidgetUniform_290f50(void *p, s32 id, s32 x, s32 y, s32 z, f32 s);
extern void UiSelFrameAnimStep_28d820(u8 *p, s32 n);

s32 MenuGridCursorBobCb_37c070(void *o)
{
    s32 x;
    s32 y;

    PhaseAdvanceWrapPi_28b630(&D_0048323C, D_0047D3B8);
    GetGridCellPosOffset_28ecd0(o, &x, &y, (s32)(8.0f * Sinf_128fd0(D_0048323C)), 0);
    UiMoveWidgetUniform_290f50(D_00484710, 0x762C, x, y, 0, 0.25f);
    UiSelFrameAnimStep_28d820(D_004E9230, 0x7604);
    return 1;
}
