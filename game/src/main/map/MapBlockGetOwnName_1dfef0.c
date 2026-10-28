/* rgp:protos */
#define RGP_SELF_MapBlockGetOwnName_1dfef0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

int MapBlockGetOwnName_1dfef0(s32 p0)
{
    s32 r0;

    r0 = ((short)MapDataGetId_1e7bd0(p0));
    return MapBlockGetName_1dff20(p0, r0);
}
