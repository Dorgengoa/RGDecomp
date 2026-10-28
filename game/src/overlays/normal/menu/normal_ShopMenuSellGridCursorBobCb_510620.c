/* rgp:protos */
#define RGP_SELF_normal_ShopMenuSellGridCursorBobCb_510620 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00510620 -- same func_28B630 / func_128FD0 scale as 0x005097E0,
 * feeding a two-out-parameter measure whose second result is clamped to 0x100.
 * The two stack locals are declared in the order that puts the first at the
 * HIGHER offset (mwcc allocates locals in reverse declaration order). */
extern f32 D_00484678;                /* gp - 0xAF8  */
extern u8 normal_D_00527E70[];

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 normal_ShopMenuSellGridCursorBobCb_510620(void *p, void *w)
{
    s32 vx;
    s32 vy;
    f32 t;

    PhaseAdvanceWrapPi_28b630(&D_00484678, 0.07853981853f);
    t = 6.0f * Sinf_128fd0(D_00484678);
    GetGridCellPosOffset_28ecd0(p, &vx, &vy, (s32)t, 0);
    if (vy > 0x100) {
        vy = 0x100;
    }
    UiMoveWidgetUniform_290f50(w, 0x40, vx, (s32)((f32)vy + t), 0.25f, 0);
    UiSelFrameAnimStep_28d820(normal_D_00527E70, 0x3F);
    return 1;
}
