/* rgp:protos */
#line 1
#include "types.h"

typedef struct Vec4 { f32 x; f32 y; f32 z; f32 w; } __attribute__((aligned(16))) Vec4;
typedef struct SPos { s32 x; s32 y; s32 z; s32 w; } __attribute__((aligned(16))) SPos;

class Cam {
public:
    u8 pad0[0xC0];
    VC_VPTR_MEMBER; void d0() { VCM0(void, 0x8); }
    void d1() { VCM0(void, 0xC); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void GetPos(Vec4 * a0) { VCM(void, (void *, Vec4 *), 0xA4, a0); }
    void GetAt(Vec4 * a0) { VCM(void, (void *, Vec4 *), 0xA8, a0); }
};

typedef struct Flare {
    s32 u0;
    s32 v0;
    s32 u1;
    s32 v1;
    f32 scale;
    f32 dist;
} Flare;

typedef struct Lens {
    Flare fl[12];
    u8 pad120[0x10];
    f32 r;
    f32 g;
    f32 b;
    u8 pad13C[8];
    f32 a;
} Lens;

typedef struct Pkt {
    s32 w0;
    s32 w4;
    s32 w8;
    s32 wC;
} Pkt;

typedef struct World {
    u8 pad0[0x4344];
    s32 w4344;
} World;

extern "C" {
extern u8 D_00461A60[];
extern u8 D_00461A70[];
extern u8 D_00461A80[];
extern u8 D_00461A90[];
extern f32 D_0047D7CC;
extern f32 D_0047D7EC;

extern f32 sqrtf(f32);
extern f32 Vu0InnerProduct_13bd60(Vec4 *, Vec4 *);
extern void VecSub_13be40(Vec4 *, Vec4 *, Vec4 *);
extern f32 VecDistance_13d3d0(Vec4 *, Vec4 *);
extern void GsPktSetOriginMode_13e2f0(s32, s32);
extern void GsPktSetGouraud_13e3b0(s32, s32);
extern void GsPktSetUseUV_13e3e0(s32, s32);
extern void GsPktSetTextured_13e400(s32, s32);
extern void GsPktSetZWriteMask_13e430(s32, s32);
extern void GsPktEnableZTest_13e460(s32, s32);
extern void GsPktEnableAlphaTest_13e4d0(s32, s32);
extern void GsPktSetBlendMode_13e4f0(s32, s32);
extern void GsPktSetAlphaBlend_13e500(s32, s32);
extern void GsPktSetTexture_13ec00(s32, s32);
extern void GsPktSetUV_13ed60(s32, s32, s32);
extern void GsPktSetRGBAQVec_13edd0(s32, f32 *);
extern void GsPktSetRGBAQ_13ee40(s32, s32, s32, s32, s32);
extern void GsPktSetXYZ_13ef10(s32, s32, s32, s32);
extern void GsPktClose_13f5b0(s32);
extern void GsPktOpenPrim_13f730(s32, s32);
extern Pkt *DepthProbeGetSlot_13fc80(s32, s32);
extern void DrawListAddTexLoad_1418c0(s32, s32, f32);
extern void DrawListEndPrim_141a20(s32);
extern s32 DrawListBeginPrim_141b00(s32);
extern s32 DrawEnvGetHeight_1451d0(s32);
extern s32 DrawEnvGetWidth_1451e0(s32);
extern s32 NameTableFindByName_159fb0(s32, u8 *, s32);
extern s32 ProjectDepth_15d0a0(f32);
extern void ProjectToScreenOffset_15d160(SPos *, Vec4 *);
extern s32 GetDrawCtxNameTable_15de40(void);
extern s32 GetDrawCtx_15de80(void);
extern Cam *ObjRecGetLiveObject_1c3bc0(World *, s32);
extern void SceneGetSunPos_1c4fc0(World *, Vec4 *);
extern s32 IsWidescreen_1c6ab0(void);
extern void SunFlareDraw_1cf240(World *, s32, u8 *, u8 *);
extern World *GetCurrentScene_1f5be0(void);
extern s32 LensFlareIsEnabled_2ed820(Lens *);
extern s32 ScreenPointInBounds_2ee250(Lens *, Vec4 *);
extern double litodp(s32);
extern double fptodp(f32);
extern double dpdiv(double, double);
extern f32 dptofp(double);


#pragma opt_dead_assignments off
void LensFlareDraw_2ed830(Lens *o)
{ RG_VU0_FRAME;
    Vec4 sun __attribute__((aligned(16)));
    Vec4 eye __attribute__((aligned(16)));
    SPos s1 __attribute__((aligned(16)));
    SPos s0 __attribute__((aligned(16)));
    Vec4 cp __attribute__((aligned(16)));
    Vec4 d1 __attribute__((aligned(16)));
    Vec4 d0 __attribute__((aligned(16)));
    Vec4 at __attribute__((aligned(16)));
    Vec4 pos __attribute__((aligned(16)));
    Vec4 c[4] __attribute__((aligned(16)));
    f32 ax;
    f32 ay;
    Cam *cam;
    s32 scr;
    s32 w;
    s32 h;
    Pkt *pk;
    s32 fnt;
    s32 gp;
    Flare *e;
    f32 dy;
    f32 len;
    World *g;
    f32 sc;
    f32 kx;
    f32 ky;
    f32 t;
    f32 sy;
    f32 sx;
    f32 q;
    f32 u;
    f32 hw;
    f32 hh;
    f32 y1;
    f32 x1;
    f32 y0;
    f32 x0;
    s32 i;
    s32 dd;
    s32 j;
    s32 vis;
    s32 dh;
    s32 dw;
    f32 dx;

    if (((unsigned char)LensFlareIsEnabled_2ed820(o)) == 0) {
        return;
    }
    if (o->a <= 0.0f) {
        return;
    }
    g = GetCurrentScene_1f5be0();
    SceneGetSunPos_1c4fc0(g, &sun);
    sun.w = 1.0f;
    cam = ObjRecGetLiveObject_1c3bc0(g, g->w4344);
    cam->GetAt(&eye);
    eye.w = 1.0f;
    scr = GetDrawCtx_15de80();
    w = DrawEnvGetWidth_1451e0(scr);
    h = DrawEnvGetHeight_1451d0(scr);
    ProjectToScreenOffset_15d160(&s0, &sun);
    ProjectToScreenOffset_15d160(&s1, &eye);
    if (s0.x / 16 <= 4 || s0.x / 16 >= w - 4) {
        return;
    }
    if (s0.y / 16 <= 4 || s0.y / 16 >= h - 4) {
        return;
    }
    pk = DepthProbeGetSlot_13fc80(scr, 0);
    pk->w0 = 1;
    pk->w4 = s0.x / 16;
    pk->w8 = s0.y / 16;
    cam->GetPos(&cp);
    dd = ProjectDepth_15d0a0(VecDistance_13d3d0(&sun, &cp));
    if (pk->wC > dd) {
        return;
    }
    cam->GetAt(&at);
    VecSub_13be40(&d0, &cp, &at);
    VecSub_13be40(&d1, &cp, &sun);
    if (Vu0InnerProduct_13bd60(&d0, &d1) < 0.0f) {
        return;
    }
    fnt = GetDrawCtxNameTable_15de40();
    DrawListAddTexLoad_1418c0(scr, 0x31D, 1.0f);
    gp = DrawListBeginPrim_141b00(scr);
    GsPktSetBlendMode_13e4f0(gp, 2);
    GsPktSetAlphaBlend_13e500(gp, 1);
    GsPktEnableAlphaTest_13e4d0(gp, 1);
    GsPktEnableZTest_13e460(gp, 0);
    GsPktSetTextured_13e400(gp, 1);
    GsPktSetUseUV_13e3e0(gp, 1);
    GsPktSetOriginMode_13e2f0(gp, 0);
    GsPktEnableZTest_13e460(gp, 1);
    GsPktSetZWriteMask_13e430(gp, 0);
    GsPktSetGouraud_13e3b0(gp, 1);
    GsPktEnableZTest_13e460(gp, 1);
    GsPktOpenPrim_13f730(gp, 6);
    GsPktSetRGBAQVec_13edd0(gp, &o->r);
    GsPktSetTexture_13ec00(gp, NameTableFindByName_159fb0(fnt, D_00461A60, -1));
    GsPktSetUV_13ed60(gp, 0, 0);
    GsPktSetXYZ_13ef10(gp, s0.x - 0x800, s0.y - 0x800, 0);
    GsPktSetUV_13ed60(gp, 0x80, 0x80);
    GsPktSetXYZ_13ef10(gp, s0.x + 0x800, s0.y + 0x800, 0);
    GsPktClose_13f5b0(gp);
    GsPktEnableZTest_13e460(gp, 0);
    GsPktSetZWriteMask_13e430(gp, 1);
    sx = (f32)s0.x;
    sy = (f32)s0.y;
    dx = 16.0f * (f32)(w / 2) - sx;
    dy = 16.0f * (f32)(h / 2) - sy;
    len = sqrtf(dx * dx + dy * dy);
    t = 2.0f * len;
    sc = dptofp(dpdiv(fptodp(t), litodp(0xAF)));
    dx = dx / len;
    dy = dy / len;
    GsPktOpenPrim_13f730(gp, 6);
    GsPktSetRGBAQ_13ee40(gp, (s32)o->r, (s32)o->g, (s32)o->b, (s32)(128.0f * o->a));
    kx = 1.0f;
    ky = 1.1666666f;
    if (((unsigned char)IsWidescreen_1c6ab0()) != 0) {
        kx = kx * 0.75f;
    }
    ax = dx * sc;
    ay = dy * sc;
    kx = kx * 1.5f;
    ky = ky * 1.5f;
    e = o->fl;
    for (i = 0; i < 12; i++, e++) {
        q = (t - sc * e->dist) / t;
        q = 1.0f - q;
        u = 1.0f + (f32)(0.1f * (f32)i);
        pos.x = sx + u * (e->dist * ax);
        pos.y = sy + u * (e->dist * ay);
        if (ScreenPointInBounds_2ee250(o, &pos) == 0) {
            continue;
        }
        vis = 0;
        dw = e->v1 - e->v0;
        dh = e->u1 - e->u0;
        hw = kx * (q * (16.0f * (e->scale * (f32)dw)));
        x0 = pos.x - hw;
        x1 = pos.x + hw;
        hh = ky * (q * (16.0f * (e->scale * (f32)dh)));
        y0 = pos.y - hh;
        y1 = pos.y + hh;
        c[0].x = x0;
        c[1].x = x0;
        c[2].x = x1;
        c[3].x = x1;
        c[0].y = y0;
        c[2].y = y0;
        c[1].y = y1;
        c[3].y = y1;
        for (j = 0; j < 4; j++) {
            vis |= ScreenPointInBounds_2ee250(o, &c[j]);
        }
        if (vis != 0) {
            GsPktSetTexture_13ec00(gp, NameTableFindByName_159fb0(fnt, D_00461A70, -1));
            GsPktSetUV_13ed60(gp, e->v0, e->u0);
            GsPktSetXYZ_13ef10(gp, (s32)x0, (s32)y0, 0);
            GsPktSetUV_13ed60(gp, e->v1, e->u1);
            GsPktSetXYZ_13ef10(gp, (s32)x1, (s32)y1, 0);
        }
    }
    GsPktClose_13f5b0(gp);
    DrawListEndPrim_141a20(scr);
    SunFlareDraw_1cf240(g, 0x31D, D_00461A80, D_00461A90);
}

}
