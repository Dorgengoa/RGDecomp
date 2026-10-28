/* rgp:protos */
#define RGP_SELF_InsectInfoIconSetUvByIdMaybe_3929b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void InsectInfoIconSetUvByIdMaybe_3929b0(s32 p0, s32 p1, s32 p2, s32 p3, s32 p4, s32 p5)
{
    s32 r0;

    r0 = ((s32)UiFindWidget_290460(p1, (p2 & 0xFFFF)));
    UiIconSetUvByKindMaybe_3928d0(p0, r0, p3, p4, p5);
}
