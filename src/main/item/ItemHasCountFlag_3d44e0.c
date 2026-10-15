#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;

struct Obj0 {
    u8 pad000[0x10];
    struct Obj1 *m10;
};

struct Obj1 {
    u8 pad000[0x17];
    u8 m17;
};

s32 ItemHasCountFlag_3d44e0(struct Obj0 *p0)
{
    struct Obj1 * t0;
    u8 t1;

    t0 = p0->m10;
    if (t0 != 0) {
        t1 = p0->m10->m17;
        return ((((u64)(((s64)t1) << 0x39)) >> 0x3F) != 0);
    }
    return 0;
}
