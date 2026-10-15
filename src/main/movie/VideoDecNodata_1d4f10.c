#include "types.h"

extern void ThreadYield_1d2b70(void);
extern void ViBufAddDma_1d4240(void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_004B3258[];

s32 VideoDecNodata_1d4f10(void)
{
    ThreadYield_1d2b70();
    ViBufAddDma_1d4240(D_004B3258);
    return 1;
}
