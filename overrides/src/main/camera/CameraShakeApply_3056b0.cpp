/* rg-override: replaces game/src/main/camera/CameraShakeApply_3056b0.cpp sha256 e1dfc03bd231ba9d3ae3443261ce1ae2ebc465296a6bdf94b0daf623adbe925f
 * why: accessibility.camera_shake (docs/SETTINGS.md "Accessibility"): the shaken eye of the
 * draw camera's copy (TaskUpdateDrawInfo_2f6ff0) blended toward the unshaken one by
 * rg_camera_shake_scale(); 1 (Original) runs the generated body unchanged, 0 = no shake */
/* rgp:protos */
#line 1
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
    VC_VPTR_MEMBER;
    
    
    
    void f18(u128 * a0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { VCM(void, (void *, u128 *, int, int), 0x18, a0, rgp_fwd2, rgp_fwd3); }
    
    
    
    
    
    
    
    
    
    void f40() { VCM0(void, 0x40); }
};

extern "C" {
double Sin_128880(double);
f32 VecDist_1cb420(u128 *, void *);
void MatMulVec4_1cb940(u128 *, u128 *, u128 *);
void VecNormalize_1cbb80(u128 *, u128 *);
void VecScale_1cbca0(u128 *, void *, f32);
void VecSub_1cbd00(u128 *, u128 *, u128 *);
void VecAdd_1cbdc0(u128 *, u128 *, u128 *);
f32 dptofp(double);
double fptodp(f32);
}
extern "C" f32 D_0047D858;
extern "C" float rg_camera_shake_scale(void);

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

extern "C" void CameraShakeApply_3056b0(O003056b0 *o, A003056b0 *a, int rgp_a2, int rgp_a3)
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

    f32 rg_k;
    u128 rg_eye;
    if (!o->x2D0) {
        return;
    }
    rg_k = rg_camera_shake_scale();   /* (counted: RG_SHAKE_LOG) */
    if (rg_k <= 0.0f) {
        return;                       /* no shake: the copy keeps the game camera's eye */
    }
    sp60 = a->v60;
    sp50 = a->v50;
    rg_eye = sp50;
    a->f18(sp70, (int)(long)(rgp_a2), (int)(long)(rgp_a3));
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
    if (rg_k < 1.0f) {
        /* reduced: eye = unshaken + (shaken - unshaken) * k */
        u128 rg_d;
        VecSub_1cbd00(&rg_d, &sp50, &rg_eye);
        VecScale_1cbca0(&rg_d, &rg_d, rg_k);
        VecAdd_1cbdc0(&sp50, &rg_eye, &rg_d);
    }
    a->v50 = sp50;
    a->f40();
}
