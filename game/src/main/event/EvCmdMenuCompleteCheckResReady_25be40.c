/* rgp:protos */
#define RGP_SELF_EvCmdMenuCompleteCheckResReady_25be40 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 EvCmdMenuCompleteCheckResReady_25be40(s32 p0)
{
    s32 r0;
    s32 r1;

    r0 = ((unsigned char)CompleteCheckResReady_203470());
    r1 = (ScriptSetRefInt_26a1e0(p0, (r0 & 0xFF)), (s32)0);
    return 1;
}
