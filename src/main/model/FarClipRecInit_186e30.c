#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern f32 D_0047E040;
extern f32 D_0047E050;

struct Obj0;

struct Obj0 {
    s32 m00;
    s32 m04;
    s32 m08;
    s32 m0C;
    s32 m10;
    s32 m14;
    s32 m18;
    f32 m1C;
    f32 m20;
};

void FarClipRecInit_186e30(struct Obj0 *p0)
{
    f32 t0;
    f32 t1;

    p0->m00 = 0;
    p0->m08 = 0;
    t0 = D_0047E040;
    p0->m0C = 0xBF800000;
    t1 = D_0047E050;
    p0->m10 = 0xBF800000;
    p0->m14 = 0;
    p0->m18 = 0;
    p0->m1C = t0;
    p0->m20 = t1;
    p0->m04 = 0;
}
