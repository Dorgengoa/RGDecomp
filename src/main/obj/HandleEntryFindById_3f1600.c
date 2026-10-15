#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern const s32 D_004644C8;

struct Obj0;
struct Obj1;
struct Obj2;

struct Obj0 {
    u8 pad000[0x20];
    s32 m20;
};

struct Obj1 {
    struct Obj2 *m00;
};

struct Obj2 {
    s32 m00;
};

s32 HandleEntryFindById_3f1600(struct Obj0 *p0, s32 p1)
{
    s32 t0;
    s32 t1;
    struct Obj1 *l0;
    s32 l1;
    struct Obj2 * t2;
    s32 t3;

    t0 = p0->m20;
    if (t0 == 0) {
        return 0;
    }
    t1 = D_004644C8;
    l0 = (struct Obj1 *)t0;
    l1 = 0;
    while (l1 < t1) {
        t2 = l0->m00;
        if (t2 != 0) {
            t3 = l0->m00->m00;
            if (t3 == p1) {
                return (s32)l0;
            }
        }
        l1 = (l1 + 1);
        l0 = (struct Obj1 *)((u8 *)l0 + 0x20);
    }
    return 0;
}
