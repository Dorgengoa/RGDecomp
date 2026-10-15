#include "types.h"

typedef struct S_002f93b0 {
    u8 pad0[0xE0];
    f32 fE0;
} S_002f93b0;

extern void EvTargetPointObjReset_2f9550(S_002f93b0 *);
extern s32 EvObjInit_2f9cf0(S_002f93b0 *, void *, void *, void *, void *, void *);
extern f32 EvTargetPointObjGetRadius_2f93a0(void *);

s32 EvTargetPointObjInit_2f93b0(S_002f93b0 *a, void *b, void *c, void *d, void *e, void *f)
{
    s32 r;
    EvTargetPointObjReset_2f9550(a);
    if (c == 0) goto zero;
    if (d != 0) goto ok;
zero:
    return 0;
ok:
    r = EvObjInit_2f9cf0(a, b, c, d, e, f);
    if (r == 0) return 0;
    a->fE0 = EvTargetPointObjGetRadius_2f93a0(c);
    return 1;
}
