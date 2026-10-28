/* rgp:protos */
#define RGP_SELF_TransMenuItemGridCloseState_37f870 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x0051F410 */

extern void *D_00484710;          /* gp - 0xA60 */
extern void *D_0048470C;          /* gp - 0xA64 */
extern s8    D_0048472C;          /* gp - 0xA44 */
extern s32   D_0048324C;          /* gp - 0x8AC */
extern f32   D_0047D4B0;          /* gp - 0x7CC0, 0.08f  */
extern f32   D_0047D9C0;          /* gp - 0x77B0, -0.1f  */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

extern void *D_00484740;
extern f32 D_0047D5D0,D_0047D998;
/*rgp*/
/*rgp*/
/*rgp*/
s32 TransMenuItemGridCloseState_37f870(void *a, s32 b)
{
    s32 x;
    s32 y;
    s32 x2;
    s32 y2;
 u8 data[0x10] __attribute__((aligned(16)));

    if (b != 0) {
 TransMenuItemFetchWidgetRefs_37bdb0(data);
 MenuItemInfoPopupShow_2a33e0(D_00484740,0,0x762E,0x762D,data,0x68,0x15E,-1,D_0047D5D0);
        UiMoveWidget_290e00(D_00484710, 0x75F8, 0x200, 0x49, 3, D_0047D4B0, 0.0f);
        UiFadeWidgetAlpha_290690(D_00484710, 0x75F8, 0.0f, -0.0625f, 1.0f);
        UiSetWidgetsVisibleById_291110(D_00484710,0x7600,0,1);
        D_0048324C = 0;
    }
    TransMenuItemCloseSlideStep_37f9f0();
    UiGetWidgetPos_2910a0(D_00484710, 0x753E, &x, &y);
    if (x == -0x12) {
        if (y == 0xC) {
            UiSetWidgetPos_290f60(D_00484710, 0x753E, -0x4A, 0xC1);
            UiSetWidgetPos_290f60(D_00484710, 0x7539, -0x45, 0xC5);
        }
    }
    if (D_0048324C == 4) {
        UiGetWidgetPos_2910a0(D_00484710, 0x753E, &x2, &y2);
        if (x2 == -0x4A) {
            D_0048472C = 1;
 UiFadeWidgetAlpha_290690(D_00484710,0x75D1,1.0f,D_0047D998,-1.0f);
            StateMachineSetState_28ede0(D_0048470C, 3, 0);
        }
        func_517CF0();
    }
    return 1;
}
