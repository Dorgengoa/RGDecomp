/* rgp:protos */
#define RGP_SELF_TaskStepObject1_2cfef0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void TaskStepObject1_2cfef0(void)
{
    s32 r0;

    r0 = ((s32)GetEventObjMgr_2d1960());
    EventObjMgrPreUpdateAllMaybe_2e8440(r0);
}
