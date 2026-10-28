/* rgp:protos */
#define RGP_SELF_MapGetAreaLightSetAtPos_1e5490 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

int MapGetAreaLightSetAtPos_1e5490(s32 p0, s32 p1, s32 p2)
{
    s32 r0;

    r0 = MapResolveAreaLightRefAtPos_1e5640(p0, p1);
    return MapAreaGetLightSetOrDefault_1e5430(p0, r0, p2);
}
