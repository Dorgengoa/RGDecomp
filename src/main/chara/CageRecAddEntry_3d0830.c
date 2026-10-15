#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;

struct Obj0 {
    u8 pad000[0x18];
    struct Obj1 *m18;
};

struct Obj1 {
    u8 pad000[0xA];
    s16 m0A;
};

struct Obj1 *CageRecAddEntry_3d0830(struct Obj0 *p0)
{
    struct Obj1 * t0;
    s16 t1;
    struct Obj1 * rv0;
    struct Obj1 * t2;
    s16 t3;

    t0 = p0->m18;
    t1 = p0->m18->m0A;
    if ((t1 < 0x10) == 0) {
        rv0 = 0;
    } else {
        p0->m18->m0A = (t1 + 1);
        t2 = p0->m18;
        t3 = p0->m18->m0A;
        *(s16 *)((u8 *)t2 + ((((t3 + -1) << 5) - (t3 + -1)) << 2) + 0x2C) = t3;
        rv0 = (struct Obj1 *)((u8 *)(struct Obj1 *)((u8 *)t2 + ((((t3 + -1) << 5) - (t3 + -1)) << 2)) + 0x2C);
    }
    return rv0;
}
