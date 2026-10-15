#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_004812C8;

s32 MapCfgLodEnd_18c630(void)
{
    D_004812C8 = (D_004812C8 + 1);
    return 1;
}
