#include "types.h"

extern void TreasureBoxPoolInit_339290(void *, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00482C40;
extern s32 D_00482C4C;

void TreasureBoxPoolSetup_338980(s32 p0)
{
    TreasureBoxPoolInit_339290(&D_00482C40, p0);
    D_00482C4C = 0;
}
