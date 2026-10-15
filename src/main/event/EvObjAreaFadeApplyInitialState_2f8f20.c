#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

struct Obj0;

struct Obj0 {
    u8 pad000[0xE0];
    s16 mE0;
    u8 pad0E2[0x2];
    s32 mE4;
};

void EvObjAreaFadeApplyInitialState_2f8f20(struct Obj0 *p0)
{
    p0->mE0 = 0;
    p0->mE4 = 0x3F800000;
}
