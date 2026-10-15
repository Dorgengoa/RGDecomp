#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;
struct Obj2;

struct Obj0 {
    u8 pad000[0x4];
    s32 m04;
    u8 pad008[0x204];
    s16 m20C;
};

struct Obj1 {
    struct Obj2 *m00;
};

struct Obj2 {
    u16 m00;
    u8 pad002[0xC2];
    s16 mC4;
};

s32 NpcObjFindById_2fb420(struct Obj0 *p0, s32 p1)
{
    s32 t0;
    s16 t1;
    struct Obj1 *l1;
    s32 l0;
    struct Obj2 * t2;
    u16 t3;
    s16 t4;

    t0 = p0->m04;
    if (t0 == 0) {
        return 0;
    }
    t1 = p0->m20C;
    l1 = (struct Obj1 *)((u8 *)p0 + 0xC);
    l0 = 0;
    while (l0 < t1) {
        t2 = l1->m00;
        t3 = l1->m00->m00;
        if ((t3 & 1) != 0) {
            t4 = l1->m00->mC4;
            if (t4 == p1) {
                return (s32)l1->m00;
            }
        }
        l0 = (l0 + 1);
        l1 = (struct Obj1 *)((u8 *)l1 + 4);
    }
    return 0;
}
