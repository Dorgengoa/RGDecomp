#include "types.h"

extern void * AbilityDataGetKind0Rec_3f5db0(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0xC];
    s32 m0C;
};

s32 AbilityDataGetAbltName_3f5d20(s32 p0)
{
    struct Obj0 *r0;
    s32 t0;

    r0 = AbilityDataGetKind0Rec_3f5db0(p0);
    if (r0 != 0) {
        t0 = r0->m0C;
        return t0;
    }
    return 0;
}
