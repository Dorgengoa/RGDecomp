#include "types.h"

extern void SaveSetMode_375a10(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_004831D0;

void SaveMgrSetMode_37b9e0(s32 p0)
{
    s32 t0;

    t0 = D_004831D0;
    if (t0 != 0) {
        SaveSetMode_375a10(t0, p0);
    }
}
