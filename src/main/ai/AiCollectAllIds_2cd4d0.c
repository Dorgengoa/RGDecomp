#include "types.h"

/* `n = 0; n += f(); n += g(...)` -- the daddu $16,$0,$0 in the delay slot
   followed by addu $16,$16,$2 is the accumulator form, not a plain assign. */

extern s32 PartyCollectLiveMemberIds_2cd6e0(s32 *);
extern s32 AiCollectTargetIds_2cd530(s32 *, s32);

s32 AiCollectAllIds_2cd4d0(s32 *buf, s32 cap)
{
    s32 n;

    n = 0;
    n += PartyCollectLiveMemberIds_2cd6e0(buf);
    n += AiCollectTargetIds_2cd530(buf + n, cap - n);
    return n;
}
