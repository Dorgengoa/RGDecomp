/* rgp:protos */
#define RGP_SELF_EffectGetPos_2e08c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

s32 EffectGetPos_2e08c0(u8 *a0, s16 *p, int rgp_a2)
{
    s32 v;

    v = *p;
    if (v == 1) {
        goto out;
    }
    if (v == 2) {
        goto call;
    }
    if (v != 3) {
        goto out;
    }
call:
    EffectEntryGetPosByIdx_2de080(a0 + 0x1674, (void *)p, (int)rgp_a2);
out:
    return 0;
}
