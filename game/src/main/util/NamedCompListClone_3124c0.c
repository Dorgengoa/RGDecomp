/* rgp:protos */
#define RGP_SELF_NamedCompListClone_3124c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct D_003124c0 {
    s32 f0;
    void *f4;
    s32 f8;
} D_003124c0;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern void *memcpy(void *, void *, s32);

s32 NamedCompListClone_3124c0(D_003124c0 *out, void *src, s32 ctx)
{
    s32 n;
    void *p;
    s32 r;
    void *q;
    NamedCompListClear_312630(out);
    if (src == 0) goto zero;
    if (ctx != 0) goto ok;
zero:
    return 0;
ok:
    r = ((s32)MemStackStrDup_14cff0(NamedCompListGetName_3124b0(src), ctx));
    out->f0 = r;
    if (r == 0) return 0;
    if (NamedCompListGetEntries_3124a0(src) == 0) goto one;
    out->f8 = NamedCompListGetCount_312490(src);
    n = out->f8;
    p = MemStackNew_14e1b0(20 * n + 0x10, ctx);
    q = ConstructNewArray_100710(p, 0, 0, 0x14, n);
    out->f4 = q;
    if (q == 0) return 0;
    memcpy(out->f4, NamedCompListGetEntries_3124a0(src), out->f8 * 20);
one:
    return 1;
}
