#include "types.h"

extern void Nop_1ed0b0(void);

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
    u8 m10;
    u8 m11;
    s16 m12;
    s16 m14;
    s16 m16;
    s16 m18;
    s16 m1A;
    s32 m1C;
};

void MapBlockBoxListInit_1e0580(struct Obj0 *p0)
{
    Nop_1ed0b0();
    p0->m14 = -1;
    p0->m16 = -1;
    p0->m18 = -1;
    p0->m1A = -1;
    p0->m1C = -1;
    p0->m04 = 0;
    p0->m10 = 0;
    p0->m08 = 0;
    p0->m11 = 0;
    p0->m0C = 0;
    p0->m12 = 0;
    p0->m00 = 0;
}
