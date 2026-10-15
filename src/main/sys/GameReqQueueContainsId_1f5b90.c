#include "types.h"

extern s32 GetGameReqQueue_1f5bc0(void);
extern s32 GameReqListContainsId_20a4c0(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 GameReqQueueContainsId_1f5b90(s32 p0)
{
    s32 r0;
    s32 r1;

    r0 = GetGameReqQueue_1f5bc0();
    r1 = GameReqListContainsId_20a4c0(r0, p0);
    return r1;
}
