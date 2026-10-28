/* rgp:protos */
#define RGP_SELF_normal_BtlChgMenuItemListScrollState_4ff5c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x004FF5C0 -- reads widget 0x23's origin and, when the Y component is
 * exactly +/-0x32, re-anchors it to 0,0 and posts 0x55FA.  Out-params at
 * sp+0x1C / sp+0x18, so `x` (0x1C) is declared FIRST; only `y` is read.
 * The `beql`/`bne` pair against 0x32 and -0x32 is a two-arm `||`. */

extern u8 normal_D_005278E0;

extern void *D_00484498;          /* gp - 0xCD8 */
extern void *D_0048449C;          /* gp - 0xCD4 */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 normal_BtlChgMenuItemListScrollState_4ff5c0(void *a, s32 b)
{
    s32 x;
    s32 y;

    UiGetWidgetPos_2910a0(D_0048449C, 0x23, &x, &y);
    if ((y == 0x32) || (y == -0x32)) {
        UiSetWidgetPos_290f60(D_0048449C, 0x23, 0, 0);
        StateMachineSetState_28ede0(D_00484498, 0x55FA, 0);
    }
    UiSelFrameAnimStep_28d820(&normal_D_005278E0, 0x28);
    return 1;
}
