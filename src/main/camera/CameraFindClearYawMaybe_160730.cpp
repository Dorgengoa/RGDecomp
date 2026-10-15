#include "types.h"
#include "vec.h"

class Base {
public:
    u8 pad0[0xC0];
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void *GetPrm();
};

class Obj : public Base {
public:
    u8 padC4[0xE0 - 0xC4];
    Vec4 xE0;
    Vec4 xF0;
    u8 pad100[0x120 - 0x100];
    u8 x120[0x230 - 0x120];
    Vec4 x230;
    s32 x240;
};

typedef struct Ent {
    u8 pad0[0x44];
    s16 x44;
    s16 x46;
    u8 pad48[0x60 - 0x48];
} Ent;

extern "C" {
void MtxMulVec4_10a8c0(Vec4 *, Mtx4 *, Vec4 *);
void VecScale_13be00(Vec4 *, Vec4 *, f32);
void VecSub_13be40(Vec4 *, Vec4 *, Vec4 *);
void MtxIdentity_13d2e0(Mtx4 *);
f32 VecDistance_13d3d0(Vec4 *, Vec4 *);
void VecAddInPlace_13e070(Vec4 *, u8 *);
s32 MeshRaycastWrapper_16f610(s32, s32, Vec4 *, Vec4 *, Vec4 *, s32, s32);
void sceVu0RotMatrixY(Mtx4 *, Mtx4 *, f32);
extern f32 D_0047D53C;
extern f32 D_0047D8A0;
extern f32 D_0047D8A4;
s32 CameraFindClearYawMaybe_160730(Obj *self, s32 arg1, s32 arg2);
}

s32 CameraFindClearYawMaybe_160730(Obj *self, s32 arg1, s32 arg2) {
    Vec4 v1E0;
    Vec4 v1D0;
    Vec4 v1C0;
    Vec4 v1B0;
    Vec4 v1A0;
    Vec4 v190;
    Vec4 v180;
    Vec4 v170;
    Vec4 v160;
    Vec4 v150;
    Mtx4 m110;
    Mtx4 mD0;
    Mtx4 m90;
    Vec4 v80;
    Vec4 *pf;
    s32 r;
    s32 na;
    s32 nb;
    s32 i;
    f32 da;
    f32 db;
    s32 t;
    f32 a;
    f32 b;
    f32 ang;

    self->GetPrm();
    {
        Vec4 *pe = &self->xE0;
        pf = &self->xF0;
        if (self->x240 != 0) {
            v1E0 = self->x230;
            VecAddInPlace_13e070(&v1E0, self->x120);
        } else {
            v1E0 = *pe;
        }
    }
    VecSub_13be40(&v1D0, &v1E0, pf);
    v190 = v1E0;
    v1B0 = *pf;
    v1A0 = v1D0;
    VecScale_13be00(&v160, &v1A0, D_0047D53C);
    VecSub_13be40(&v160, &v1E0, &v160);
    v160.w = 3.0f;
    r = MeshRaycastWrapper_16f610(arg1, arg2, &v160, &v190, &v1C0, 0, 0x2000);
    while (r >= 0 && ((Ent *)arg1)[r].x44 == 2) {
        ((Ent *)arg1)[r].x46 = 0x2000;
        r = MeshRaycastWrapper_16f610(arg1, arg2, &v160, &v190, &v1C0, 0, 0x2000);
    }
    v180 = v1A0;
    v170 = v1A0;
    v180.w = 0.0f;
    v170.w = 0.0f;
    v1A0.w = 0.0f;
    MtxIdentity_13d2e0(&m110);
    MtxIdentity_13d2e0(&mD0);
    MtxIdentity_13d2e0(&m90);
    sceVu0RotMatrixY(&m110, &m110, D_0047D8A0);
    sceVu0RotMatrixY(&mD0, &mD0, D_0047D8A4);
    db = 120.0f;
    nb = 0;
    na = 0;
    v150 = v1B0;
    da = db;
    for (i = 0; (f32)i < 128.0f; i++) {
        if (na == 0) {
            MtxMulVec4_10a8c0(&v180, &m110, &v180);
            VecSub_13be40(&v150, &v190, &v180);
            VecScale_13be00(&v80, &v180, D_0047D53C);
            VecSub_13be40(&v80, &v190, &v80);
            v80.w = 1.0f;
            r = MeshRaycastWrapper_16f610(arg1, arg2, &v80, &v190, &v1C0, 0, 0x2000);
            while (r >= 0 && ((Ent *)arg1)[r].x44 == 2) {
                ((Ent *)arg1)[r].x46 = 0x2000;
                r = MeshRaycastWrapper_16f610(arg1, arg2, &v80, &v190, &v1C0, 0, 0x2000);
            }
            if (r >= 0) {
                na = i + 1;
                if (!(da <= VecDistance_13d3d0(&v1C0, &v190))) {
                    da = VecDistance_13d3d0(&v1C0, &v190) - 10.0f;
                }
            }
        }
        if (nb == 0) {
            MtxMulVec4_10a8c0(&v170, &mD0, &v170);
            VecSub_13be40(&v150, &v190, &v170);
            VecScale_13be00(&v160, &v170, D_0047D53C);
            VecSub_13be40(&v160, &v190, &v160);
            v160.w = 1.0f;
            r = MeshRaycastWrapper_16f610(arg1, arg2, &v160, &v190, &v1C0, 0, 0x2000);
            while (r >= 0 && ((Ent *)arg1)[r].x44 == 2) {
                ((Ent *)arg1)[r].x46 = 0x2000;
                r = MeshRaycastWrapper_16f610(arg1, arg2, &v160, &v190, &v1C0, 0, 0x2000);
            }
            if (r >= 0) {
                nb = i + 1;
                if (!(db <= VecDistance_13d3d0(&v1C0, &v190))) {
                    db = VecDistance_13d3d0(&v1C0, &v190) - 10.0f;
                }
            }
        }
    }
    if (na == 0) {
        na = 0x80;
    }
    if (nb == 0) {
        nb = 0x80;
    }
    da = (da < db) ? da : db;
    t = (s32)(14.0f * (1.0f - da / 120.0f));
    if (t < na && t < nb) {
        return 0;
    }
    a = 0.0f;
    b = 0.0f;
    ang = 0.0f;
    if (na <= t) {
        a = D_0047D8A0 * (f32)(t - na);
    }
    if (nb <= t) {
        b = D_0047D8A0 * (f32)(t - nb);
    }
    if (a > 0.0f && b > 0.0f) {
        ang = 0.5f * (b - a);
    } else {
        if (a > 0.0f) {
            ang = -a;
        }
        if (b > 0.0f) {
            ang = b;
        }
    }
    sceVu0RotMatrixY(&m90, &m90, ang);
    MtxMulVec4_10a8c0(&v1A0, &m90, &v1A0);
    VecSub_13be40(pf, &v190, &v1A0);
    return 1;
}
