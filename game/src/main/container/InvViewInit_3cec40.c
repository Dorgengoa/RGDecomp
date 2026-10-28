/* rgp:protos */
#define RGP_SELF_InvViewInit_3cec40 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x4];
    s32 m04;
    s16 m08;
    s16 m0A;
    s16 m0C;
    s16 m0E;
    s16 m10;
    s16 m12;
};

void InvViewInit_3cec40(struct Obj0 *p0, s32 p1, s32 p2, s32 p3, s32 p4, s32 p5)
{
    p0->m04 = p1;
    p0->m08 = p2;
    p0->m0A = p3;
    p0->m0C = p4;
    p0->m0E = p5;
    p0->m10 = -1;
    p0->m12 = -1;
}
