#include "types.h"

extern void MotionListSelectByIndexAll_172030(s32, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void ModelObjPlayMotionByIndex_186790(s32 p0, s32 p1, s32 p2)
{
    MotionListSelectByIndexAll_172030((p0 + 0x1F0), p1, p2);
}
