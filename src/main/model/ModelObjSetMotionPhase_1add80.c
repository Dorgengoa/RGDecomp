#include "types.h"

extern void MotionListSetPhase_171f50(s32, f32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void ModelObjSetMotionPhase_1add80(s32 p0, f32 fa0)
{
    MotionListSetPhase_171f50((p0 + 0x1F0), fa0);
}
