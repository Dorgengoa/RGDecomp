#include "types.h"

typedef struct S_002e6d70 {
    u8 pad0[2];
    s16 f2;
    s32 f4;
} S_002e6d70;

typedef struct R_002e6d70 {
    u8 pad0[0x2C];
    s32 f2C;
} R_002e6d70;

extern s32 TargetRefGetKind_2e7130(S_002e6d70 *);
extern void *GetMapMgr_201a90(void);
extern R_002e6d70 *MapSlotsFindActiveById_1e4870(void *, s16, s32);

s32 TargetRefAreaHasFlag80_2e6d70(S_002e6d70 *self)
{
    s32 t;
    s32 x;
    R_002e6d70 *r;
    t = TargetRefGetKind_2e7130(self);
    if (t == 13) goto zeroA;
    if (t == 1) goto zeroA;
    x = self->f4;
    goto n0;
zeroA:
    return 0;
n0:
    if (x != 0) goto n1;
    return 0;
n1:
    t = TargetRefGetKind_2e7130(self);
    if (t == 9) goto n2;
    if (t == 8) goto n2;
    if (t == 7) goto n2;
    if (t == 6) goto n2;
    return 0;
n2:
    r = MapSlotsFindActiveById_1e4870(GetMapMgr_201a90(), self->f2, 0);
    if (r == 0) goto zret;
    return (r->f2C & 0x80) != 0;
zret:
    return 0;
}
