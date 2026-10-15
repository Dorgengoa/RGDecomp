#include "types.h"

extern const f32 D_0047D3B8 __attribute__((section(".sdata")));
extern f32 D_004824C8;
extern void *D_00482360;

extern void PhaseAdvanceWrapPi_28b630(f32 *p, f32 t);
extern f32 Sinf_128fd0(f32 x);
extern void GetGridCellPosOffset_28ecd0(void *a, s32 *b, s32 *c, s32 d, s32 e);
extern void UiMoveWidgetUniform_290f50(void *a, s32 id, s32 x, s32 y, s32 z, f32 t);

s32 MenuGridCursorBobCb_2a76b0(void *a0)
{
    s32 x;
    s32 y;

    PhaseAdvanceWrapPi_28b630(&D_004824C8, D_0047D3B8);
    GetGridCellPosOffset_28ecd0(a0, &x, &y, (s32)(6.0f * Sinf_128fd0(D_004824C8)), 0);
    UiMoveWidgetUniform_290f50(D_00482360, 0x146, x, y, 0, 0.25f);
    return 1;
}
