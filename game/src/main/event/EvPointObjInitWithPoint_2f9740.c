/* rgp:protos */
#define RGP_SELF_EvPointObjInitWithPoint_2f9740 1
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

void EvPointObjInitWithPoint_2f9740(s32 p0, s32 p1, s32 p2, f32 fa0, f32 fa1, f32 fa2, f32 fa3)
{
    EvObjResetThunk_2f9eb0((int)p0);
    EvObjInitWithKey_2f9e60(p0, p1, p2);
    TargetRefSetPoint_2e6710((p0 + 0xA0), fa0, fa1, fa2, fa3);
}
