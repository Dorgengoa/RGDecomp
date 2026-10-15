#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_0046FE10[];
extern u8 D_0046FE50[];

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
    u8 pad024[0x40];
    u8 m64;
    u8 m65;
    u8 m66;
};

struct Obj0 *WFilebufCtor_105be0(struct Obj0 *p0, s32 p1)
{
    p0->m00 = D_0046FE10;
    p0->m04 = 0;
    p0->m08 = 0;
    p0->m0C = 0;
    p0->m10 = 0;
    p0->m14 = 0;
    p0->m18 = 0;
    p0->m00 = D_0046FE50;
    p0->m1C = p1;
    p0->m20 = 0;
    p0->m64 = 0;
    p0->m66 = 1;
    p0->m65 = 0;
    return p0;
}
