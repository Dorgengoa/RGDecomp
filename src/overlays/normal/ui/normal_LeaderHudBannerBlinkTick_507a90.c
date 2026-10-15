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

extern s32  normal_LeaderHudIsBannerBlinking_506ae0(void *p);
extern s32  normal_LeaderHudBannerCountdownTick_506a70(void *p);
extern void normal_LeaderHudSetBannerBlinking_506af0(void *p, s32 a);
extern void normal_LeaderHudSetField70Related_506b40(void *p, s32 a);
extern void func_2907A0(void *w, s32 id, f32 v);
extern void func_290690(void *w, s32 id, f32 x, f32 y, f32 z);
extern void func_290F50(void *w, s32 id, s32 a, s32 b, s32 c, f32 t);

void normal_LeaderHudBannerBlinkTick_507a90(void)
{
    s32 t;
    s32 k;
    f32 v;

    if (normal_LeaderHudIsBannerBlinking_506ae0(D_0048456C) != 0) {
        if (normal_LeaderHudBannerCountdownTick_506a70(D_0048456C) == 0) {
            t = D_00480630;
            v = 1.0f - 1.0f / (f32)(t + 1);
            if (t == 0) {
                D_00480630 = 4;
            } else {
                D_00480630 = t - 1;
            }
            func_2907A0(D_00484564, 7, v);
        } else {
            D_00480630 = 4;
            D_00480634 = 1;
            normal_LeaderHudSetBannerBlinking_506af0(D_0048456C, 0);
            normal_LeaderHudSetField70Related_506b40(D_0048456C, -1);
            func_2907A0(D_00484564, 7, D_0047D248);
            func_290690(D_00484564, 7, 0.0f, 0.0625f, -1.0f);
            k = 0;
            if (D_00484570 != 0) {
                k = 0x19;
            }
            func_290F50(D_00484564, 7, 0x200, k + 8, 0, D_0047D440);
        }
    } else {
        D_00480630 = 4;
        D_00480634 = 1;
    }
}
