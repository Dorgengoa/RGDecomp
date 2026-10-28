/* rgp:protos */
#define RGP_SELF_GameReqQueuePushFront_1f5ab0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void GameReqQueuePushFront_1f5ab0(s32 p0, s32 p1)
{
    s32 r0;

    r0 = ((s32)GetGameReqQueue_1f5bc0());
    GameReqListPushFront_20a240(r0, p0, p1);
}
