/* rgp:protos */
#define RGP_SELF_GameReqQueuePushBack_1f5b50 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

int GameReqQueuePushBack_1f5b50(s32 p0, s32 p1)
{
    s32 r0;

    r0 = ((s32)GetGameReqQueue_1f5bc0());
    return GameReqListPushBack_20a410(r0, p0, p1);
}
