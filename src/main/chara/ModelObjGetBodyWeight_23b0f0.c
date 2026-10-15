#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x4D0];
    f32 m4D0;
};

f32 ModelObjGetBodyWeight_23b0f0(struct Obj0 *p0)
{
    f32 t0;

    if (p0 != 0) {
        t0 = p0->m4D0;
        return t0;
    }
    return 0.0f;
}
