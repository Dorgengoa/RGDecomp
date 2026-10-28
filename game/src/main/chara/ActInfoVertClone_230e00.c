/* rgp:protos */
#define RGP_SELF_ActInfoVertClone_230e00 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct D_00230e00 {
    s32 f0;
    s32 f4;
    s32 f8;
    f32 fC;
    f32 f10;
    f32 f14;
} D_00230e00;

/*rgp*/

s32 ActInfoVertClone_230e00(D_00230e00 *out, D_00230e00 *src, s32 p2, void *ctx)
{
    s32 r;
    out->f0 = 0;
    out->f8 = -1;
    out->f4 = 0;
    out->fC = 0.0f;
    out->f10 = 0.0f;
    out->f14 = 0.0f;
    if (p2 == 0) goto zero;
    if (ctx == 0) goto zero;
    if (src == 0) goto zero;
    if (src->f0 != 0) goto ok;
zero:
    return 0;
ok:
    out->f8 = src->f8;
    out->fC = src->fC;
    out->f10 = src->f10;
    out->f14 = src->f14;
    if (src->f4 != 0) {
        r = ((s32)StrPoolIntern_302fd0(ctx, src->f4, p2));
        out->f4 = r;
        if (r == 0) return 0;
    }
    r = ((s32)StrPoolIntern_302fd0(ctx, src->f0, p2));
    out->f0 = r;
    if (r == 0) return 0;
    return 1;
}
