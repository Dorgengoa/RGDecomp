/* rgp:protos */
#define RGP_SELF_MapPartTableReset_1de6c0 1
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
    s16 m00;
    u8 pad002[0x2];
    s32 m04;
    s16 m08;
    s16 m0A;
    f32 m0C;
    f32 m10;
    f32 m14;
    f32 m18;
    f32 m1C;
    f32 m20;
    f32 m24;
    f32 m28;
    f32 m2C;
    f32 m30;
    f32 m34;
    f32 m38;
};

void MapPartTableReset_1de6c0(struct Obj0 *p0)
{
    f32 t0;
    f32 t1;

    p0->m00 = -1;
    t0 = D_0047D1F0;
    p0->m04 = 0;
    t1 = D_0047D1EC;
    p0->m08 = 0;
    p0->m0A = 0;
    p0->m0C = t0;
    p0->m10 = t0;
    p0->m14 = t0;
    p0->m18 = t1;
    p0->m1C = t1;
    p0->m20 = t1;
    p0->m24 = t0;
    p0->m28 = t0;
    p0->m2C = t0;
    p0->m30 = t1;
    p0->m34 = t1;
    p0->m38 = t1;
}
