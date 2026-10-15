#include "types.h"

extern void EffectEntriesSetId_2ddf00(void *, s16 *);

s32 EffectSetId_2e0100(u8 *p, s16 *q)
{
    s16 v;

    v = *q;
    if (v == 2) goto call;
    if (v == 3) goto call;
    goto done;
call:
    EffectEntriesSetId_2ddf00(p + 0x1674, q);
done:
    return 0;
}
