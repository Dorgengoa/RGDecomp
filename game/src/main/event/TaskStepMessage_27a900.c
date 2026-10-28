/* rgp:protos */
#define RGP_SELF_TaskStepMessage_27a900 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void TaskStepMessage_27a900(void)
{
    s32 r0;

    r0 = ((s32)GetMesMgr_277e90());
    MesMgrUpdateAll_277ac0(r0);
}
