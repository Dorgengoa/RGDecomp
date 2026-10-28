/* rgp:protos */
#define RGP_SELF_normal_TransWarpCloseSlide_51c1e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x0051C1E0 -- two-state phase driver on the gp word D_00484884.
 * Same shape as normal_FUN_0051A1A0 (which drives the same states off a
 * pointer argument instead of a gp word).
 */

extern void *D_00484710;          /* gp - 0xA60 */
extern s32   D_00484884;          /* gp - 0x8EC */
extern f32   D_0047D5D0;          /* gp - 0x7BA0 */
extern f32   D_0047D9E0;          /* gp - 0x7790 */
extern f32   D_0047D9E4;          /* gp - 0x778C */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 normal_TransWarpCloseSlide_51c1e0(void)
{
    s32 x;
    s32 y;

    switch (D_00484884) {
    case 0:
        UiMoveWidgetUniform_290f50(D_00484710, 0x753C, -0x12, 0x9C, D_0047D5D0, 0);
        UiMoveWidgetUniform_290f50(D_00484710, 0x7537, -0xF, 0x9F, D_0047D5D0, 0);
        UiGetWidgetPos_2910a0(D_00484710, 0x753C, &x, &y);
        if (x < 0x1F) {
            D_00484884 = 1;
            UiFadeWidgetAlpha_290690(D_00484710, 0x7553, 0.0f, D_0047D9E0, -1.0f);
        }
        break;
    case 1:
        UiGetWidgetAlpha_290770(D_00484710, 0x7553);
        UiFadeWidgetAlpha_290690(D_00484710, 0x7550, 1.0f, D_0047D9E4, -1.0f);
        UiSetSpriteU_28f930(D_00484710, 0x7550, 0xE0, 0);
        D_00484884 = 4;
        break;
    }
    return 0;
}
