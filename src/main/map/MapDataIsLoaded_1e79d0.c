#include "types.h"

extern s32 MapDataGetState_1e7a00(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

u8 MapDataIsLoaded_1e79d0(s32 p0)
{
    s32 r;

    r = MapDataGetState_1e7a00(p0);
    return (r == 2);
}
