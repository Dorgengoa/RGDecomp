#include "types.h"

extern s32 memset(s32, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 SaveSlotTextBufCtor_37bd60(s32 p0)
{
    s32 r0;

    r0 = memset(p0, 0, 0x100);
    return p0;
}
