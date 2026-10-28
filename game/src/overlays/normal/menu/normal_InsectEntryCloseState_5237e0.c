/* rgp:protos */
#define RGP_SELF_normal_InsectEntryCloseState_5237e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x005237E0 -- the normal_D_00528180 panel's four-slot (1/3/2/0x11) fade.
 * The SAME four func_290690 calls are written TWICE: unconditionally on the
 * D_004849D0 branch, and behind a `*func_2904B0(...,2) <= 1.0f` test on the
 * other.  The `bnel` delay slot carrying the else-arm's first `lwc1` is the
 * scheduler, not a second statement.
 *
 * No arguments are read; returns 1.  Then the 0x3 slot's own value gates the
 * four func_291110 tear-downs and the two byte flags.
 * normal_D_00528180 lives at 0x00528180 -- far outside gp's window, hence %hi/%lo.
 */

extern u8  normal_D_00528180[];
extern u8  D_004849B8;            /* gp - 0x7B8  */
extern s32 D_004849D0;            /* gp - 0x7A0  */
extern u8  D_004849D8;            /* gp - 0x798  */
extern f32 D_0047D7C8;            /* -0.2  gp - 0x79A8 */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 normal_InsectEntryCloseState_5237e0(void *a, s32 b)
{
    if (D_004849D0 == 0) {
        if (*((f32 *)UiGetWidgetColor_2904b0(normal_D_00528180, 2)) <= 1.0f) {
            UiFadeWidgetAlpha_290690(normal_D_00528180, 1, 0.0f, D_0047D7C8, -1.0f);
            UiFadeWidgetAlpha_290690(normal_D_00528180, 3, 0.0f, D_0047D7C8, -1.0f);
            UiFadeWidgetAlpha_290690(normal_D_00528180, 2, 0.0f, D_0047D7C8, -1.0f);
            UiFadeWidgetAlpha_290690(normal_D_00528180, 0x11, 0.0f, D_0047D7C8, -1.0f);
        }
    } else {
        UiFadeWidgetAlpha_290690(normal_D_00528180, 1, 0.0f, D_0047D7C8, -1.0f);
        UiFadeWidgetAlpha_290690(normal_D_00528180, 3, 0.0f, D_0047D7C8, -1.0f);
        UiFadeWidgetAlpha_290690(normal_D_00528180, 2, 0.0f, D_0047D7C8, -1.0f);
        UiFadeWidgetAlpha_290690(normal_D_00528180, 0x11, 0.0f, D_0047D7C8, -1.0f);
    }
    if (UiGetWidgetAlpha_290770(normal_D_00528180, 3) <= 0.0f) {
        UiSetWidgetsVisibleById_291110(normal_D_00528180, 1, 0, 1);
        UiSetWidgetsVisibleById_291110(normal_D_00528180, 3, 0, 1);
        UiSetWidgetsVisibleById_291110(normal_D_00528180, 2, 0, 1);
        UiSetWidgetsVisibleById_291110(normal_D_00528180, 0x11, 0, 1);
        D_004849B8 = 0;
        D_004849D8 = 0;
    }
    return 1;
}
