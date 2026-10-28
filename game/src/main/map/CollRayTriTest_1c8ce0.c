/* rgp:protos */
#define RGP_SELF_CollRayTriTest_1c8ce0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
typedef rg_u128 u128;

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

float CollRayTriTest_1c8ce0(s32 p0, s32 p1, s32 p2, s32 p3, s32 p4)
{
    u128 v60;

    TriNormal_1cb970(&v60, p0, p1, p2);
    return RayTriIntersectT_1c8d60(p0, p1, p2, &v60, p3, p4);
}
