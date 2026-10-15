#include "types.h"

/* title.bin overlay, 0x004EDAF0 -- the twin of title_FUN_004EDC00: same
 * wrapping phase, a different placement helper, and a second branch choosing
 * between the four-argument and the six-argument draw call.
 */

extern f32 D_0047D1FC;
extern f32 D_0047D3B8;
extern f32 D_004841F4;
extern void *D_00484174;

extern void func_290010(void *a, s32 b, s32 c, s32 d);
extern f32 func_128FD0(f32 v);
extern void func_376FD0(void *a, s16 b, s32 *x, s32 *y);
extern void func_290F60(void *a, s32 b, s32 x, s32 y);
extern void func_290F50(void *a, s32 b, s32 x, s32 y, s32 e, f32 f);

void title_TitleLoadPortCursorBob_4edaf0(s16 a, s32 mode, s32 flag)
{
    f32 t;
    f32 k;
    s32 x;
    s32 y;

    if (flag != 0) {
        func_290010(D_00484174, 0xCA, 1, -1);
        goto on;
    }
    func_290010(D_00484174, 0xCA, 0, -1);
    return;
on:
    {
        t = D_004841F4 + D_0047D3B8;
        D_004841F4 = t;
        if (t > 0.0f) {
            D_004841F4 = t - D_0047D1FC;
        }
        k = 6.0f * func_128FD0(D_004841F4);
        func_376FD0(D_00484174, a, &x, &y);
        x = (s32)((f32)x + k);
        if (mode != 0) {
            func_290F60(D_00484174, 0xCA, x, y);
        } else {
            func_290F50(D_00484174, 0xCA, x, y, 0, 0.5f);
        }
    }
}
