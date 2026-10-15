#include "types.h"

typedef unsigned __int128 u128;

extern void VecScale_13be00(f32 *, const f32 *, f32);   /* dst = src * k   */
extern void VecAdd_13be20(f32 *, const f32 *, const f32 *); /* dst = a + b */

struct Obj0 {
    u8 pad000[0x30];
    f32 m30;
    s32 m34;
};

struct Obj1 {
    u8 pad000[0x38];
    s32 m38;
    u8 pad03C[0x14];
    f32 m50[4];
    f32 m60[4];
    u8 pad070[0xE0];
    f32 m150[4];
    f32 m160[4];
};

/* Two guards, both taken from the FALL-THROUGH: bgtz falls into the
   "counter not yet started" arm, and the bnel falls into the reset arm. */
s32 EventCameraCmdEyeAtVelDecay_255230(struct Obj0 *p0, struct Obj1 *p1)
{
    s32 t;

    t = p1->m38;
    if (t <= 0) {
        p1->m38 = t + 1;
        return 1;
    }
    if (t >= p0->m34) {
        p1->m38 = 0;
        *(u128 *)p1->m150 = 0;
        *(u128 *)p1->m160 = 0;
        return 0;
    }
    VecScale_13be00(p1->m150, p1->m150, p0->m30);
    VecScale_13be00(p1->m160, p1->m160, p0->m30);
    VecAdd_13be20(p1->m50, p1->m50, p1->m150);
    VecAdd_13be20(p1->m60, p1->m60, p1->m160);
    p1->m38 = p1->m38 + 1;
    return 1;
}
