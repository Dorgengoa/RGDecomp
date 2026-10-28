/* rgp:protos */
#define RGP_SELF_FilebufCtor_105040 1
#include "port/game_protos.h"
#line 1
#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_0046FEE0[];
extern u8 D_0046FF20[];

struct Obj0;

struct Obj0 {
    void *m00;
    s32 m04;
    s32 m08;
    s32 m0C;
    s32 m10;
    s32 m14;
    s32 m18;
    s32 m1C;
    s32 m20;
    u8 pad024[0x10];
    u8 m34;
    u8 m35;
    u8 m36;
};

struct Obj0 *FilebufCtor_105040(struct Obj0 *p0, s32 p1)
{
    p0->m00 = D_0046FEE0;
    p0->m04 = 0;
    p0->m08 = 0;
    p0->m0C = 0;
    p0->m10 = 0;
    p0->m14 = 0;
    p0->m18 = 0;
    p0->m00 = D_0046FF20;
    p0->m1C = p1;
    p0->m20 = 0;
    p0->m34 = 0;
    p0->m36 = 1;
    p0->m35 = 1;
    return p0;
}
