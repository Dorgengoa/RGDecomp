#include "types.h"

extern s32 GetGameReqQueue_1f5bc0(void);
extern void GameReqListClear_209f50(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void GameReqQueueClear_1f59e0(void)
{
    s32 r0;

    r0 = GetGameReqQueue_1f5bc0();
    GameReqListClear_209f50(r0);
}
