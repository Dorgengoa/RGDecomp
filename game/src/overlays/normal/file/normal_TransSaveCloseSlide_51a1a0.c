/* rgp:protos */
#define RGP_SELF_normal_TransSaveCloseSlide_51a1a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x0051A1A0 -- two-state phase driver, state word behind the pointer
 * argument.  Sibling of normal_FUN_0051C1E0. */

extern void *D_004847D4;          /* gp - 0x99C */
extern f32   D_0047D5D0;          /* gp - 0x7BA0 */
extern f32   D_0047D9F8;          /* gp - 0x7778 */
extern f32   D_0047DA00;          /* gp - 0x7770 */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 normal_TransSaveCloseSlide_51a1a0(s32 *p)
{
    s32 x;
    s32 y;
    s32 x2;
    s32 y2;

    switch (p[0]) {
    case 0:
        UiMoveWidgetUniform_290f50(D_004847D4, 0x753B, -0x12, 0xC, D_0047D5D0, 0);
        UiMoveWidgetUniform_290f50(D_004847D4, 0x7536, -0xF, 0xF, D_0047D5D0, 0);
        UiFadeWidgetAlpha_290690(D_004847D4, 0x7558, 0.0f, D_0047D9F8, -1.0f);
        UiMoveWidgetUniform_290f50(D_004847D4, 0x7558, 0xC8, 0, D_0047D5D0, 0);
        UiGetWidgetPos_2910a0(D_004847D4, 0x753B, &x, &y);
        if (x < 0x1F) {
            p[0] = 1;
            UiFadeWidgetAlpha_290690(D_004847D4, 0x7553, 0.0f, -0.05f, -1.0f);
            UiFadeWidgetAlpha_290690(D_004847D4, 0x7531, 0.0f, -0.05f, -1.0f);
        }
        break;
    case 1:
        UiGetWidgetAlpha_290770(D_004847D4, 0x7553);
        UiFadeWidgetAlpha_290690(D_004847D4, 0x754F, 1.0f, D_0047DA00, -1.0f);
        UiSetSpriteU_28f930(D_004847D4, 0x754F, 0xE0, 0);
        UiGetWidgetPos_2910a0(D_004847D4, 0x753B, &x2, &y2);
        if (x2 == -0x12) {
            if (y2 == 0xC) {
                UiSetWidgetPos_290f60(D_004847D4, 0x753B, -0x4A, 0x4F);
                UiSetWidgetPos_290f60(D_004847D4, 0x7536, -0x45, 0x53);
            }
        }
        p[0] = 3;
        break;
    }
    return 0;
}
