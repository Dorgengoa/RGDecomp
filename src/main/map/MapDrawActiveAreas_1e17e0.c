#include "types.h"

extern s32 MapSlotsCollectActiveAreasMaybe_1e3d70(s32, void *, s32);
extern s32 MapAreasDrawLit_1e1830(s32, s32, void *, s32);
typedef unsigned __int128 u128;

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 MapDrawActiveAreas_1e17e0(s32 p0, s32 p1)
{
    u128 v30[5];
    s32 r0;
    s32 r1;

    r0 = MapSlotsCollectActiveAreasMaybe_1e3d70(p0, v30, 0x14);
    r1 = MapAreasDrawLit_1e1830(p0, p1, v30, r0);
    return r1;
}
