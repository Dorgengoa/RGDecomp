#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_004833F8;

void InsectCageMenuDisplayModeSet_388e80(s32 p0)
{
    D_004833F8 = ((p0 + 3) % 3);
}
