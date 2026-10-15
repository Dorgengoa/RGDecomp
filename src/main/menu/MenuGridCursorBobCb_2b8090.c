#include "types.h"

/* Byte-shape clone of already-merged MenuGridCursorBobCb_2b7500 (src/s31a/MenuGridCursorBobCb_2b7500.c),
   found via CENSUS open-vs-CLOSED signature search -- differs only in the
   scratch global used (D_00482544 vs D_00482548) and the two literal
   constants (0x184 vs 0x185; angle 6.0f is shared). */

extern const f32 D_0047D3B8 __attribute__((section(".sdata")));
extern f32 D_00482544;
extern void PhaseAdvanceWrapPi_28b630(void *p, f32 x);
extern f32 Sinf_128fd0(f32 x);
extern void GetGridCellPosOffset_28ecd0(s32 a, s32 *b, s32 *c, s32 d, s32 e);
extern void UiMoveWidgetUniform_290f50(s32 a, s32 b, s32 c, s32 d, s32 e, f32 f);

s32 MenuGridCursorBobCb_2b8090(s32 p0, s32 p1)
{
    s32 v0;
    s32 v1;
    s32 k;

    PhaseAdvanceWrapPi_28b630(&D_00482544, D_0047D3B8);
    k = (s32)(6.0f * Sinf_128fd0(D_00482544));
    GetGridCellPosOffset_28ecd0(p0, &v0, &v1, k, k);
    UiMoveWidgetUniform_290f50(p1, 0x184, v0, v1, 0, 0.25f);
    return 1;
}
