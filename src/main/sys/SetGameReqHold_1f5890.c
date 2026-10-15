#include "types.h"

/* Decoded by the pass-6 symbolic executor (build/w1_gen6.py):
   stores in listing order, return value read off $v0 at the jr.
   Field types are by ACCESS WIDTH; the build arbitrates. */

extern u8 D_004819A8;

void SetGameReqHold_1f5890(void)
{
    D_004819A8 = 1;
}
