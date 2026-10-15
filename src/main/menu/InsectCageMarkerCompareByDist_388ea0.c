#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;

struct Obj0 {
    u8 pad000[0x4];
    f32 m04;
};

struct Obj1 {
    u8 pad000[0x4];
    f32 m04;
};

s32 InsectCageMarkerCompareByDist_388ea0(struct Obj1 *p0, struct Obj0 *p1)
{
    s32 rv1;
    s32 rv0;

    if (p0->m04 > p1->m04) {
        rv1 = 1;
    } else {
        rv0 = 1;
        if (p0->m04 >= p1->m04) {
            rv0 = 0;
        }
        rv1 = -(rv0 & 0xFF);
    }
    return rv1;
}
