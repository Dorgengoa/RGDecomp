/* rgp:protos */
#define RGP_SELF_InsectCageLoadMap_389e70 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_00463F50[];
extern s32 D_0047FC80;
extern u8 D_004E9380[];

s32 InsectCageLoadMap_389e70(s32 p0)
{
    s32 r0;
    s32 rv2;
    s32 t0;
    s32 r1;

    r0 = ((s32)GetMapMgr_201a90());
    rv2 = 1;
    if (r0 == 0) {
        rv2 = 0;
    } else {
        t0 = *(s32 *)((u8 *)&D_0047FC80 + (p0 << 2));
        r1 = MapMgrAuxAreaLoad_1e2fc0(r0, D_004E9380, D_00463F50, t0);
        rv2 = 1;
    }
    return rv2;
}
