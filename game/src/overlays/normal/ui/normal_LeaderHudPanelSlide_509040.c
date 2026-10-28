/* rgp:protos */
#define RGP_SELF_normal_LeaderHudPanelSlide_509040 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00509040 -- two mirrored arms; the constants 8 and -0xC8 swap
 * places between the func_290F60 pair and the func_290F50 pair.  The gp float
 * at 0x0047D440 is a literal-pool entry, so it is written as 0.3f. */
extern void *D_00484564;          /* gp - 0xC0C */
/*rgp*/
/*rgp*/
extern s32 normal_LeaderHudPanelSlide_509040(s32 a, s32 b);
s32 normal_LeaderHudPanelSlide_509040(s32 a, s32 b)
{
    if (a != 0) {
        if (b != 0) {
            UiSetWidgetPos_290f60(D_00484564, 2, -0xC8, 0x13);
            UiSetWidgetPos_290f60(D_00484564, 0x10, -0xC8, 0x13);
        }
        UiMoveWidgetUniform_290f50(D_00484564, 2, 8, 0x13, 0.3f, 0);
        UiMoveWidgetUniform_290f50(D_00484564, 0x10, 8, 0x13, 0.3f, 0);
    } else {
        if (b != 0) {
            UiSetWidgetPos_290f60(D_00484564, 2, 8, 0x13);
            UiSetWidgetPos_290f60(D_00484564, 0x10, 8, 0x13);
        }
        UiMoveWidgetUniform_290f50(D_00484564, 2, -0xC8, 0x13, 0.3f, 0);
        UiMoveWidgetUniform_290f50(D_00484564, 0x10, -0xC8, 0x13, 0.3f, 0);
    }
    return 1;
}
