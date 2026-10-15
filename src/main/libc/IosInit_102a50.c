#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x4];
    s32 m04;
    s32 m08;
    s32 m0C;
    s32 m10;
    s32 m14;
    s32 m18;
    s32 m1C;
    s32 m20;
    u8 pad024[0x4];
    s64 m28;
    s64 m30;
    s16 m38;
    u8 m3A;
    u8 m3B;
};

void IosInit_102a50(struct Obj0 *p0, s32 p1)
{
    s32 rv0;

    p0->m20 = p1;
    p0->m3B = 0;
    p0->m3A = 1;
    rv0 = 1;
    if (p1 != 0) {
        rv0 = 0;
    }
    p0->m3A = rv0;
    p0->m38 = 0x1002;
    p0->m30 = 0;
    p0->m28 = 6;
    p0->m04 = 0;
    p0->m08 = 0;
    p0->m0C = 0;
    p0->m10 = 0;
    p0->m14 = 0;
    p0->m18 = 0;
    p0->m1C = 0;
}
