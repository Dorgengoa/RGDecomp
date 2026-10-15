#include "types.h"

extern void ItemReset_3d50d0(void *);

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
    u8 pad000[0x2];
    s16 m02;
    s16 m04;
    s16 m06;
    s16 m08;
    u8 pad00A[0x2];
    s32 m0C;
    s32 m10;
    s32 m14;
    s32 m18;
    s32 m1C;
    u8 pad020[0x7CC];
    s32 m7EC;
};

void ItemGameRecReset_3d0e50(struct Obj0 *p0)
{
    struct Obj1 * t0;
    struct Obj1 * t1;
    struct Obj1 * t2;
    struct Obj1 * t3;
    struct Obj1 * t4;
    struct Obj1 * t5;
    struct Obj1 * t6;
    struct Obj1 * t7;
    struct Obj1 * t8;
    struct Obj1 * t9;

    ItemReset_3d50d0(p0);
    t0 = p0->m18;
    if (t0 != 0) {
        p0->m18->m02 = -1;
        t1 = p0->m18;
        p0->m18->m04 = -1;
        t2 = p0->m18;
        p0->m18->m0C = 0;
        t3 = p0->m18;
        p0->m18->m06 = -1;
        t4 = p0->m18;
        p0->m18->m08 = -1;
        t5 = p0->m18;
        p0->m18->m10 = 0;
        t6 = p0->m18;
        p0->m18->m14 = 0;
        t7 = p0->m18;
        p0->m18->m18 = 0;
        t8 = p0->m18;
        p0->m18->m1C = 0;
        t9 = p0->m18;
        p0->m18->m7EC = 0xBF800000;
    }
}
