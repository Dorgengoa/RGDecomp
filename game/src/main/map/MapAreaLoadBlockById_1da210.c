/* rgp:protos */
#define RGP_SELF_MapAreaLoadBlockById_1da210 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

int MapAreaLoadBlockById_1da210(s32 p0, s32 p1, s32 p2, s32 p3)
{
    s32 r0;

    r0 = MapAreaFindBlockById_1dc760(p0, p2);
    return MapAreaLoadBlock_1da130(p0, p1, r0, p3);
}
