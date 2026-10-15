#include "types.h"

extern s32 GroupEntryMatchesKey_3f41b0(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;

struct Obj0 {
    u8 pad000[0x8];
    s32 m08;
    s32 m0C;
};

struct Obj1 {
    u8 pad000[0x94];
    s32 m94;
};

s32 GroupFindByKey_41fb60(struct Obj0 *p0, s32 p1)
{
    s32 t0;
    s32 t1;
    struct Obj1 *l1;
    s32 l0;
    s32 t2;
    s32 r4;

    t0 = p0->m08;
    if (t0 == 0) {
        return 0;
    }
    t1 = p0->m0C;
    l1 = (struct Obj1 *)t1;
    l0 = 0;
    while (l0 < 2) {
        t2 = l1->m94;
        if (t2 == 0) {
            goto Lc3;
        }
        r4 = GroupEntryMatchesKey_3f41b0(t2, p1);
        if (r4 != 0) {
            return (s32)l1;
        }
    Lc3:;
        l0 = (l0 + 1);
        l1 = (struct Obj1 *)((u8 *)l1 + 0x98);
    }
    return 0;
}
