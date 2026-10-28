/* rgp:protos */
#define RGP_SELF_MapAreaCtor_201ba0 1
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

s32 MapAreaCtor_201ba0(s32 p0)
{
    s32 r2;

    MapDataInit_1e7c50(p0);
    Nop_1ed0b0();
    r2 = (Nop_1ed090(), (s32)0);
    return p0;
}
