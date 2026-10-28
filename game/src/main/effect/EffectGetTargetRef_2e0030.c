/* rgp:protos */
#define RGP_SELF_EffectGetTargetRef_2e0030 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

s32 EffectGetTargetRef_2e0030(u8 *p, s16 *q)
{
    s16 v;
    s32 r;

    v = *q;
    if (v == 2) goto call;
    if (v == 3) goto call;
    goto zero;
call:
    r = EffectEntriesGetNodeTargetRef_2dd930(p + 0x1674, q);
    if (r != 0) {
        return r;
    }
zero:
    return 0;
}
