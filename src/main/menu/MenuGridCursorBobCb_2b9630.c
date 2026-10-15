#include "types.h"

struct Obj0;
struct Obj1;

extern const f32 D_0047D3B8 __attribute__((section(".sdata")));
extern f32 D_00482544;
extern f32 PhaseAdvanceWrapPi_28b630(struct Obj0 *p0, f32 fa0);
extern f32 Sinf_128fd0(f32 x);
extern void GetGridCellPosOffset_28ecd0(s32 p0, struct Obj0 *p1, struct Obj1 *p2, s32 p3, s32 p4);
extern void UiMoveWidgetUniform_290f50(s32 p0, s32 p1, s32 p2, s32 p3, s32 p4, f32 fa0);

s32 MenuGridCursorBobCb_2b9630(s32 p0, s32 p1)
{
    s32 v0;
    s32 v1;

    PhaseAdvanceWrapPi_28b630((struct Obj0 *)&D_00482544, D_0047D3B8);
    GetGridCellPosOffset_28ecd0(p0, (struct Obj0 *)&v0, (struct Obj1 *)&v1, (s32)(8.0f * Sinf_128fd0(D_00482544)), 0);
    UiMoveWidgetUniform_290f50(p1, 0x183, v0, v1, 0, 0.25f);
    return 1;
}
