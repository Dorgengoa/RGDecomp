#include "types.h"

extern void InsectCageMenuDisplayModeSet_388e80(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s8 D_004833F8;

void InsectCageMenuDisplayModePrev_388e60(void)
{
    s8 t0;

    t0 = D_004833F8;
    InsectCageMenuDisplayModeSet_388e80((t0 + -1));
}
