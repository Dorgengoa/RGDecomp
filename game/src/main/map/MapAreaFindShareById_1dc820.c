/* rgp:protos */
#define RGP_SELF_MapAreaFindShareById_1dc820 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 MapAreaFindShareById_1dc820(s32 p0, s32 p1)
{
    s32 r0;
    s32 rv3;
    s32 r1;
    s32 r2;

    r0 = ((unsigned char)MapIdIndexHasIds_1ddbd0((p0 + 0xFC)));
    rv3 = r2;
    if (r0 != 0) {
        r1 = MapIdIndexFind_1ddaf0((p0 + 0xFC), p1);
        rv3 = r1;
    } else {
        r2 = ((s32)MapRecTableFindShareById_1dd4a0((p0 + 0x54), p1));
        rv3 = r2;
    }
    return rv3;
}
