#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s16 MesWinGetCharX_274d90(s32 p0, s32 p1)
{
    s16 t0;

    t0 = *(s16 *)((u8 *)(p1 << 3) + p0 + 0xC6);
    return t0;
}
