#include "types.h"

extern s32 scePrintf_119288(void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_00457C30[];

s32 sceCdChgSys_12ae70(void)
{
    s32 r;

    r = scePrintf_119288(D_00457C30);
    return 2;
}
