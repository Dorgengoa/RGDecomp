#include "types.h"

typedef unsigned __int128 u128;
typedef struct V16 { u128 q; } V16;

typedef struct Ent {
    s32 m0;
    s32 m4;
    f32 m8;
    f32 mC;
    f32 m10;
    f32 m14;
    f32 m18;
    f32 m1C;
} Ent;

typedef struct Pool {
    u8 pad0[0xA0];
    s32 mA0;
    V16 *mA4;
    u8 padA8[0x34];
    s32 mDC;
    Ent *mE0;
} Pool;

extern f32 VecDistance_13d3d0(V16 *, V16 *);
extern f32 VariantGetFloat_15f740(s32);
extern s32 VariantGetInt_15f780(s32);
extern Pool *D_00481154;
extern s32 D_0048116C;
extern s32 D_00481178;

static __inline Ent *alloc(void)
{
    Pool *p = D_00481154;
    s32 idx = D_0048116C++;
    if (!(idx >= 0 && idx < p->mDC)) {
        return NULL;
    }
    return &p->mE0[idx];
    return NULL;
}

static __inline s32 valid(s32 i)
{
    Pool *p = D_00481154;
    if (i < 0 || i >= p->mA0) {
        return 0;
    }
    return 1;
}

s32 DynBindSpringCmd_1679e0(s64 *arg0, s32 arg1)
{
    V16 a;
    V16 b;
    Ent *e;
    s32 idx;
    s32 i0;
    s32 i1;
    f32 d;
    f32 s;
    f32 f;

    e = alloc();
    if (e == NULL) {
        return 0;
    }
    i0 = D_00481178 + VariantGetInt_15f780((s32)arg0++);
    i1 = D_00481178 + VariantGetInt_15f780((s32)arg0++);
    if (!valid(i0) || !valid(i1)) {
        return 0;
    }
    e->m0 = i0;
    e->m4 = i1;
    if (valid(i0)) {
        a = D_00481154->mA4[i0];
    }
    if (valid(i1)) {
        b = D_00481154->mA4[i1];
    }
    e->mC = VariantGetFloat_15f740((s32)arg0++);
    s = VariantGetFloat_15f740((s32)arg0++);
    d = VecDistance_13d3d0(&a, &b);
    e->m14 = d * s;
    e->m18 = d * VariantGetFloat_15f740((s32)arg0++);
    e->m1C = d * VariantGetFloat_15f740((s32)arg0++);
    if (arg1 >= 7) {
        e->m10 = VariantGetFloat_15f740((s32)arg0++);
    }
    e->m8 = 0.5f;
    if (arg1 >= 8) {
        f = VariantGetFloat_15f740((s32)arg0++);
        e->m8 = f;
        if (!(f <= 1.0f) || f < 0.0f) {
            e->m8 = 0.5f;
        }
    }
    return 1;
}
