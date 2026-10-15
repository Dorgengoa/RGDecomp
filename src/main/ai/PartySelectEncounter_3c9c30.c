#include "types.h"

extern void * PartyFindEncounterForKeyMaybe_3c99e0(void *, s32, void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;
struct Obj2;
struct Obj3;

struct Obj0 {
    u8 pad000[0x24];
    struct Obj1 *m24;
    u8 pad028[0x56];
    s16 m7E;
    s16 m80;
    s16 m82;
};

struct Obj1 {
    u8 pad000[0x10];
    s32 m10;
};

struct Obj2 {
    s16 m00;
};

struct Obj3 {
    s16 m00;
};

struct Obj3 *PartySelectEncounter_3c9c30(struct Obj0 *p0)
{
    s32 v3C;
    struct Obj1 * t0;
    struct Obj2 *rv0;
    s32 t1;
    s32 rv1;
    s16 t2;
    struct Obj3 *r2;
    s16 t3;
    s32 t4;

    t0 = p0->m24;
    if (t0 != 0) {
        t1 = t0->m10;
        rv0 = (struct Obj2 *)t1;
    } else {
        rv0 = 0;
    }
    if (rv0 != 0) {
        t2 = rv0->m00;
        rv1 = t2;
    } else {
        rv1 = -1;
    }
    v3C = -1;
    r2 = PartyFindEncounterForKeyMaybe_3c99e0(p0, rv1, &v3C);
    if (r2 != 0) {
        p0->m7E = rv1;
        t3 = r2->m00;
        p0->m80 = t3;
        t4 = v3C;
        p0->m82 = t4;
        return r2;
    }
    p0->m7E = -1;
    p0->m80 = -1;
    p0->m82 = -1;
    return r2;
}
