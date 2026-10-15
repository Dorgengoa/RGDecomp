#include "types.h"

extern s32 PadStateInit_184f90(void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0xB4];
    s32 mB4;
    s32 mB8;
};

struct Obj0 *PadCtor_185040(struct Obj0 *p0)
{
    s32 r0;

    r0 = PadStateInit_184f90(p0);
    p0->mB8 = -1;
    p0->mB4 = -1;
    return p0;
}
