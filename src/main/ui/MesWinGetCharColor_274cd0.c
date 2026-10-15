#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

u8 MesWinGetCharColor_274cd0(s32 p0, s32 p1)
{
    u8 t0;

    t0 = *(u8 *)((u8 *)(p1 << 3) + p0 + 0xCB);
    return t0;
}
