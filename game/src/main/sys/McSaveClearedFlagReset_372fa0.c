/* rgp:protos */
#define RGP_SELF_McSaveClearedFlagReset_372fa0 1
#include "port/game_protos.h"
#line 1
#include "types.h"



/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00483168;

void McSaveClearedFlagReset_372fa0(s32 p0)
{
    *(u8 *)((u8 *)&D_00483168 + p0) = 0;
}
