#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00483340;

s32 InsectCageMenuGetCageItem_391060(s32 p0)
{
    s32 t0;

    t0 = *(s32 *)((u8 *)&D_00483340 + (p0 << 2));
    return t0;
}
