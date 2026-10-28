/* rgp:protos */
#define RGP_SELF_MenuGridCursorBobCb_2b8090 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Byte-shape clone of already-merged MenuGridCursorBobCb_2b7500 (src/s31a/MenuGridCursorBobCb_2b7500.c),
   found via CENSUS open-vs-CLOSED signature search -- differs only in the
   scratch global used (D_00482544 vs D_00482548) and the two literal
   constants (0x184 vs 0x185; angle 6.0f is shared). */

extern f32 D_0047D3B8 __attribute__((section(".sdata")));
extern f32 D_00482544;
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 MenuGridCursorBobCb_2b8090(s32 p0, s32 p1)
{
    s32 v0;
    s32 v1;
    s32 k;

    PhaseAdvanceWrapPi_28b630(&D_00482544, D_0047D3B8);
    k = (s32)(6.0f * Sinf_128fd0(D_00482544));
    GetGridCellPosOffset_28ecd0(p0, &v0, &v1, k, k);
    UiMoveWidgetUniform_290f50(p1, 0x184, v0, v1, 0.25f, 0);
    return 1;
}
