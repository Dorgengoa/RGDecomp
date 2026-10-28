/* rg-override: replaces game/src/main/gfx/CompassHudRender_370fb0.cpp sha256 f363f3bcda6f2867b72a9bfbe4d99dbdc6bd1c7255dc8b2019f301cf23d745ae
 * why: widescreen stage 1 (docs/WIDESCREEN.md "Stage 1"): the compass model is not WIDE-aware (projection 0.75 always): with the WIDE flag it takes rg_aspect_d() and its marker sprites rg_hud_xscale_world(); flag off = generated code */
/* rgp:protos */
#line 1
#pragma opt_propagation off
#pragma opt_loop_invariants off
#include "types.h"
/* rg-override: widescreen stage 1 (src/settings/rg_aspect.h) */
extern "C" float rg_aspect_d(void);
extern "C" float rg_hud_xscale(void);
extern "C" void rg_layout_suppress(int on);
extern "C" int rg_layout_active(void);
extern "C" float rg_hud_xscale_world(void);
extern "C" unsigned char IsWidescreen_1c6ab0(void);
#include "vec.h"

struct Cam {
    u8 pad0[0xC0];
    VC_VPTR_MEMBER;
    
    f32 f10() { return VCM0(f32, 0x10); }
    void f14(f32 a0) { VCM(void, (void *, f32), 0x14, a0); }
};

typedef struct V4 {
    f32 x, y, z, w;
} V4;

typedef struct P4 {
    V4 v[4];
} P4;

typedef struct Prm {
    f32 f0;
    f32 f4;
    f32 f8;
    f32 fC;
    f32 f10;
    u8 pad14[0x10];
    f32 f24;
    f32 f28;
    u8 pad2C[0x14];
} Prm;

typedef struct Sel {
    s32 a;
    s32 b;
    u8 pad8[8];
    Vec4 v10;
    u8 pad20[0xA0];
    Vec4 vC0;
    Vec4 vD0;
    u8 padE0[0xC0];
} Sel;

typedef struct Mtx {
    Vec4 r[4];
} Mtx;

typedef struct Scr {
    s32 x;
    s32 y;
    s32 z;
    s32 w;
} Scr;

typedef struct Owner {
    u8 pad[0x120];
    u8 sub120[0x50];
    f32 f170;
    u8 pad174[0xC];
    Vec4 v180;
} Owner;

typedef struct Arg {
    Owner *p0;
    s32 f4;
    s32 f8;
    u8 padC[0x10];
    f32 f1C;
} Arg;

typedef struct Wrk {
    u8 pad[0xF20];
    u8 *pF20;
} Wrk;

typedef struct Gam {
    u8 pad[0x4344];
    s32 f4344;
} Gam;

extern "C" V4 D_0047F9A0 __attribute__((section(".sdata")));
extern "C" V4 D_0047F9B0 __attribute__((section(".sdata")));
extern "C" V4 D_0047F9C0 __attribute__((section(".sdata")));
extern "C" V4 D_00453E10[4];

extern "C" {
void MtxMulVec4_10a8c0(Vec4 *, Mtx *, Vec4 *);
void VecAdd_13be20(Vec4 *, Vec4 *, Vec4 *);
void GsPktSetOriginMode_13e2f0(void *, s32);
void GsPktSetTexFilter_13e3d0(void *, s32);
void GsPktSetTextured_13e400(void *, s32);
void GsPktSetZWriteMask_13e430(void *, s32);
void GsPktEnableZTest_13e460(void *, s32);
void GsPktSetAlphaTestFunc_13e4c0(void *, s32, s32);
void GsPktSetBlendMode_13e4f0(void *, s32);
void GsPktSetAlphaBlend_13e500(void *, s32);
void GsPktSetTexture_13ec00(void *, s32);
void GsPktSetUV_13ed60(void *, s32, s32);
void GsPktSetRGBAQ_13ee40(void *, s32, s32, s32, s32);
void GsPktSetXYZ_13ef10(void *, s32, s32, s32);
void GsPktClose_13f5b0(void *);
void GsPktOpenPrim_13f730(void *, s32);
void GsPktSetDefaultState_13fa80(void *);
void DrawListAddTexLoad_1418c0(Wrk *, s32, f32);
void DrawListEndPrim_141a20(Wrk *);
void *DrawListBeginPrim_141b00(Wrk *);
void LightStateSetCurrent_142920(Wrk *, s32);
s32 LightStatePush_1429f0(Wrk *, Sel *, s32);
void CameraSetViewFromCameraBase_142dd0(Wrk *, void *, int, int);
void ViewStackPop_1443e0(Wrk *);
void ViewStackPush_144430(Wrk *);
void DrawListAddLightPacket_148120(Wrk *);
void DrawListAddCameraMatrixPacket_1481b0(Wrk *);
void DrawListAddViewPacket_1482e0(Wrk *);
void FrameCalcWorldMatrix_148ff0(s32, Mtx *);
void ModelDraw_14f6d0(Owner *, Wrk *, void *);
s32 ModelGetRootFrame_1511a0(Owner *);
void ViewSetScreenMatrix_1562b0(u8 *, Prm *);
void ViewSetPerspective_1564a0(u8 *, f32, f32, f32, f32, f32, f32);
void LightStateInit_156b50(Sel *);
void ProjectToScreen_15d340(Scr *, Vec4 *);
void GetDrawCtxNameTable_15de40(void);
Wrk *GetDrawCtx_15de80(void);
void CameraTweenStep_1771a0(Cam *);
void CameraObjCtor_177430(Cam *);
void *ObjRecGetLiveObject_1c3bc0(Gam *, s32);
Gam *GetCurrentScene_1f5be0(void);
void *memcpy(void *, const void *, u32);
void sceVu0ScaleVectorXYZ(Vec4 *, Vec4 *, f32);
extern f32 D_0047D1FC;
extern f32 D_0047D288;
extern f32 D_0047D830;
extern f32 D_0047D834;
extern f32 D_0047D838;
extern s8 D_0047F9D0[4][2];

#define VEC(c, o) (*(Vec4 *)((u8 *)(c) + (o)))

static void rg_wide_CompassHudRender_370fb0(Arg *arg) {
    Prm save __attribute__((aligned(16)));
    Prm tmp __attribute__((aligned(16)));
    Vec4 buf[0x19] __attribute__((aligned(16)));
    Sel sel __attribute__((aligned(16)));
    Vec4 c __attribute__((aligned(16)));
    Mtx m __attribute__((aligned(16)));
    Vec4 v100 __attribute__((aligned(16)));
    V4 pts[4] __attribute__((aligned(16)));
    Scr scr __attribute__((aligned(16)));
    Vec4 q __attribute__((aligned(16)));
    Vec4 b __attribute__((aligned(16)));
    Vec4 a __attribute__((aligned(16)));
    Wrk *w;
    Gam *g;
    u8 *src;
    s32 r;
    void *o;
    s32 i;
    u8 *cp;
    Vec4 *p;
    s8 *uv;
    s8 *u1;
    s32 hw; /* rg-override: marker half width (0xD0 = 13 px) */


    if (arg->f1C <= 0.0f) return;
    w = GetDrawCtx_15de80();
    g = GetCurrentScene_1f5be0();
    ViewStackPush_144430(w);
    cp = w->pF20;
    src = cp + 0x14;
    memcpy(&save, src, 0x3C);
    memcpy(&tmp, src, 0x3C);
    CameraObjCtor_177430((Cam *)buf);
    ((Cam *)buf)->f14(42.5f);
    { V4 *pb = (V4 *)&b; *pb = D_0047F9B0; }
    b.y = 30.0f;
    b.z = 40.0f;
    b.x = 0.0f;
    { V4 *pa = (V4 *)&a; *pa = D_0047F9A0; }
    a.x = 0.0f;
    a.y = 0.0f;
    a.z = 0.0f;
    VEC(buf, 0xF0) = b;
    VEC(buf, 0x60) = b;
    VEC(buf, 0xE0) = a;
    VEC(buf, 0x50) = a;
    CameraTweenStep_1771a0((Cam *)buf);
    /* rg-override: stage 2 keeps the compass in the bottom-left corner (left anchor about
       the screen's left edge, GS pixel 1792 = 2048 - 256) */
    tmp.f24 = rg_layout_active() ? 1792.0f + (D_0047D830 - 1792.0f) * rg_hud_xscale_world() : D_0047D830;
    tmp.f28 = D_0047D834;
    tmp.f0 = D_0047D1FC * ((Cam *)buf)->f10() / 180.0f;
    ViewSetScreenMatrix_1562b0(cp, &tmp);
    ViewSetPerspective_1564a0(cp, D_0047D838, ((unsigned char)IsWidescreen_1c6ab0()) ? rg_aspect_d() : 0.75f, tmp.fC, tmp.f10, tmp.fC, tmp.f10);
    CameraSetViewFromCameraBase_142dd0(w, buf, 0, 0);
    DrawListAddCameraMatrixPacket_1481b0(w);
    DrawListAddViewPacket_1482e0(w);
    sel.a = -1;
    sel.b = 0;
    LightStateInit_156b50(&sel);
    r = LightStatePush_1429f0(w, &sel, 1);
    *(V4 *)&c = D_0047F9C0;
    sel.v10 = c;
    sel.vD0 = c;
    sel.vC0 = c;
    DrawListAddLightPacket_148120(w);
    DrawListAddTexLoad_1418c0(w, arg->f4, 1.0f);
    arg->p0->f170 = arg->f1C;
    ModelDraw_14f6d0(arg->p0, w, arg->p0->sub120);
    LightStateSetCurrent_142920(w, r);
    FrameCalcWorldMatrix_148ff0(ModelGetRootFrame_1511a0(arg->p0), &m);
    v100 = arg->p0->v180;
    GetDrawCtxNameTable_15de40();
    if (arg->f8 != 0) {
        o = DrawListBeginPrim_141b00(w);
        *(P4 *)pts = *(P4 *)D_00453E10;
        GsPktSetDefaultState_13fa80(o);
        GsPktEnableZTest_13e460(o, 0);
        GsPktSetBlendMode_13e4f0(o, 1);
        GsPktSetAlphaBlend_13e500(o, 1);
        GsPktSetAlphaTestFunc_13e4c0(o, 1, 0);
        GsPktSetTextured_13e400(o, 1);
        GsPktSetZWriteMask_13e430(o, 1);
        GsPktSetOriginMode_13e2f0(o, 1);
        GsPktSetTexFilter_13e3d0(o, 1);
        GsPktOpenPrim_13f730(o, 6);
        GsPktSetTexture_13ec00(o, arg->f8);
        GsPktSetRGBAQ_13ee40(o, 0x80, 0x80, 0x80, (s32)(96.0f * arg->f1C));
        hw = ((unsigned char)IsWidescreen_1c6ab0()) ? (s32)(208.0f * rg_hud_xscale_world()) : 0xD0;
        i = 0;
        do {
            p = (Vec4 *)&pts[i];
            sceVu0ScaleVectorXYZ(p, p, 4.5f);
            MtxMulVec4_10a8c0(p, &m, p);
            VecAdd_13be20(&q, &v100, &((Vec4 *)pts)[i]);
            q.y += D_0047D288;
            ProjectToScreen_15d340(&scr, &q);
            uv = D_0047F9D0[i];
            u1 = uv + 1;
            GsPktSetUV_13ed60(o, uv[0], uv[1]);
            GsPktSetXYZ_13ef10(o, scr.x - hw, scr.y - 0xD0, 0);
            GsPktSetUV_13ed60(o, uv[0] + 0x1F, *u1 + 0x1F);
            GsPktSetXYZ_13ef10(o, scr.x + hw, scr.y + 0xD0, 0);
            i++;
        } while (i < 4);
        GsPktClose_13f5b0(o);
        DrawListEndPrim_141a20(w);
    }
    ViewSetScreenMatrix_1562b0(cp, &save);
    ViewStackPop_1443e0(w);
    CameraSetViewFromCameraBase_142dd0(w, ObjRecGetLiveObject_1c3bc0(g, g->f4344), 0, 0);
    DrawListAddCameraMatrixPacket_1481b0(w);
}
/* rg-override: widescreen stage 2 (src/settings/rg_layout.h): a world-anchored element
 * (positioned by projecting a world point; it narrows itself about that point with
 * rg_hud_xscale_world()), so the 2D layout transform leaves its packets alone */
void CompassHudRender_370fb0(Arg *arg)
{
    rg_layout_suppress(1);
    rg_wide_CompassHudRender_370fb0(arg);
    rg_layout_suppress(0);
}

}
