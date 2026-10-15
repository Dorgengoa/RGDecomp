#include "types.h"

extern void ViBufRestartDma_1d3e70(void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_004B3258[];

s32 VideoDecRestartDma_1d4eb0(void)
{
    ViBufRestartDma_1d3e70(D_004B3258);
    return 1;
}
