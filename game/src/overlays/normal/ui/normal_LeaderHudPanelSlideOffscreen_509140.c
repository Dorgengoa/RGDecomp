/* rgp:protos */
#define RGP_SELF_normal_LeaderHudPanelSlideOffscreen_509140 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00509140 -- slide the 0x02 / 0x10 pair of widgets in or out. */

extern f32   D_0047D440;          /* gp - 0x7D30 */
extern f32   D_0047D534;          /* gp - 0x7C3C */
extern void *D_00484564;          /* gp - 0xC0C  */

/*rgp*/
/*rgp*/

s32 normal_LeaderHudPanelSlideOffscreen_509140(s32 a, s32 b, s32 c)
{
    if (a != 0) {
        if (b != 0) {
            UiSetWidgetPos_290f60(D_00484564, 2, -0x100, 0x13);
            UiSetWidgetPos_290f60(D_00484564, 0x10, -0x100, 0x13);
        }
        UiMoveWidgetUniform_290f50(D_00484564, 2, 8, 0x13, D_0047D440, 0);
        UiMoveWidgetUniform_290f50(D_00484564, 0x10, 8, 0x13, D_0047D440, 0);
    } else {
        if (b != 0) {
            UiSetWidgetPos_290f60(D_00484564, 2, 8, 0x13);
            UiSetWidgetPos_290f60(D_00484564, 0x10, 8, 0x13);
        }
        if (c == 0) {
            UiSetWidgetPos_290f60(D_00484564, 2, 0x200, 0x13);
            UiSetWidgetPos_290f60(D_00484564, 0x10, 0x200, 0x13);
        }
        UiMoveWidgetUniform_290f50(D_00484564, 2, -0x100, 0x13, D_0047D534, 0);
        UiMoveWidgetUniform_290f50(D_00484564, 0x10, -0x100, 0x13, D_0047D534, 0);
    }
    return 1;
}
