#include "types.h"

typedef struct D_0022f890 {
    s32 f0;
    s32 f4;
    s32 f8;
    s32 fC;
    s32 f10;
    s8 f14;
} D_0022f890;

extern s32 StrPoolIntern_302fd0(void *, s32, s32);

s32 ActInfoLocusClone_22f890(D_0022f890 *out, D_0022f890 *src, s32 p2, void *ctx)
{
    s32 r;
    out->f0 = 0;
    out->f14 = -1;
    out->f4 = 0;
    out->f8 = 0;
    out->fC = 0;
    out->f10 = 0;
    if (p2 == 0) goto zero;
    if (ctx == 0) goto zero;
    if (src == 0) goto zero;
    if (src->f0 != 0) goto ok;
zero:
    return 0;
ok:
    r = StrPoolIntern_302fd0(ctx, src->f0, p2);
    out->f0 = r;
    if (r == 0) return 0;
    out->f14 = src->f14;
    if (src->f4 != 0) {
        r = StrPoolIntern_302fd0(ctx, src->f4, p2);
        out->f4 = r;
        if (r == 0) return 0;
    }
    if (src->f8 != 0) {
        r = StrPoolIntern_302fd0(ctx, src->f8, p2);
        out->f8 = r;
        if (r == 0) return 0;
    }
    r = StrPoolIntern_302fd0(ctx, src->fC, p2);
    out->fC = r;
    if (r == 0) return 0;
    r = StrPoolIntern_302fd0(ctx, src->f10, p2);
    out->f10 = r;
    return r != 0;
}
