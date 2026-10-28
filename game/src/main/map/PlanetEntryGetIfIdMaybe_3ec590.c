/* rgp:protos */
#define RGP_SELF_PlanetEntryGetIfIdMaybe_3ec590 1
#include "port/game_protos.h"
#line 1
#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;
struct Obj1;
struct Obj2;
struct Obj3;

struct Obj0 {
    u8 pad000[0x8];
    struct Obj1 *m08;
};

struct Obj1 {
    u8 pad000[0xC];
    s32 m0C;
};

struct Obj2 {
    struct Obj3 *m00;
};

struct Obj3 {
    s16 m00;
};

struct Obj2 *PlanetEntryGetIfIdMaybe_3ec590(struct Obj0 *p0, s32 p1)
{
    struct Obj2 *rv0;
    struct Obj1 * t0;
    s32 t1;
    struct Obj1 * t2;
    s32 t3;
    struct Obj3 * t4;
    s16 t5;

    if (p1 < 0) {
        return (struct Obj2 *)0;
    }
    if (p1 == 1) {
        t0 = p0->m08;
        t1 = p0->m08->m0C;
        rv0 = (struct Obj2 *)t1;
    } else {
        t2 = p0->m08;
        t3 = p0->m08->m0C;
        rv0 = (struct Obj2 *)(t3 + 0x1C);
    }
    if (rv0 == 0) {
        return (struct Obj2 *)0;
    }
    t4 = rv0->m00;
    if (t4 == 0) {
        return (struct Obj2 *)0;
    }
    t5 = rv0->m00->m00;
    if (t5 != p1) {
        return (struct Obj2 *)0;
    }
    return rv0;
}
