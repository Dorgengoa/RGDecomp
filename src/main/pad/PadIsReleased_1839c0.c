#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x4];
    s32 m04;
    u8 pad008[0x54];
    s32 m5C;
    u8 pad060[0x1EC];
    s32 m24C;
};

s32 PadIsReleased_1839c0(struct Obj0 *p0, s32 p1)
{
    s32 t0;
    s32 rv0;
    s32 t1;
    s32 t2;

    t0 = p0->m24C;
    rv0 = ((p1 & (~t1 & t2)) != 0);
    if (t0 != 0) {
        rv0 = 0;
    } else {
        t1 = p0->m04;
        t2 = p0->m5C;
        rv0 = ((p1 & (~t1 & t2)) != 0);
    }
    return rv0;
}
