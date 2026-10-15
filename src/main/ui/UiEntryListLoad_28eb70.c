#include "types.h"

extern void UiEntryListResetEntryRect_28eb40(void *, void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;
struct Obj2;

struct Obj0 {
    s32 m00;
    s32 m04;
    u8 pad008[0x8];
    s32 m10;
};

struct Obj1 {
    u16 m00;
    s16 m02;
    s16 m04;
    s16 m06;
    s16 m08;
    s16 m0A;
    s16 m0C;
    s16 m0E;
    s16 m10;
};

struct Obj2 {
    struct Obj1 *m00;
    s16 m04;
    s16 m06;
    s16 m08;
    s16 m0A;
    s16 m0C;
    s16 m0E;
    s16 m10;
    s16 m12;
};

void UiEntryListLoad_28eb70(struct Obj0 *p0, s32 p1, s32 p2)
{
    s32 t0;
    struct Obj1 *l1;
    struct Obj2 *l0;
    s16 t1;
    s16 t2;
    s16 t3;
    s16 t4;
    s16 t5;
    s16 t6;
    s16 t7;
    s16 t8;

    p0->m00 = p1;
    t0 = p0->m04;
    l0 = (struct Obj2 *)t0;
    l1 = (struct Obj1 *)p1;
    while (l1->m00 != 0) {
        l0->m00 = l1;
        t1 = l1->m02;
        l0->m04 = t1;
        t2 = l1->m04;
        l0->m06 = t2;
        t3 = l1->m06;
        l0->m08 = t3;
        t4 = l1->m08;
        l0->m0A = t4;
        t5 = l1->m0A;
        l0->m0C = t5;
        t6 = l1->m0C;
        l0->m0E = t6;
        t7 = l1->m0E;
        l0->m10 = t7;
        t8 = l1->m10;
        l0->m12 = t8;
        UiEntryListResetEntryRect_28eb40(p0, l0);
        l0 = (struct Obj2 *)((u8 *)l0 + 0x20);
        l1 = (struct Obj1 *)((u8 *)l1 + 0x40);
    }
    l0->m00 = 0;
    p0->m10 = p2;
}
