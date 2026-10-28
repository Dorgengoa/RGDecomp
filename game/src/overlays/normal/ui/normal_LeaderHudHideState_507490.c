/* rgp:protos */
#define RGP_SELF_normal_LeaderHudHideState_507490 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00507490 -- a pure CALL LIST: f(void *, s32), `$4` never read,
 * guard on `b`, returns 1.  Eight `jal` in 42 words.
 *
 * The guard chains normal_FUN_00506AC0's result straight into
 * normal_FUN_00507E90 (`lw $4` sits in the first call's delay slot), then a
 * fixed normal_LeaderHudPanelSlideOffscreen_509140(0,0,1), then func_290690 with 0.0f / 0.0625f
 * (`lui 0x3D80` inline) / 1.0f.
 *
 * The tail is a NESTED pair of func_2899B0 tests -- both `beq*` jump to the
 * SHARED epilogue and retail falls through into the body, so they are nested
 * ifs, not early returns.  `addiu $7,$0,-1` is the fourth argument of
 * func_290010.
 */

extern void *D_00484564;          /* gp - 0xC0C */
extern void *D_0048456C;          /* gp - 0xC04 */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 normal_LeaderHudHideState_507490(void *a, s32 b)
{
    if (b != 0) {
        normal_LeaderHudBannerSlideEdge_507e90(normal_LeaderHudGetBannerWidth_506ac0(D_0048456C), 0, 0);
        normal_LeaderHudPanelSlideOffscreen_509140(0, 0, 1);
        UiFadeWidgetAlpha_290690(D_00484564, 1, 0.0f, 0.0625f, 1.0f);
    }
    if (UiPageWidgetAtTargetPos_2899b0(D_0048456C, 7) != 0) {
        if (UiPageWidgetAtTargetPos_2899b0(D_0048456C, 2) != 0) {
            normal_LeaderHudDeactivate_506d70(D_0048456C);
            UiSetWidgetVisible_290010(D_00484564, 1, 0, -1);
        }
    }
    return 1;
}
