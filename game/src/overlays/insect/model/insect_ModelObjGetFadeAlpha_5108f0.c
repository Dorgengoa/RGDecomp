/* rgp:protos */
#define RGP_SELF_insect_ModelObjGetFadeAlpha_5108f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x005108F0 -- pass-28 unnamed-listing conversion.  Tail-call thunk
 * WITH a delay-slot fixup (`addiu $4, $4, 0x1C8`), so unlike the empty-slot
 * class the callee's arity IS read here: func_186DC0's own listing touches
 * $4 and nothing else and returns in $f0. */
/*rgp*/

f32 insect_ModelObjGetFadeAlpha_5108f0(u8 *p)
{
    return FadeGetAlpha_186dc0(p + 0x1C8);
}
