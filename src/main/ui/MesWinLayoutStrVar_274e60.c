#include "types.h"

extern void MesWinLayoutText_274e70(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void MesWinLayoutStrVar_274e60(s32 p0, s32 p1)
{
    MesWinLayoutText_274e70(p0, ((p0 + (p1 << 5)) + 0x195D));
}
