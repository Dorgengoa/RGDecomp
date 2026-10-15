#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_00470B00[];
extern u8 D_00470DD0[];
extern u8 D_00470E00[];
extern u8 D_00470E30[];

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
};

struct Obj0 *EffCurveCtorRotX_19cea0(struct Obj0 *p0)
{
    p0->m00 = D_00470E30;
    p0->m04 = -1;
    p0->m00 = D_00470E00;
    p0->m08 = 0;
    p0->m10 = 0;
    p0->m0C = 0;
    p0->m14 = 0;
    p0->m18 = 0;
    p0->m00 = D_00470DD0;
    p0->m1C = 0;
    p0->m20 = 0;
    p0->m00 = D_00470B00;
    return p0;
}
