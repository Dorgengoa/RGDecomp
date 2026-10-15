#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void MesWinSetNumVar_2769a0(s32 p0, s32 p1, s32 p2, s32 p3)
{
    *(s32 *)((u8 *)(p1 << 2) + p0 + 0x1BA0) = p2;
    *(s16 *)((u8 *)(p1 << 1) + p0 + 0x1BF0) = p3;
}
