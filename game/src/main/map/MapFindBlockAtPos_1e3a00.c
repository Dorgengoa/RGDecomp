/* rgp:protos */
#define RGP_SELF_MapFindBlockAtPos_1e3a00 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 MapFindBlockAtPos_1e3a00(s32 p0, s32 p1, f32 fa0)
{
    s32 v1C;
    s32 r0;
    s32 t0;
    s32 rv3;
    s32 r1;
    s32 rv2;
    s32 t1;

    r0 = (MapFindSmallestBlockAtPos_1e3b50(p0, 0, &v1C, p1, fa0), (s32)0);
    t0 = v1C;
    if (t0 == 0) {
        rv3 = 0;
    } else {
        r1 = ((signed char)MapDataGetType_1e7c00(t0));
        if (r1 != 4) {
            rv2 = 0;
        } else {
            t1 = v1C;
            rv2 = t1;
        }
        rv3 = rv2;
    }
    return rv3;
}
