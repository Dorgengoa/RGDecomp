#include "types.h"

extern void memset(void *, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;

struct Obj0 {
    u8 pad000[0x4];
    s32 m04;
    u8 pad008[0x1180];
    struct Obj1 *m1188;
};

struct Obj1 {
    s32 m00;
    s32 m04;
    s32 m08;
    s32 m0C;
    s32 m10;
    s32 m14;
    s32 m18;
    s32 m1C;
};

void InsectTeamTableReset_431d10(struct Obj0 *p0)
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

    p0->m04 = 0;
    memset((struct Obj0 *)((u8 *)p0 + 8), 0, 0x1180);
    t0 = p0->m1188;
    if (t0 != 0) {
        memset(t0, 0, 0x1588);
        t1 = p0->m1188;
        p0->m1188->m00 = 0;
        t2 = p0->m1188;
        p0->m1188->m04 = 0;
        t3 = p0->m1188;
        p0->m1188->m08 = 0;
        t4 = p0->m1188;
        p0->m1188->m0C = 0;
        t5 = p0->m1188;
        p0->m1188->m10 = 0;
        t6 = p0->m1188;
        p0->m1188->m14 = 0;
        t7 = p0->m1188;
        p0->m1188->m18 = 0;
        t8 = p0->m1188;
        p0->m1188->m1C = 0;
        return;
    }
}
