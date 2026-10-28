/* rgp:protos */
#define RGP_SELF_TaskTableSetEnabledByName_1f5500 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 TaskTableSetEnabledByName_1f5500(s32 p0, s32 p1, s32 p2)
{
    s32 r0;

    r0 = ((s32)TaskTableFindByName_1f55d0(p0, p2));
    if (r0 != 0) {
        TaskSetFlag_1f5750(r0, p1, 0);
    }
}
