/* rgp:protos */
#define RGP_SELF_MenuItemCmdPopupPlaceMaybe_2a4620 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
extern s16 D_00450DD2[];
extern f32 D_0047D76C;

s32 MenuItemCmdPopupPlaceMaybe_2a4620(s32 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7)
{
    s32 v2;
    s32 v7;
    s32 x;
    s32 y;

    UiSetWidgetsVisibleById_291110(*arg0, arg1, 1, 1);
    UiFadeWidgetAlpha_290690(*arg0, arg1, 1.0f, D_0047D76C, -1.0f);
    UiSetWidgetsVisibleById_291110(*arg0, arg2, 1, 1);
    UiFadeWidgetAlpha_290690(*arg0, arg2, 1.0f, D_0047D76C, -1.0f);
    if (arg6 == 4) {
        v2 = -D_00450DD2[arg6 * 2];
    } else {
        v2 = 10 - D_00450DD2[arg6 * 2];
    }
    v2 = arg3 < 6 ? 0x58 : v2;
    if (arg4 < 2) {
        v7 = 0x18;
    } else if (arg4 == 2) {
        v7 = 0x44 - (arg5 - 1) * 0x1B;
    } else {
        v7 = 0x44 - arg5 * 0x1B;
    }
    if (arg4 == 0 && arg6 == 5) {
        v7 += 0x14;
    } else if (arg4 == 4) {
        v7 -= arg7;
    }
    x = v2 + arg3 * 0x2A;
    y = v7 + arg4 * 0x32;
    UiSetWidgetPos_290f60(*arg0, arg1, x, y);
    UiSetWidgetPos_290f60(*arg0, arg2, (s32)(98.0f + (f32)x), (s32)(73.0f + (f32)y));
    return 1;
}
