/* rgp:protos */
#define RGP_SELF_normal_LeaderHudBannerBlinkTick_507a90 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00507A90 -- the page-turn tick.  The gp float at 0x0047D440 is a
 * literal-pool entry (0.3f); 0x0047D248 is a real gp global. */

extern void *D_00484564;          /* gp - 0xC0C */
extern void *D_0048456C;          /* gp - 0xC04 */
extern u8    D_00484570;          /* gp - 0xC00 */
extern s32   D_00480630;          /* gp - 0x4B40 */
extern s32   D_00480634;          /* gp - 0x4B3C */
extern f32   D_0047D248;          /* gp - 0x7F28 */
extern f32   D_0047D440;          /* gp - 0x7D30 */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void normal_LeaderHudBannerBlinkTick_507a90(void)
{
    s32 t;
    s32 k;
    f32 v;

    if (((signed char)normal_LeaderHudIsBannerBlinking_506ae0(D_0048456C)) != 0) {
        if (((unsigned char)normal_LeaderHudBannerCountdownTick_506a70(D_0048456C)) == 0) {
            t = D_00480630;
            v = 1.0f - 1.0f / (f32)(t + 1);
            if (t == 0) {
                D_00480630 = 4;
            } else {
                D_00480630 = t - 1;
            }
            UiSetWidgetAlpha_2907a0(D_00484564, 7, v);
        } else {
            D_00480630 = 4;
            D_00480634 = 1;
            normal_LeaderHudSetBannerBlinking_506af0(D_0048456C, 0);
            normal_LeaderHudSetField70Related_506b40(D_0048456C, -1);
            UiSetWidgetAlpha_2907a0(D_00484564, 7, D_0047D248);
            UiFadeWidgetAlpha_290690(D_00484564, 7, 0.0f, 0.0625f, -1.0f);
            k = 0;
            if (D_00484570 != 0) {
                k = 0x19;
            }
            UiMoveWidgetUniform_290f50(D_00484564, 7, 0x200, k + 8, D_0047D440, 0);
        }
    } else {
        D_00480630 = 4;
        D_00480634 = 1;
    }
}
