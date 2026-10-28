/* rgp:protos */
#define RGP_SELF_CBlurParamsInit_1ce6e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern f32 D_0047D1C8;

struct Obj0;

struct Obj0 {
    s32 m00;
    s32 m04;
    s32 m08;
    f32 m0C;
    u8 m10;
    u8 m11;
    s16 m12;
    s16 m14;
    s16 m16;
};

void CBlurParamsInit_1ce6e0(struct Obj0 *p0)
{
    f32 t0;

    p0->m10 = 0;
    p0->m12 = 1;
    p0->m11 = 0;
    t0 = D_0047D1C8;
    p0->m00 = 0x3F800000;
    p0->m04 = 0x3F800000;
    p0->m08 = 0x3F800000;
    p0->m0C = t0;
    p0->m14 = 0;
    p0->m16 = 0;
}
