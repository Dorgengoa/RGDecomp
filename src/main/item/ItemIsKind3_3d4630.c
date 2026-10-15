#include "types.h"

extern s32 ItemDefIsKind3_40e350(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0x10];
    s32 m10;
};

s32 ItemIsKind3_3d4630(struct Obj0 *p0)
{
    s32 t0;
    s32 r0;

    t0 = p0->m10;
    if (t0 != 0) {
        r0 = ItemDefIsKind3_40e350(t0);
        return r0;
    }
    return 0;
}
