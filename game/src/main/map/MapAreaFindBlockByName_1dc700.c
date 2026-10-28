/* rgp:protos */
#define RGP_SELF_MapAreaFindBlockByName_1dc700 1
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

s32 MapAreaFindBlockByName_1dc700(s32 p0, s32 p1)
{
    s32 r0;
    s32 rv3;
    s32 r1;
    s32 r2;

    r0 = ((unsigned char)MapIdIndexHasNames_1ddbc0((p0 + 0x10C)));
    rv3 = r2;
    if (r0 != 0) {
        r1 = MapIdIndexFindByName_1dda20((p0 + 0x10C), p1);
        rv3 = r1;
    } else {
        r2 = ((s32)MapRecTableFindBlockByName_1dd270((p0 + 0x54), p1));
        rv3 = r2;
    }
    return rv3;
}
