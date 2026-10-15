#pragma optimization_level 3
#include "types.h"

typedef unsigned __int128 u128;
typedef struct Vec4 { f32 x; f32 y; f32 z; f32 w; } __attribute__((aligned(16))) Vec4;
typedef struct V4 { f32 x; f32 y; f32 z; f32 w; } V4;
typedef struct Tri6 { V4 v[6]; } Tri6;
typedef struct Mtx4 { Vec4 r[4]; } Mtx4;

class Cam {
public:
    u8 pad0[0xC0];
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void GetMtx(void *);
    virtual void d7();
    virtual void d8();
    virtual void d9();
    virtual void d10();
    virtual void d11();
    virtual void d12();
    virtual void d13();
    virtual void d14();
    virtual void d15();
    virtual void d16();
    virtual void d17();
    virtual void d18();
    virtual void d19();
    virtual void d20();
    virtual void d21();
    virtual void d22();
    virtual void d23();
    virtual void d24();
    virtual void d25();
    virtual void d26();
    virtual void d27();
    virtual void d28();
    virtual void d29();
    virtual void d30();
    virtual void d31();
    virtual void d32();
    virtual void d33();
    virtual void d34();
    virtual void d35();
    virtual void d36();
    virtual void d37();
    virtual void d38();
    virtual void d39();
    virtual void d40();
    virtual void GetPos(Vec4 *);
    virtual void GetAt(Vec4 *);
};

typedef struct Ray {
    f32 f50;
    f32 f54;
    f32 f58;
    f32 f5C;
} Ray;

typedef struct Halo {
    u8 b0;
    u8 b1;
    u8 b2;
    u8 pad3[0xD];
    Vec4 v10;
    Vec4 v20;
    Vec4 v30;
    f32 f40;
    s32 w44;
    f32 f48;
    s32 w4C;
    Ray rays[16];
    u8 pad150[0x18];
    f32 f168;
    f32 f16C;
} Halo;

extern "C" {

extern V4 D_0044F9E0[6];
extern V4 D_0044FA40[6];
extern volatile f32 D_0047D288;
extern f32 D_0047D53C;
extern f32 D_0047D5D0;
extern const f32 D_0047D7C4 __attribute__((section(".sdata")));
extern f32 D_0047D804;
extern f32 D_0047D840;
extern f32 D_0047D844;

extern f32 sqrtf(f32);
extern f32 Cosf_128d30(f32);
extern f32 Sinf_128fd0(f32);
extern f32 Vu0InnerProduct_13bd60(Vec4 *, Vec4 *);
extern void VecNormalize_13bd90(Vec4 *, Vec4 *);
extern void VecScale_13be00(void *, void *, f32);
extern void VecAdd_13be20(void *, void *, void *);
extern void VecSub_13be40(Vec4 *, Vec4 *, Vec4 *);
extern f32 WrapAngle_13c050(f32);
extern void MtxMulPoint_13c890(Vec4 *, Mtx4 *, Vec4 *);
extern void MtxMulVec4_13c900(V4 *, Mtx4 *, V4 *);
extern void MtxRotZ_13cdb0(Mtx4 *, f32);
extern void GsPktSetOriginMode_13e2f0(s32, s32);
extern void GsPktSetGouraud_13e3b0(s32, s32);
extern void GsPktSetTexFilter_13e3d0(s32, s32);
extern void GsPktSetTextured_13e400(s32, s32);
extern void GsPktSetFrameMask_13e420(s32, s32);
extern void GsPktSetZWriteMask_13e430(s32, s32);
extern void GsPktEnableZTest_13e460(s32, s32);
extern void GsPktSetAlphaTestFunc_13e4c0(s32, s32, s32);
extern void GsPktEnableAlphaTest_13e4d0(s32, s32);
extern void GsPktSetBlendMode_13e4f0(s32, s32);
extern void GsPktSetAlphaBlend_13e500(s32, s32);
extern void GsPktSetTexture_13ec00(s32, s32);
extern void GsPktSetRGBAQ_13ee40(s32, s32, s32, s32, s32);
extern void GsPktSetXYZf_13f060(s32, f32, f32, f32);
extern void GsPktClose_13f5b0(s32);
extern void GsPktOpenPrim_13f730(s32, s32);
extern void DrawListEndPrim_141a20(s32);
extern s32 DrawListBeginPrim_141b00(s32);
extern s32 DrawEnvGetHeight_1451d0(s32);
extern s32 DrawEnvGetWidth_1451e0(s32);
extern s32 GetDrawCtx_15de80(void);



void SunLightDraw_293410(Halo *o, Cam *cam)
{
    Mtx4 m;
    Vec4 pos;
    Vec4 at;
    Vec4 d;
    Vec4 n;
    Vec4 s;
    Vec4 e;
    Vec4 ctr;
    Vec4 c;
    Vec4 w;
    s32 gp;
    f32 rstep;
    f32 ang;
    f32 sw;
    f32 sh;
    f32 dot;
    f32 a;
    s32 b;
    s32 i;
    f32 sn;
    f32 cs;
    s32 r;
    f32 hh;
    f32 sz;
    f32 yk;
    s32 j;
    V4 *v;
    s32 scr;

    if (o->b0 == 0) {
        return;
    }
    if (o->f48 == 0.0f) {
        return;
    }
    scr = GetDrawCtx_15de80();
    rstep = D_0047D804 / (f32)o->w44;
    ang = 0.0f;
    sw = (f32)DrawEnvGetWidth_1451e0(scr);
    sh = (f32)DrawEnvGetHeight_1451d0(scr);
    {
        u8 *p_ = (u8 *)&ctr;
        u32 n_ = 0x10;
        if (p_) {
            while (n_) {
                *p_ = 0;
                n_--;
                p_++;
            }
        }
    }
    ctr.y = sh / 2.0f;
    ctr.x = sw / 2.0f;
    cam->GetMtx(&m);
    cam->GetPos(&pos);
    cam->GetAt(&at);
    pos.y -= at.y;
    at.y -= at.y;
    if (o->b1 != 0) {
        VecScale_13be00(&o->v30, &o->v30, (f32)5000);
        if (o->v30.y < 8000.0f) {
            o->v30.y = 8000.0f;
        }
        o->b1 = 0;
    }
    VecAdd_13be20(&w, &o->v30, &at);
    VecSub_13be40(&d, &w, &pos);
    MtxMulPoint_13c890(&d, &m, &d);
    *(u128 *)&n = *(u128 *)&d;
    VecNormalize_13bd90(&n, &n);
    n.x *= -1.0f;
    n.z *= -1.0f;
    e.x = n.x;
    e.y = -n.y;
    e.z = 0.0f;
    e.w = 0.0f;
    VecNormalize_13bd90(&e, &e);
    VecScale_13be00(&s, &e, sw);
    VecAdd_13be20(&s, &ctr, &s);
    if (o->w4C == 0) {
        Vec4 up = {0.0f, 1.0f, 0.0f, 0.0f};
        dot = Vu0InnerProduct_13bd60(&m.r[2], (Vec4 *)(u32)&up);
        if (!((dot < 0.0f ? -dot : dot) <= 0.6000000238f)) {
            return;
        }
        if (!((dot < 0.0f ? -dot : dot) <= 0.3000000119f)) {
            a = dot < 0.0f ? -dot : dot;
            o->f48 = 0.6000000238f - a;
            o->f48 = o->f48 / 0.3000000119f;
        }
    }
    gp = DrawListBeginPrim_141b00(scr);
    GsPktSetGouraud_13e3b0(gp, 1);
    GsPktSetAlphaBlend_13e500(gp, 1);
    GsPktSetBlendMode_13e4f0(gp, 2);
    GsPktEnableAlphaTest_13e4d0(gp, 1);
    GsPktSetFrameMask_13e420(gp, 1);
    GsPktSetAlphaTestFunc_13e4c0(gp, 1, 0);
    GsPktEnableZTest_13e460(gp, 0);
    GsPktSetZWriteMask_13e430(gp, 1);
    GsPktSetTexFilter_13e3d0(gp, 1);
    GsPktSetTextured_13e400(gp, 0);
    GsPktSetOriginMode_13e2f0(gp, 0);
    GsPktOpenPrim_13f730(gp, 5);
    GsPktSetTexture_13ec00(gp, 0);
    {
        f32 col[2] = {1.0f, 1.8f};
        VecScale_13be00(&c, &o->v10, o->f48 * (o->f168 * col[0]));
    }
    for (i = 0; i < 4; i++) {
        if (!((&c.x)[i] <= 255.0f)) {
            (&c.x)[i] = 255.0f;
        }
    }
    GsPktSetRGBAQ_13ee40(gp, (s32)c.x, (s32)c.y, (s32)c.z, (s32)c.w);
    GsPktSetXYZf_13f060(gp, s.x, s.y, 0.0f);
    VecScale_13be00(&c, &o->v20, o->f48);
    GsPktSetRGBAQ_13ee40(gp, (s32)c.x, (s32)c.y, (s32)c.z, (s32)c.w);
    for (i = 0; i < o->w44 + 1; i++) {
        f32 kk[2] = {1.0f, 0.65f};
        sn = Cosf_128d30(ang);
        cs = sqrtf(1.0f - sn * sn);
        GsPktSetXYZf_13f060(gp, s.x + (sn * o->f40) * *(f32 *)(s32)&kk[i - i], s.y + (cs * o->f40) * *(f32 *)(s32)&kk[i - i], 0.0f);
        ang = WrapAngle_13c050(ang + rstep);
    }
    GsPktClose_13f5b0(gp);
    if (o->b2 != 0) {
        o->f16C = WrapAngle_13c050(D_0047D840 + o->f16C);
    }
    GsPktOpenPrim_13f730(gp, 3);
    for (r = 0; r < 16; r++) {
        Mtx4 rm;
        Tri6 A = *(Tri6 *)D_0044F9E0;
        Tri6 B = *(Tri6 *)D_0044FA40;
        MtxRotZ_13cdb0(&rm, WrapAngle_13c050(o->rays[r].f54 + o->f16C));
        hh = 0.5f * (1.0f + Sinf_128fd0(o->rays[r].f5C));
        sz = 48.0f * hh;
        yk = D_0047D53C + D_0047D5D0 * hh;
        for (j = 0; j < 6; j++) {
            v = &A.v[j];
            v->x = v->x * o->rays[r].f58;
            v->y = v->y * o->rays[r].f50;
            v->y = v->y * yk;
            MtxMulVec4_13c900(v, &rm, v);
            VecAdd_13be20(v, &s, v);
            VecScale_13be00(&B.v[j], &B.v[j], sz * o->f48);
        }
        for (b = 0; b < 4; b++) {
            for (i = 0; i < 3; i++) {
                j = b + i;
                GsPktSetRGBAQ_13ee40(gp, (s32)B.v[j].x, (s32)B.v[j].y, (s32)B.v[j].z, 0x80);
                GsPktSetXYZf_13f060(gp, A.v[j].x, A.v[j].y, 0.0f);
            }
        }
        if (o->b2 != 0) {
            o->rays[(u32)r].f5C = WrapAngle_13c050(D_0047D844 + o->rays[(u32)r].f5C);
        }
    }
    GsPktClose_13f5b0(gp);
    DrawListEndPrim_141a20(scr);
    o->b2 = 0;
}

}
