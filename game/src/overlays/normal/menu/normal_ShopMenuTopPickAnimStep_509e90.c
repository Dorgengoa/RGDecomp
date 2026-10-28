/* rgp:protos */
#define RGP_SELF_normal_ShopMenuTopPickAnimStep_509e90 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00509E90 -- the shop camera's 7-state fade/zoom machine, dispatched
 * off the s16 phase at gp-0xB70 through normal_jtbl_005264E0.  The alpha at gp-0xB68
 * ramps between 1.0f and 1.9f; state 4 waits for the widget's y to fall below
 * -30 before dropping straight to the last state. */

extern s16 D_00484600;            /* gp - 0xB70  */
extern s16 D_00484604;            /* gp - 0xB6C  */
extern f32 D_00484608;            /* gp - 0xB68  */
extern f32 D_0047D4C8;            /* gp - 0x7CA8 */
extern f32 D_0047D35C;            /* gp - 0x7E14 */
extern f32 D_0047D440;            /* gp - 0x7D30 */
extern f32 D_0047D4E0;            /* gp - 0x7C90 */
extern f32 D_0047D280;            /* gp - 0x7EF0 */

extern u8 normal_D_00527C40[];

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 normal_ShopMenuTopPickAnimStep_509e90(void)
{
    s32 x;
    s32 y;
    u16 id;
    f32 v;

    switch (D_00484600) {
    case 0:
        break;
    case 1:
        id = D_00484604 + 0x16;
        v = D_00484608 + D_0047D4C8;
        D_00484608 = v;
        if (!(v < D_0047D35C)) {
            D_00484608 = D_0047D35C;
            D_00484600 = 2;
        }
        UiSetWidgetColor_2905b0(normal_D_00527C40, id, D_00484608, D_00484608, D_00484608, -1.0f);
        break;
    case 2:
        id = D_00484604 + 0x16;
        v = D_00484608 - D_0047D440;
        D_00484608 = v;
        if (v <= 1.0f) {
            D_00484608 = 1.0f;
            UiFadeWidgetAlpha_290690(normal_D_00527C40, id, 0.0f, D_0047D4E0, -1.0f);
            D_00484600 = 3;
        }
        UiSetWidgetColor_2905b0(normal_D_00527C40, id, D_00484608, D_00484608, D_00484608, -1.0f);
        break;
    case 3:
        normal_ShopMenuTopRowsSlideOut_50a1c0();
        UiSetWidgetPos_290f60(normal_D_00527C40, 0xE, 0, D_00484604 * 39 + 0x32);
        UiMoveWidgetUniform_290f50(normal_D_00527C40, 0xE, 0, -0x1E, D_0047D280, 0);
        UiFadeWidgetColor_2904e0(normal_D_00527C40, 0xE, 1.0f, 1.0f, 1.0f, 1.0f, D_0047D280);
        D_00484600 = 4;
        break;
    case 4:
        UiGetWidgetPos_2910a0(normal_D_00527C40, 0xE, &x, &y);
        if ((f32)y <= -30.0f) {
            D_00484608 = 0.0f;
            D_00484600 = 7;
        }
        break;
    case 5:
        v = D_00484608 + D_0047D440;
        D_00484608 = v;
        if (!(v < D_0047D35C)) {
            D_00484608 = D_0047D35C;
            D_00484600 = 6;
        }
        break;
    case 6:
        v = D_00484608 - D_0047D440;
        D_00484608 = v;
        if (v <= 1.0f) {
            D_00484608 = 1.0f;
            D_00484600 = 7;
        }
        break;
    }
    return 0;
}
