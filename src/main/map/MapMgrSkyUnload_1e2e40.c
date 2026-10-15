#include "types.h"

extern s32 MapSkyUnload_1e6190(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 MapMgrSkyUnload_1e2e40(s32 p0)
{
    s32 r;

    r = MapSkyUnload_1e6190((p0 + 0xE0));
    return 1;
}
