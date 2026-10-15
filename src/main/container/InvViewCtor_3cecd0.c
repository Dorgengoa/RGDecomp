#include "types.h"

extern s32 InvViewInit_3cec40(void *, s32, s32, s32, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_00472250[];
extern u8 D_00475890[];
extern u8 D_004758B0[];

struct Obj0;

struct Obj0 {
    void *m00;
};

struct Obj0 *InvViewCtor_3cecd0(struct Obj0 *p0, s32 p1, s32 p2, s32 p3, s32 p4, s32 p5)
{
    s32 r0;

    p0->m00 = D_00472250;
    p0->m00 = D_004758B0;
    p0->m00 = D_00475890;
    r0 = InvViewInit_3cec40(p0, p1, p2, p3, p4, p5);
    return p0;
}
