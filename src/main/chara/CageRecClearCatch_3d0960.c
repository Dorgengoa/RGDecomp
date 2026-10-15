#include "types.h"



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
    u8 pad006[0x6];
    s32 m0C;
    u8 pad010[0x7DC];
    f32 m7EC;
};

s32 CageRecClearCatch_3d0960(struct Obj0 *p0)
{
    struct Obj1 * t0;
    s16 t1;
    struct Obj1 * t2;
    struct Obj1 * t3;
    struct Obj1 * t4;
    f32 t5;

    t0 = p0->m18;
    t1 = p0->m18->m04;
    if (t1 <= 0) {
        return 0;
    }
    p0->m18->m02 = -1;
    t2 = p0->m18;
    p0->m18->m04 = -1;
    t3 = p0->m18;
    p0->m18->m0C = 0;
    t4 = p0->m18;
    t5 = p0->m18->m7EC;
    if (t5 > 0.0f) {
        p0->m18->m7EC = 0.0f;
    }
    return 1;
}
