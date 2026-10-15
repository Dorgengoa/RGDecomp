#include "types.h"

extern s32 PartyLocationGroupIdIsOneMaybe_3cb120(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;

struct Obj0 {
    u8 pad000[0x8];
    struct Obj1 *m08;
    u8 pad00C[0xC];
    s32 m18;
};

struct Obj1 {
    u8 pad000[0xC];
    s32 m0C;
};

s32 PlanetEntryGetCurrentMaybe_3ec530(struct Obj0 *p0)
{
    struct Obj1 * t0;
    s32 rv2;
    s32 t1;
    s32 r0;
    s32 rv1;
    struct Obj1 * t2;
    s32 t3;
    struct Obj1 * t4;
    s32 t5;

    t0 = p0->m08;
    rv2 = rv1;
    if (t0 == 0) {
        rv2 = 0;
    } else {
        t1 = p0->m18;
        r0 = PartyLocationGroupIdIsOneMaybe_3cb120(t1);
        rv1 = (t5 + 0x1C);
        if (r0 != 0) {
            t2 = p0->m08;
            t3 = p0->m08->m0C;
            rv1 = t3;
        } else {
            t4 = p0->m08;
            t5 = p0->m08->m0C;
            rv1 = (t5 + 0x1C);
        }
        rv2 = rv1;
    }
    return rv2;
}
