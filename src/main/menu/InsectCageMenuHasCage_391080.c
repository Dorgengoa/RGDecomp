#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00483338;

s8 InsectCageMenuHasCage_391080(s32 p0)
{
    s8 t0;

    t0 = *(s8 *)((u8 *)&D_00483338 + p0);
    return t0;
}
