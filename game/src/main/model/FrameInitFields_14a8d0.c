/* rgp:protos */
#define RGP_SELF_FrameInitFields_14a8d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

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
    u8 m24;
    u8 m25;
    u8 pad026[0x2];
    u8 m28;
    u8 m29;
    u8 m2A;
    u8 m2B;
    u8 m2C;
    u8 m2D;
    s16 m2E;
};

void FrameInitFields_14a8d0(struct Obj0 *p0)
{
    p0->m28 = 0;
    p0->m00 = 0;
    p0->m04 = 0;
    p0->m08 = 0;
    p0->m0C = 0;
    p0->m10 = 0;
    p0->m14 = 0;
    p0->m18 = 0;
    p0->m1C = 0;
    p0->m29 = 1;
    p0->m2A = 0;
    p0->m2B = 0;
    p0->m24 = 1;
    p0->m25 = 1;
    p0->m2E = 0x4000;
    p0->m20 = 0;
    p0->m2C = 0;
    p0->m2D = 0;
}
