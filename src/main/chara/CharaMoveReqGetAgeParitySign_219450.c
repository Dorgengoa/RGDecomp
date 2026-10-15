#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x14];
    s32 m14;
};

f32 CharaMoveReqGetAgeParitySign_219450(struct Obj0 *p0)
{
    s32 t0;

    t0 = p0->m14;
    if ((t0 & 1) != 0) {
        return -1.0f;
    }
    return 1.0f;
}
