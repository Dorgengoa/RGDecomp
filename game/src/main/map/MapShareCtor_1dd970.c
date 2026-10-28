/* rgp:protos */
#define RGP_SELF_MapShareCtor_1dd970 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 MapShareCtor_1dd970(s32 p0)
{
    s32 r3;

    MapDataInit_1e7c50(p0);
    Nop_1ed0b0();
    Nop_1ed090();
    r3 = (MapShareInit_1ed040(p0), (s32)0);
    return p0;
}
