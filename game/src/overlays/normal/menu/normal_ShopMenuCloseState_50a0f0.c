/* rgp:protos */
#define RGP_SELF_normal_ShopMenuCloseState_50a0f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x0050A0F0 -- the 0x30-widget phase handler on the STATIC overlay
 * object normal_D_00527C40 (same f(void *, s32) family as normal_FUN_0050F960:
 * `$4` never read, guard on `b`, every path returns 1).
 *
 * The two `sh` stores sit ahead of / inside func_1FEDE0's delay slot, so both
 * gp stores precede the call in source.  func_2910A0 fills the two stack
 * s32s at sp+0x1C / sp+0x18 (mwcc allocates locals in REVERSE declaration
 * order, so the one read back is declared first).  `slti $1, $2, -0x49`
 * writes $at, so the source token is `< -0x49` ([[at-compare-class]]).
 * The tail `mtc1 $0,$f1 / c.le.s $f0,$f1 / bc1fl` is a plain `<= 0.0f`.
 */

extern u8 normal_D_00527C40[];

extern f32   D_0047D4D0;          /* gp - 0x7CA0 */
extern s16   D_00480638;          /* gp - 0x4B38 */
extern u8    D_004845D8;          /* gp - 0xB98  */
extern s16   D_0048460C;          /* gp - 0xB64  */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 normal_ShopMenuCloseState_50a0f0(void *a, s32 b)
{
    s32 x;
    s32 y;

    if (b != 0) {
        D_0048460C = 0;
        D_00480638 = 2;
        GetGameData_1fede0();
        EventCondRefreshAllMaybe_1fe4f0();
        normal_ShopMenuTopRowsSlideOut_50a1c0();
        UiFadeWidgetAlpha_290690(normal_D_00527C40, 0x30, 0.0f, D_0047D4D0, -1.0f);
    }
    UiGetWidgetPos_2910a0(normal_D_00527C40, 9, &x, &y);
    if (x < -0x49 && D_0048460C == 0) {
        normal_ShopMenuFrameFadeOut_50a2f0();
        D_0048460C = 1;
    }
    if (UiGetWidgetAlpha_290770(normal_D_00527C40, 1) <= 0.0f) {
        D_004845D8 = 0;
    }
    return 1;
}
