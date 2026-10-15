#include "types.h"

extern s32 GetGameReqQueue_1f5bc0(void);
extern void GameReqListPushWarp_20a340(s32, s32, s32, s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void GameReqQueuePushWarp_1f5af0(s32 p0, s32 p1, s32 p2, s32 p3)
{
    s32 r0;

    r0 = GetGameReqQueue_1f5bc0();
    GameReqListPushWarp_20a340(r0, p0, p1, p2, p3);
}
