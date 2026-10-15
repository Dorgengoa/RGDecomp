#include "types.h"

/* title.bin overlay, 0x004EDC00 -- place a widget on a wrapping phase.
 *
 * The shared phase D_004841F4 is advanced by D_0047D3B8 and wrapped past
 * D_0047D1FC (PI); the store of the advanced value sits in a plain `bc1t`
 * delay slot so it is unconditional and the wrap is the guarded arm.
 *
 * $f20 is saved because the 6.0f product has to survive func_3770B0 -- which
 * is also why this one does NOT contract into `madd.s` the way the same
 * expression does in title_TitleDemoMenuCursorBobCb_4e9f00: the call splits the basic block.
 */

extern f32 D_0047D1FC;
extern f32 D_0047D3B8;
extern f32 D_004841F4;
extern void *D_00484174;

extern void func_290010(void *a, s32 b, s32 c, s32 d);
extern f32 func_128FD0(f32 v);
extern void func_3770B0(void *a, void *b, s32 *x, s32 *y);
extern void func_290F60(void *a, s32 b, s32 x, s32 y);
extern void func_3773A0(void *a, void *b);

void title_TitleLoadYesNoCursorBob_4edc00(void *o, void *unused, s32 flag)
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
        func_3770B0(D_00484174, o, &x, &y);
        x = (s32)((f32)x + k);
        func_290F60(D_00484174, 0xCA, x, y);
        func_3773A0(D_00484174, o);
    }
}
