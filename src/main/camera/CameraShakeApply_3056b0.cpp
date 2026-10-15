#include "types.h"
#include "vec.h"

#define S32(p, o) (*(s32 *)((u8 *)(p) + (o)))
#define F32(p, o) (*(f32 *)((u8 *)(p) + (o)))

class A003056b0 {
public:
    u8 pad0[0x50];
    u128 v50;
    u128 v60;
    u8 pad70[0xC0 - 0x70];
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void f18(u128 *);
    virtual void w0();
    virtual void w1();
    virtual void w2();
    virtual void w3();
    virtual void w4();
    virtual void w5();
    virtual void w6();
    virtual void w7();
    virtual void w8();
    virtual void f40();
};

extern "C" {
s32 Sin_128880(s32);
f32 VecDist_1cb420(u128 *, void *);
void MatMulVec4_1cb940(u128 *, u128 *, u128 *);
void VecNormalize_1cbb80(u128 *, u128 *);
void VecScale_1cbca0(u128 *, void *, f32);
void VecSub_1cbd00(u128 *, u128 *, u128 *);
void VecAdd_1cbdc0(u128 *, u128 *, u128 *);
f32 dptofp(s32);
s32 fptodp(f32);
}
extern f32 D_0047D858;

typedef struct O003056b0 {
    u8 pad0[0x2AC];
    u8 flag;
    u8 pad2ad[3];
    u128 v2B0;
    u128 v2C0;
    f32 x2D0;
    f32 x2D4;
    f32 x2D8;
    f32 x2DC;
} O003056b0;

extern "C" void CameraShakeApply_3056b0(O003056b0 *o, A003056b0 *a)
{
    u128 sp70[4];
    u128 sp60;
    u128 sp50;
    u128 sp40;
    f32 t;
    f32 f22;
    f32 f3;
    f32 f21;
    f32 f20;
    f32 one;

    if (!o->x2D0) {
        return;
    }
    sp60 = a->v60;
    sp50 = a->v50;
    a->f18(sp70);
    f3 = 1.0f;
    if (o->x2D8) {
        f3 = f3 / (f32)(s32)(f3 + o->x2DC / (0.5f * o->x2D4));
    }
    f22 = o->x2D0 * f3;
    t = o->x2D4; t = o->x2DC / t;
    f21 = dptofp(Sin_128880(fptodp(D_0047D858 * (t - (f32)(s32)t))));
    if (o->flag != 0) {
        f20 = VecDist_1cb420(&sp60, &o->v2B0);
    } else {
        f20 = 1000.0f;
    }
    VecScale_1cbca0(&sp40, &o->v2C0, f22 * f21);
    ((s32 *)&sp40)[3] = 0x3F800000;
    { u128 *d = &sp40; MatMulVec4_1cb940(d, sp70, d); }
    { u128 *d = &sp50; VecSub_1cbd00(d, d, &sp60); }
    { u128 *d = &sp50; VecNormalize_1cbb80(d, d); }
    { u128 *d = &sp50; VecScale_1cbca0(d, d, f20); }
    { u128 *d = &sp50; VecAdd_1cbdc0(d, d, &sp60); }
    { u128 *d = &sp50; VecAdd_1cbdc0(d, d, &sp40); }
    a->v50 = sp50;
    a->f40();
}
