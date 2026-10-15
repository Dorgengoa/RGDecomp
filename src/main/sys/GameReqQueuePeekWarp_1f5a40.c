#include "types.h"

extern s32 GetGameReqQueue_1f5bc0(void);
extern void GameReqListPeekWarp_20a160(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void GameReqQueuePeekWarp_1f5a40(s32 p0)
{
    s32 r0;

    r0 = GetGameReqQueue_1f5bc0();
    GameReqListPeekWarp_20a160(r0, p0);
}
