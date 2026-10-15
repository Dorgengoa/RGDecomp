#include "types.h"

/* Advance a global phase, wrap it, and drive the shake amplitude from it.
   The product is named so mwcc does not contract the mul.s/add.s pair into a
   madd.s - retail has them separate. */

struct S {
    u8 pad000[0x5C];
    s32 m5C;
};

extern f32 D_00482CD8;
extern f32 D_0047D65C;
extern f32 D_0047D1FC;
extern f32 D_0047D248;
extern f32 D_0047D660;
extern f32 D_0047D35C;
extern f32 Sinf_128fd0(f32);
extern void UiSetWidgetColor_2905b0(s32, s32, f32, f32, f32, f32);

s32 MenuWidgetPulseColor_340d40(struct S *p0, s32 p1, s32 p2)
{
    f32 t;
    f32 v;

    if (p2 != 0) {
        D_00482CD8 = 0.0f;
    }
    D_00482CD8 = D_00482CD8 + D_0047D65C;
    if (D_00482CD8 >= D_0047D1FC) {
        D_00482CD8 = 0.0f;
    }
    t = D_0047D248 * Sinf_128fd0(D_00482CD8);
    v = D_0047D660 + t;
    if (v >= D_0047D35C) {
        v = D_0047D35C;
    }
    UiSetWidgetColor_2905b0(p0->m5C, p1, v, v, v, -1.0f);
    return 1;
}
