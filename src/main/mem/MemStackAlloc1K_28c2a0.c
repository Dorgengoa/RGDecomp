#include "types.h"

extern void MemStackNew_14e0b0(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 MemStackAlloc1K_28c2a0(s32 p0)
{
    if (p0 != 0) {
        MemStackNew_14e0b0(0x400, p0);
        return;
    }
    return 0;
}
