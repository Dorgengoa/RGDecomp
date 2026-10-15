#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x1E4];
    f32 m1E4;
};

f32 CharaMeterGet_3b0630(struct Obj0 *p0)
{
    f32 t0;

    t0 = p0->m1E4;
    return t0;
}
