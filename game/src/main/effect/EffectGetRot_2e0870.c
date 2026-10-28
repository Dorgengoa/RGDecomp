/* rgp:protos */
#define RGP_SELF_EffectGetRot_2e0870 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

s32 EffectGetRot_2e0870(u8 *a0, s16 *p, int rgp_a2)
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
    EffectEntryGetRotByIdx_2de030(a0 + 0x1674, (void *)p, (int)rgp_a2);
out:
    return 0;
}
