#include "types.h"

extern s32 ActionPacketClear_3e3e90(void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_0048399C;
extern u8 D_004E9740[];

s32 EventPendingPacketClear_3e25e0(void)
{
    s32 r;

    D_0048399C = 0;
    r = ActionPacketClear_3e3e90(D_004E9740);
    return 1;
}
