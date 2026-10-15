#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;
struct Obj2;
struct Obj3;
struct Obj4;
struct Obj5;

struct Obj0 {
    u8 pad000[0x8];
    struct Obj1 *m08;
};

struct Obj1 {
    u8 pad000[0x94];
    struct Obj2 *m94;
};

struct Obj2 {
    u8 pad000[0x14];
    struct Obj3 *m14;
};

struct Obj3 {
    u8 pad000[0x10];
    s32 m10;
    s32 m14;
};

struct Obj4 {
    struct Obj5 *m00;
};

struct Obj5 {
    s16 m00;
};

s32 RankingFindPlayerEntryMaybe_3e8c70(struct Obj0 *p0)
{
    struct Obj3 *t2;
    s32 t4;
    struct Obj4 *l0;
    s32 l1;
    struct Obj5 *t5;
    s16 t6;

    t2 = p0->m08->m94->m14;
    if (t2 == 0) {
        return 0;
    }
    l0 = (struct Obj4 *)t2->m14;
    t4 = t2->m10;
    l1 = 0;
    while (l1 < t4) {
        t5 = l0->m00;
        if (t5 != 0) {
            t6 = t5->m00;
            if (t6 == 0) {
                return (s32)l0;
            }
        }
        l1 = (l1 + 1);
        l0 = (struct Obj4 *)((u8 *)l0 + 0x14);
    }
    return 0;
}
