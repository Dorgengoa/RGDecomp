/* rgp:protos */
#define RGP_SELF_EffectSetId_2e0100 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

s32 EffectSetId_2e0100(u8 *p, s16 *q, short rgp_a2)
{
    s16 v;

    v = *q;
    if (v == 2) goto call;
    if (v == 3) goto call;
    goto done;
call:
    EffectEntriesSetId_2ddf00(p + 0x1674, q, (short)rgp_a2);
done:
    return 0;
}
