/* rgp:protos */
#define RGP_SELF_MapAreaCallScript_1e4370 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 MapAreaCallScript_1e4370(s32 p0, s32 p1, s32 p2)
{
    s32 r0;
    s32 r1;

    r0 = ((s32)MapFindAreaSlotByName_1e4c30(p0, p1));
    if (r0 != 0) {
        r1 = MapScriptCall_1e99d0(r0, p2);
        return r1;
    }
    return -1;
}
