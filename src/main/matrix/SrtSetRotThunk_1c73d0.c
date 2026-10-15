#include "types.h"

extern void SrtSetRot_1c73d0(s32, f32, f32, f32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void SrtSetRotThunk_1c73d0(s32 p0, f32 fa0, f32 fa1, f32 fa2)
{
    SrtSetRot_1c73d0(p0, fa0, fa1, fa2);
}
