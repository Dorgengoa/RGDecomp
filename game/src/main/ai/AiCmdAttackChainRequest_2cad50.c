/* rgp:protos */
#define RGP_SELF_AiCmdAttackChainRequest_2cad50 1
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

s32 AiCmdAttackChainRequest_2cad50(s32 p0, s32 p1)
{
    s32 rv5;
    s32 r0;
    s32 r1;
    s32 r2;
    s32 r3;
    s32 r4;

    rv5 = 1;
    if (p1 != 1) {
        rv5 = 0;
    } else {
        r0 = ((s32)GetGameData_1fede0());
        r1 = ScriptSlotGetInt_2cc9c0(p0);
        r2 = (GameFlowResetChainReq_285f60(), (s32)0);
        r3 = (GameFlowSetChainCharaId_285f10(r1), (s32)0);
        r4 = GameReqQueuePushBack_1f5b50(9, -1);
        rv5 = 1;
    }
    return rv5;
}
