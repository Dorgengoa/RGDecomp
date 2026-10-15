#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern const f32 D_0045B078;

struct Obj0;

struct Obj0 {
    u8 m00;
    u8 pad001[0x3];
    f32 m04;
};

f32 StatusEntryGetTime_3a60f0(struct Obj0 *p0)
{
    u8 t0;
    f32 t1;
    f32 t2;

    t0 = p0->m00;
    if (t0 == 0) {
        return 0.0f;
    }
    t1 = D_0045B078;
    t2 = p0->m04;
    return (t2 / (2.0f * t1));
}
