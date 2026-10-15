#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;

struct Obj0 {
    s32 m00;
    u8 pad004[0x4];
    struct Obj1 *m08;
};

struct Obj1 {
    s32 m00;
};

s32 ArrayGetCountIndirect_1527c0(struct Obj0 *p0)
{
    s32 t0;
    struct Obj1 * t1;
    s32 t2;

    t0 = p0->m00;
    if (t0 != 0) {
        t1 = p0->m08;
        t2 = p0->m08->m00;
        return t2;
    }
    return 0;
}
