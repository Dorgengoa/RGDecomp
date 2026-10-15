#include "types.h"

typedef struct S_002f8f50 {
    u8 pad0[0xE2];
    s16 fE2;
} S_002f8f50;

extern void EvObjAreaFadeReset_2f90a0(S_002f8f50 *);
extern s32 EvObjInit_2f9cf0(S_002f8f50 *, void *, void *, void *, void *, void *);
extern s16 EvObjGetAreaId_2f8f30(void *);

s32 EvObjAreaFadeInit_2f8f50(S_002f8f50 *a, void *b, void *c, void *d, void *e, void *f)
{
    s32 r;
    EvObjAreaFadeReset_2f90a0(a);
    if (c == 0) goto zero;
    if (d != 0) goto ok;
zero:
    return 0;
ok:
    r = EvObjInit_2f9cf0(a, b, c, d, e, f);
    if (r == 0) return 0;
    a->fE2 = EvObjGetAreaId_2f8f30(c);
    return 1;
}
