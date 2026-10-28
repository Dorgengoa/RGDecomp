/* rgp:protos */
#define RGP_SELF_EvCmdTreasureBoxTriggerCurrent_25e5b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 EvCmdTreasureBoxTriggerCurrent_25e5b0(void)
{
    s32 r0;
    s32 r1;
    s32 r2;
    s32 r3;
    s32 r4;

    r0 = ((s32)GetTreasureBoxPool_3389b0());
    r1 = GameFlowGetTreasureBoxId_285ec0();
    r2 = TreasureBoxPoolFindById_339150(r0, r1);
    if (r2 == 0) {
        return 0;
    }
    r3 = TreasureBoxTriggerEncounter_33a620(r2);
    r4 = GameReqQueuePushBack_1f5b50(7, 2);
    return 1;
}
