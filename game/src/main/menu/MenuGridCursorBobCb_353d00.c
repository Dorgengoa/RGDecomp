/* rgp:protos */
#define RGP_SELF_MenuGridCursorBobCb_353d00 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
extern f32 D_0047D3B8 __attribute__((section(".sdata")));
extern s32 D_00482360;
extern f32 D_00482F08;

s32 MenuGridCursorBobCb_353d00(s16 *arg0) {
    f32 t;

    PhaseAdvanceWrapPi_28b630(&D_00482F08, D_0047D3B8);
    t = 8.0f * Sinf_128fd0(D_00482F08);
    UiMoveWidgetUniform_290f50(D_00482360, 0x1A6, (s32)((f32)arg0[0] + t), arg0[1] + arg0[9] * arg0[3], 0.25f, 0);
    return 1;
}
