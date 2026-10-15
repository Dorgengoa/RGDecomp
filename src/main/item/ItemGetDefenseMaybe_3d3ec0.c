#include "types.h"

extern void * ItemDefGetKind2Data_40e180(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;

struct Obj0 {
    u8 pad000[0x10];
    s32 m10;
};

struct Obj1 {
    u8 pad000[0x14];
    s16 m14;
};

s32 ItemGetDefenseMaybe_3d3ec0(struct Obj0 *p0)
{
    s32 t0;
    struct Obj1 *r0;
    s16 t1;

    t0 = p0->m10;
    r0 = ItemDefGetKind2Data_40e180(t0);
    if (r0 != 0) {
        t1 = r0->m14;
        return t1;
    }
    return 0;
}
