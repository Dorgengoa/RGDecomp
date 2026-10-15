#include "types.h"
/* normal 0x00507E90 -- sibling of 0x00507D70: same widget 7, but the anchor is
 * the literal 0x200 screen edge instead of a measured box. */

extern f32   D_0047D440;          /* gp - 0x7D30 */
extern void *D_00484564;          /* gp - 0xC0C  */
extern u8    D_00484570;          /* gp - 0xC00  */

extern void  func_290010(void *w, u16 id, s32 a, s32 b);
extern void  func_290F60(void *w, u16 id, s32 a, s32 b);
extern void  func_290F50(void *w, u16 id, s32 a, s32 b, s32 c, f32 f);
extern void  func_290690(void *w, u16 id, f32 x, f32 y, f32 z);

s32 normal_LeaderHudBannerSlideEdge_507e90(s32 a, s32 b, s32 c)
{
    s32 t;

    t = 0;
    if (D_00484570 != 0) {
        t = 0x19;
    }
    if (b != 0) {
        if (a == 0) {
            func_290010(D_00484564, 7, 0, -1);
        } else {
            func_290010(D_00484564, 7, 1, -1);
        }
        if (c != 0) {
            func_290F60(D_00484564, 7, -(a + 8), t + 8);
        }
        func_290F50(D_00484564, 7, 0x200 - (a + 8), t + 8, 0, 0.5f);
        func_290690(D_00484564, 7, 1.0f, 0.0625f, 0.0f);
    } else {
        if (a == 0) {
            a = 0x100;
        }
        if (c != 0) {
            func_290F60(D_00484564, 7, 0x200 - (a + 8), t + 8);
        }
        func_290F50(D_00484564, 7, 0x200, t + 8, 0, D_0047D440);
        func_290690(D_00484564, 7, 0.0f, 0.0625f, 1.0f);
    }
    return 1;
}
