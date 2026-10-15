#include "types.h"

typedef struct {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} Vec;

typedef struct {
    u8 pad0[0x930];
    u8 m930[0x97C - 0x930];
    u8 m97C[0xA2E - 0x97C];
    s16 st;
    u8 padA30[0xA44 - 0xA30];
    s32 flags;
} Obj;

extern "C" {
f32 VecLength_1cb4c0(Vec *);
void VecScaleToLength_1cb510(Vec *, Vec *, f32);
void VecSub_1cbd00(Vec *, Vec *, Vec *);
void CharaMoveReqSet_219310(void *, Vec *, s32, s32);
void CharaGetPos_2388a0(Obj *, Vec *);
void TargetRefGetPos_2e6a60(void *, Vec *);
s32 TargetRefIsActive_2e6f00(void *);
f32 TargetRefGetRadius_2e7100(void *);
s32 TargetRefGetKind_2e7130(void *);
extern f32 D_0045B080[4];
}

extern "C" s32 CharaLaunchTowardTarget_2114e0(Obj *obj, s32 arg1, f32 f0, f32 f1)
{
    Vec a;
    Vec b;
    Vec v;
    bool ok;
    u8 *p;
    s32 k;
    f32 hi;
    f32 lo;
    f32 y;
    f32 d;
    f32 t;

    ok = obj->st == 2 || obj->st == 3;
    if (!ok) {
        return 0;
    }
    if (!(obj->flags & 0x8000)) {
        return 0;
    }
    p = obj->m97C;
    if (TargetRefIsActive_2e6f00(p) == 0) {
        return 0;
    }
    k = TargetRefGetKind_2e7130(p);
    if (k != 5 && k != 4) {
        return 0;
    }
    CharaGetPos_2388a0(obj, &a);
    TargetRefGetPos_2e6a60(p, &b);
    hi = D_0045B080[0];
    b.y = b.y + 0.0f - 0.75f * hi;
    VecSub_1cbd00(&v,&b,&a);
    y = v.y;
    v.y = 0.0f;
    t = VecLength_1cb4c0(&v);
    d = t - TargetRefGetRadius_2e7100(p) - f0;
    if (d < -f1) {
        d = -f1;
    }
    if (!(d <= f1)) {
        d = f1;
    }
    VecScaleToLength_1cb510(&v, &v, d);
    if (!(y <= 5.0f*hi)) y=5.0f*hi;
    v.y = y;
    CharaMoveReqSet_219310(obj->m930, &v, arg1, 0);
    return 1;
}
