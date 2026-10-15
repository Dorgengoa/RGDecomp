#include "types.h"

typedef struct { f32 x, y, z; } V3f;

typedef struct E3036f0 { u8 pad[0xC]; } E3036f0;

typedef struct T3036f0 {
    u8  pad00[0x10];
    V3f v10;
    V3f v1C;
    V3f v28;
    s32 a34[9];
    V3f v58;
    V3f v64;
    V3f v70;
    s32 a7C[9];
    u8  mA0[0xD0 - 0xA0];
    s32 fD0;
    u8  padD4[0x180 - 0xD4];
    E3036f0 *f180;
    u8  pad184[4];
    s16 f188;
} T3036f0;

extern void EvObjResolveTarget_2f9a60(T3036f0 *);
extern void EventRefListResolve_3045f0(E3036f0 *);
extern u8 EvDoorObjRefListsAllResolved_304280(T3036f0 *);
extern void TargetRefApplyToEventObj_2e6810(void *, void *);

s32 EvDoorObjResolve_3036f0(T3036f0 *self)
{
    E3036f0 *e;
    s32 i;
    s32 *sp;
    s32 *dp;
    s32 n;
    s32 v;

    EvObjResolveTarget_2f9a60(self);
    e = self->f180;
    i = 0;
    while (i < self->f188) {
        EventRefListResolve_3045f0(e);
        i++;
        e++;
    }
    if (EvDoorObjRefListsAllResolved_304280(self) != 0) {
        v = self->fD0 | 0x02000000;
    } else {
        v = self->fD0 & 0xFDFFFFFF;
    }
    self->fD0 = v;
    TargetRefApplyToEventObj_2e6810(self->mA0, &self->v10);
    self->v58 = self->v10;
    self->v64 = self->v1C;
    self->v70 = self->v28;
    sp = self->a34;
    dp = self->a7C;
    for (n = 9; n > 0; n--) {
        *dp = *sp;
        sp++;
        dp++;
    }
    return 1;
}
