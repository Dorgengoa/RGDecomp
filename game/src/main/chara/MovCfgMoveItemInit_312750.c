/* rgp:protos */
#define RGP_SELF_MovCfgMoveItemInit_312750 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void MovCfgMoveItemInit_312750(s32 p0, f32 fa0, f32 fa1, f32 fa2, f32 fa3, f32 fa4)
{
    ActionWindowSet_228550(p0, fa0, fa1);
    Vec3Set_3127b0((p0 + 8), fa2, fa3, fa4);
}
