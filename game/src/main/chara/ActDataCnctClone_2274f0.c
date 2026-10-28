/* rgp:protos */
#define RGP_SELF_ActDataCnctClone_2274f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct { s32 a; f32 b; } T_002274f0;

s32 ActDataCnctClone_2274f0(T_002274f0 *out, T_002274f0 *src, s32 c6, s32 c7)
{
    s32 t;

    out->a = 0;
    out->b = 1.0f;
    if (c6 == 0) goto fail;
    if (c7 == 0) goto fail;
    if (src == 0) goto fail;
    t = src->a;
    if (t != 0) goto ok;
fail:
    return 0;
ok:
    out->a = t;
    out->b = src->b;
    return 1;
}
