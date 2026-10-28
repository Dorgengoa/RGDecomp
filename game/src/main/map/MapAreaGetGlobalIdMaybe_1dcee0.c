/* rgp:protos */
#define RGP_SELF_MapAreaGetGlobalIdMaybe_1dcee0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 MapAreaGetGlobalIdMaybe_1dcee0(s32 p0)
{
    s32 r0;
    s32 rv2;
    s32 r1;

    r0 = ((short)MapDataGetId_1e7bd0(p0));
    rv2 = (r1 + 0x4E20);
    if (r0 < 0) {
        rv2 = -1;
    } else {
        r1 = ((short)MapAreaGetGroundTypeMaybe_1dceb0(p0));
        rv2 = (r1 + 0x4E20);
    }
    return rv2;
}
