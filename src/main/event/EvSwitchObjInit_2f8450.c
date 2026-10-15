#include "types.h"

typedef struct P3_002f8450 { f32 a; f32 b; f32 c; } P3_002f8450;

typedef struct S_002f8450 {
    u8 pad0[0x110];
    P3_002f8450 f110;
    P3_002f8450 f11C;
    P3_002f8450 f128;
    P3_002f8450 f134;
    P3_002f8450 f140;
    P3_002f8450 f14C;
} S_002f8450;

extern void EvSwitchObjReset_2f8670(S_002f8450 *);
extern s32 EvObjInit_2f9cf0(S_002f8450 *, s32, S_002f8450 *, s32, s32, s32);
extern s32 EvSwitchObjGetTargetRef_2f8400(S_002f8450 *);
extern s32 TargetRefCopy_2e7140(void *, s32, s32);

s32 EvSwitchObjInit_2f8450(S_002f8450 *self, s32 p1, S_002f8450 *src, s32 p3, s32 p4, s32 p5)
{
    EvSwitchObjReset_2f8670(self);
    if (src == 0) goto zero;
    if (p3 != 0) goto ok;
zero:
    return 0;
ok:
    if (EvObjInit_2f9cf0(self, p1, src, p3, p4, p5) == 0) return 0;
    if (TargetRefCopy_2e7140((u8 *)self + 0xE0, EvSwitchObjGetTargetRef_2f8400(src), p3) == 0) return 0;
    self->f110 = src->f110;
    self->f11C = src->f11C;
    self->f128 = src->f128;
    self->f134 = src->f134;
    self->f140 = src->f140;
    self->f14C = src->f14C;
    return 1;
}
