#include "types.h"

extern s32 MesWinGetItemSlot_2746e0(s32, s32);
extern void MesItemNameMeasureWidth_274710(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void MesWinMeasureItemSlot_2746b0(s32 p0, s32 p1)
{
    s32 r0;

    r0 = MesWinGetItemSlot_2746e0(p0, p1);
    MesItemNameMeasureWidth_274710(p0, r0);
}
