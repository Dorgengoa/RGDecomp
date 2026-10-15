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
    u8 pad000[0x7EC];
    f32 m7EC;
};

s32 CageRecIsPlaced_3d0d20(struct Obj0 *p0)
{
    struct Obj1 * t0;
    s32 rv1;
    f32 t1;
    s32 rv0;

    t0 = p0->m18;
    if (t0 == 0) {
        rv1 = 0;
    } else {
        t1 = p0->m18->m7EC;
        rv0 = 1;
        if (t1 < 0.0f) {
            rv0 = 0;
        }
        rv1 = rv0;
    }
    return rv1;
}
