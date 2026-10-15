#include "types.h"

extern s32 GetGameReqQueue_1f5bc0(void);
extern s32 GameReqListPeek_20a1e0(s32, void *, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

s32 GameReqQueuePeekHead_1f5a70(s32 p0)
{
    s32 v2C;
    s32 r0;
    s32 r1;
    s32 t0;

    r0 = GetGameReqQueue_1f5bc0();
    r1 = GameReqListPeek_20a1e0(r0, &v2C, p0);
    if (r1 != 0) {
        t0 = v2C;
        return t0;
    }
    return -1;
}
