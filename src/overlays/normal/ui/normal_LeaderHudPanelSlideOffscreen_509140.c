#include "types.h"
/* normal 0x00509140 -- slide the 0x02 / 0x10 pair of widgets in or out. */

extern f32   D_0047D440;          /* gp - 0x7D30 */
extern f32   D_0047D534;          /* gp - 0x7C3C */
extern void *D_00484564;          /* gp - 0xC0C  */

extern void  func_290F60(void *w, u16 id, s32 a, s32 b);
extern void  func_290F50(void *w, u16 id, s32 a, s32 b, s32 c, f32 f);

s32 normal_LeaderHudPanelSlideOffscreen_509140(s32 a, s32 b, s32 c)
{
    if (a != 0) {
        if (b != 0) {
            func_290F60(D_00484564, 2, -0x100, 0x13);
            func_290F60(D_00484564, 0x10, -0x100, 0x13);
        }
        func_290F50(D_00484564, 2, 8, 0x13, 0, D_0047D440);
        func_290F50(D_00484564, 0x10, 8, 0x13, 0, D_0047D440);
    } else {
        if (b != 0) {
            func_290F60(D_00484564, 2, 8, 0x13);
            func_290F60(D_00484564, 0x10, 8, 0x13);
        }
        if (c == 0) {
            func_290F60(D_00484564, 2, 0x200, 0x13);
            func_290F60(D_00484564, 0x10, 0x200, 0x13);
        }
        func_290F50(D_00484564, 2, -0x100, 0x13, 0, D_0047D534);
        func_290F50(D_00484564, 0x10, -0x100, 0x13, 0, D_0047D534);
    }
    return 1;
}
