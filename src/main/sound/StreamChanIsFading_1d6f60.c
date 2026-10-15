#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x90];
    f32 m90;
};

s32 StreamChanIsFading_1d6f60(struct Obj0 *p0)
{
    f32 t0;

    t0 = p0->m90;
    if (0.0f == t0) {
        return 0;
    }
    return 1;
}
