#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 EventTimerClear_3c06d0(s32 p0, s32 p1)
{
    *(s32 *)((u8 *)(p1 << 2) + p0 + 0x4C58) = 0;
    *(s32 *)((u8 *)(p1 << 2) + p0 + 0x4C60) = 0;
    return 1;
}
