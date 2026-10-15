#include "types.h"
#pragma usefloatacc off
/* normal 0x00515B20 -- lays out the four 0x753x rows plus the 0x754B/0x754C
 * pair, either instantly (a != 0, func_290F60) or on a per-row ramp
 * (func_290F50 with the animated time).  `i * 38` is retail's shift chain. */

extern void *D_004846E8;          /* gp - 0xA88 */
extern f32   D_0047DA04;          /* gp - 0x776C */
extern f32   D_0047DA0C;          /* gp - 0x7764 */
extern f32   D_0047DA10;          /* gp - 0x7760 */

extern void func_290F60(void *p, u16 id, s32 c, s32 d);
extern void func_290F50(void *p, u16 id, s32 c, s32 d, s32 e, f32 x);
extern void func_291110(void *p, u16 id, s32 c, s32 d);

s32 normal_TransMenuTopRowsSlideOut_515b20(s32 a)
{
    s32 y;
    u16 id2;
    u16 id1;
    s32 i;
    f32 m;
    f32 t;

    for (i = 0; i < 4; i++) {
        id2 = i + 0x753B;
        id1 = i + 0x7536;
        y = i * 38 + 0x4F;
        if (a != 0) {
            func_290F60(D_004846E8, id2, -0x4A, y);
            func_290F60(D_004846E8, id1, -0x47, y + 3);
        } else {
            m = D_0047DA0C * i;
            t = D_0047DA10 + m;
            func_290F50(D_004846E8, id2, -0x4A, y, 0, t);
            func_290F50(D_004846E8, id1, -0x47, y + 3, 0, t);
        }
        func_291110(D_004846E8, i + 0x753F, 1, 1);
    }
    if (a != 0) {
        func_290F60(D_004846E8, 0x754C, 0x9A, -0x28);
        func_290F60(D_004846E8, 0x754B, 0x9D, -0x25);
    } else {
        func_290F50(D_004846E8, 0x754C, 0x9A, -0x28, 0, D_0047DA04);
        func_290F50(D_004846E8, 0x754B, 0x9D, -0x25, 0, D_0047DA04);
    }
    func_291110(D_004846E8, 0x7547, 0, 1);
    func_291110(D_004846E8, 0x7546, 0, 1);
    return 0;
}
