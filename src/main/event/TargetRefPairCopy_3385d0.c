#include "types.h"

typedef struct S_003385d0 {
    u8 pad0[0x60];
    void *f60;
} S_003385d0;

extern void TargetRefPairReset_338730(S_003385d0 *);
extern void *TargetRefPairGetRec_338680(void *);
extern void *TargetRefPairGetFirst_3386a0(void *);
extern void *TargetRefPairGetSecond_338690(void *);
extern s32 TargetRefCopy_2e7140(void *, void *, void *);

s32 TargetRefPairCopy_3385d0(S_003385d0 *a, void *b, void *c)
{
    void *r;
    TargetRefPairReset_338730(a);
    if (b == 0) goto zero;
    if (c != 0) goto ok;
zero:
    return 0;
ok:
    r = TargetRefPairGetRec_338680(b);
    a->f60 = r;
    if (r != 0) goto ok2;
    return 0;
ok2:
    r = TargetRefPairGetFirst_3386a0(b);
    if (TargetRefCopy_2e7140(a, r, c) == 0) return 0;
    r = TargetRefPairGetSecond_338690(b);
    return TargetRefCopy_2e7140((u8 *)a + 0x30, r, c);
}
