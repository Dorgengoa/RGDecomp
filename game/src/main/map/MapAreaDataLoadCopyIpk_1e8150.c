/* rgp:protos */
#define RGP_SELF_MapAreaDataLoadCopyIpk_1e8150 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 MapAreaDataLoadCopyIpk_1e8150(s32 p0)
{
    s32 r0;
    s32 r1;

    r0 = MapAreaDataCopyFileBuf_1e81b0(p0, 0, (p0 + 0x16CC));
    if (r0 == 0) {
        return r0;
    }
    r1 = (LoaderReleaseHandle_1ccb70(p0), (s32)0);
    return r0;
}
