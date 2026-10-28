/* rgp:protos */
#define RGP_SELF_CdDiskWatchSetEnabled_17fe80 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_0048121C;

s32 CdDiskWatchSetEnabled_17fe80(s32 p0)
{
    s32 old0;

    old0 = D_0048121C;
    D_0048121C = p0;
    return old0;
}
