#include "types.h"

typedef struct P_002285a0 { s32 f0; s32 f4; } P_002285a0;

extern s32 StrPoolIntern_302fd0(void *, s32, s32);

s32 ActReferenceClone_2285a0(P_002285a0 *dst, P_002285a0 *src, s32 c, void *ctx)
{
    s32 t;
    s32 r;
    dst->f0 = 0;
    dst->f4 = 0;
    if (c == 0) goto zero;
    if (ctx == 0) goto zero;
    if (src == 0) goto zero;
    t = src->f0;
    if (t == 0) goto zero;
    if (src->f4 != 0) goto ok;
zero:
    return 0;
ok:
    dst->f0 = t;
    dst->f4 = src->f4;
    r = StrPoolIntern_302fd0(ctx, src->f0, c);
    dst->f0 = r;
    if (r == 0) return 0;
    r = StrPoolIntern_302fd0(ctx, src->f4, c);
    dst->f4 = r;
    return r != 0;
}
