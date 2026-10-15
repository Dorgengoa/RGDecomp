#include "types.h"

/* clone group cg06-004: seed a gp float, run it through a converter, scale by
   a literal and truncate, hand the result plus two out-parameters to the
   emitter, then re-read the out-parameters for the second emitter.  Members
   differ only in the scale literal and the id. */

extern const f32 D_0047D3B8 __attribute__((section(".sdata")));
extern f32 D_004824C8;
extern void *D_00482360;

extern void PhaseAdvanceWrapPi_28b630(f32 *out, f32 v);
extern f32 Sinf_128fd0(f32 v);
extern void GetGridCellPosOffset_28ecd0(void *a, s32 *px, s32 *py, s32 n, s32 e);
extern void UiMoveWidgetUniform_290f50(void *a, s32 id, s32 x, s32 y, s32 e, f32 t);

s32 MenuGridCursorBobCb_2a8fa0(void *a)
{
    s32 x;
    s32 y;

    PhaseAdvanceWrapPi_28b630(&D_004824C8, D_0047D3B8);
    GetGridCellPosOffset_28ecd0(a, &x, &y, (s32)(6.0f * Sinf_128fd0(D_004824C8)), 0);
    UiMoveWidgetUniform_290f50(D_00482360, 0x227, x, y, 0, 0.25f);
    return 1;
}
