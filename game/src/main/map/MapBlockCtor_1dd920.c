/* rgp:protos */
#define RGP_SELF_MapBlockCtor_1dd920 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 MapBlockCtor_1dd920(s32 p0)
{
    s32 r5;

    MapDataInit_1e7c50(p0);
    Nop_1ed0b0();
    MapBlockBoxListInit_1e0580((p0 + 0x54));
    Nop_1ed090();
    AreaBoxInit_1e01f0((p0 + 0x74));
    r5 = (MapBlockInit_1e0100(p0), (s32)0);
    return p0;
}
