/* rgp:protos */
#define RGP_SELF_AreaBoxReset_1e98c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern f32 D_0047D1EC;
extern f32 D_0047D1F0;

struct Obj0;

struct Obj0 {
    s32 m00;
    s32 m04;
    s32 m08;
    s32 m0C;
    s32 m10;
    s32 m14;
    s32 m18;
    s32 m1C;
    s32 m20;
    s32 m24;
    s32 m28;
    s32 m2C;
    s32 m30;
    s32 m34;
    s32 m38;
    s32 m3C;
    s32 m40;
    f32 m44;
    f32 m48;
};

void AreaBoxReset_1e98c0(struct Obj0 *p0)
{
    f32 t0;
    f32 t1;

    p0->m00 = 0;
    p0->m04 = 0;
    t0 = D_0047D1F0;
    p0->m08 = 0;
    t1 = D_0047D1EC;
    p0->m0C = 0;
    p0->m10 = 0;
    p0->m14 = 0;
    p0->m18 = 0;
    p0->m1C = 0;
    p0->m20 = 0;
    p0->m24 = 0;
    p0->m28 = 0;
    p0->m2C = 0;
    p0->m30 = 0;
    p0->m34 = 0x3F800000;
    p0->m38 = 0;
    p0->m3C = 0;
    p0->m40 = 0x3F800000;
    p0->m44 = t0;
    p0->m48 = t1;
}
