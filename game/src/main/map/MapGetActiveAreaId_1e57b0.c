/* rgp:protos */
#define RGP_SELF_MapGetActiveAreaId_1e57b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 MapGetActiveAreaId_1e57b0(s32 p0)
{
    s32 r0;
    s32 r1;

    r0 = MapGetActiveArea_1e56e0(p0);
    if (r0 != 0) {
        r1 = ((short)MapDataGetId_1e7bd0(r0));
        return r1;
    }
    return -1;
}
