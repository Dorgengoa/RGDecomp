#include "types.h"

extern void sceVu0CopyVector(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void EvMapObjPartSetRows_363950(s32 p0, s32 p1)
{
    sceVu0CopyVector((p0 + 0xC0), p1);
    sceVu0CopyVector((p0 + 0xD0), (p1 + 0x10));
    sceVu0CopyVector((p0 + 0xE0), (p1 + 0x20));
}
