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
    u8 pad000[0x238];
    struct Obj1 *m238;
};

struct Obj1 {
    u8 pad000[0x10];
    struct Obj3 *m10;
    u8 pad014[0x4];
    struct Obj2 *m18;
};

struct Obj2 {
    u8 pad000[0x10];
    s16 m10;
};

struct Obj3 {
    u8 pad000[0x10];
    s16 m10;
};

s32 CharaSysGetEncounterSpawnParamMaybe_3a36a0(struct Obj0 *p0)
{
    struct Obj1 * t0;
    struct Obj2 * t1;
    s16 t2;
    struct Obj3 * t3;
    s16 t4;

    t0 = p0->m238;
    t1 = p0->m238->m18;
    if (t1 != 0) {
        t2 = p0->m238->m18->m10;
        return (s32)t2;
    }
    t3 = p0->m238->m10;
    if (t3 != 0) {
        t4 = p0->m238->m10->m10;
        return (s32)t4;
    }
    return -1;
}
