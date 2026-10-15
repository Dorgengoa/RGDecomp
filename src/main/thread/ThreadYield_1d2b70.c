#include "types.h"

extern void RotateThreadReadyQueue(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_0047DF30;

void ThreadYield_1d2b70(void)
{
    s32 t0;

    t0 = D_0047DF30;
    RotateThreadReadyQueue(t0);
}
