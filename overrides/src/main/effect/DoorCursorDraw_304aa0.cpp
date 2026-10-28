/* rg-override: replaces game/src/main/effect/DoorCursorDraw_304aa0.cpp sha256 fe3472aa7353d77a2f5cd4c16e5e33ccd89b9679f549eab27f1d41e4d3a0f657
 * why: widescreen stage 1 (docs/WIDESCREEN.md "Stage 1"): WIDE width factor rg_hud_xscale() instead of 0.75 (the same value at 16:9) */
#include "types.h"
/* rg-override: widescreen stage 1 (src/settings/rg_aspect.h) */
extern "C" float rg_aspect_d(void);
extern "C" float rg_hud_xscale(void);
extern "C" void rg_layout_suppress(int on);
extern "C" float rg_hud_xscale_world(void);

typedef rg_u128 u128;

typedef struct {
    f32 x, y, z, w;
} V4_304AA0;

class Ent304AA0 {
    u8 pad[0x1B0];
public:
    VC_VPTR_MEMBER;
    
    
    
    void f4(f32 a0) { VCM(void, (void *, f32), 0x18, a0); }
    
    
    void f7() { VCM0(void, 0x24); }
};

extern "C" {
extern void GsPktSetOriginMode_13e2f0(s32, s32);
extern void GsPktSetGouraud_13e3b0(s32, s32);
extern void GsPktSetTexFilter_13e3d0(s32, s32);
extern void GsPktSetTextured_13e400(s32, s32);
extern void GsPktSetZWriteMask_13e430(s32, s32);
extern void GsPktSetZTest_13e450(s32, s32);
extern void GsPktSetAlphaTestFunc_13e4c0(s32, s32, s32);
extern void GsPktEnableAlphaTest_13e4d0(s32, s32);
extern void GsPktSetBlendMode_13e4f0(s32, s32);
extern void GsPktSetAlphaBlend_13e500(s32, s32);
extern void GsPktSetRGBAQVec_13edd0(s32, f32 *);
extern void GsPktSetXYZ_13ef10(s32, s32, s32, s32);
extern void GsPktClose_13f5b0(s32);
extern void GsPktOpenPrim_13f730(s32, s32);
extern void DrawListAddTexLoad_1418c0(s32, s32, f32);
extern void DrawListEndPrim_141a20(s32);
extern s32 DrawListBeginPrim_141b00(s32);
extern s32 DrawEnvGetHeight_1451d0(s32);
extern s32 DrawEnvGetWidth_1451e0(s32);
extern void ModelSetRot_151080(Ent304AA0 *, f32 *);
extern void ModelSetPos_151110(Ent304AA0 *, f32 *);
extern s32 NameTableFindByName_159fb0(s32, void *, s32);
extern void ProjectToScreenOffset_15d160(s32 *, f32 *);
extern s32 GetDrawCtxNameTable_15de40(void);
extern s32 GetDrawCtx_15de80(void);
extern s32 ObjRecGetLiveObject_1c3bc0(u8 *, s32);
extern s32 GetAspectMode_1c6aa0(void);
extern f32 AngleWrap_1cbf30(f32);
extern u8 *GetCurrentScene_1f5be0(void);
extern Ent304AA0 *GetDoorCursorObj_1fdb10(void);
extern u8 D_004621F0[];
extern f32 D_0047F130;
extern f32 D_0047F134;
extern f32 D_0047F138;
extern f32 D_0047F13C;
extern f32 D_0047F140;
extern f32 D_0047F144;
extern f32 D_0047F148;
extern f32 D_0047F14C;
extern f32 D_0047F150;
extern f32 D_0047F154;
extern f32 D_0047F158;
extern f32 D_0047F15C;
extern f32 D_0047F160;
extern f32 D_0047F164;
extern f32 D_0047F168;
extern f32 D_0047F16C;
extern f32 D_0047D858;
}

static void rg_wide_DoorCursorDraw_304aa0(u8 *o) {
    V4_304AA0 V110 __attribute__((aligned(16)));
    V4_304AA0 V100 __attribute__((aligned(16)));
    s32 sF0[4] __attribute__((aligned(16)));
    s32 sE0[4] __attribute__((aligned(16)));
    s32 D0[4] __attribute__((aligned(16)));
    s32 C0[4] __attribute__((aligned(16)));
    V4_304AA0 col __attribute__((aligned(16)));
    V4_304AA0 vA0 __attribute__((aligned(16)));
    f32 v90[4] __attribute__((aligned(16)));
    Ent304AA0 *e;
    s32 mgr;
    s32 c;
    s32 W;
    s32 H;
    f32 f20;
    s32 i;
    f32 a;
    s32 w;
    s32 h;
    f32 *p;
    f32 r;
    u8 *g;
    f32 *pf;

    if (*(s16 *)(o + 0x1E) == 0) {
        return;
    }
    if (*(s16 *)(o + 0x1E) == 6) {
        return;
    }
    e = GetDoorCursorObj_1fdb10();
    if (e == 0) {
        return;
    }
    mgr = GetDrawCtx_15de80();
    pf = (f32 *)&V110;
    pf[0] = D_0047F140;
    pf[1] = D_0047F144;
    pf[2] = D_0047F148;
    pf[3] = D_0047F14C;
    V110.x = *(f32 *)(o + 0x0);
    V110.y = *(f32 *)(o + 0x4);
    V110.z = *(f32 *)(o + 0x8);
    pf = (f32 *)&V100;
    pf[0] = D_0047F150;
    pf[1] = D_0047F154;
    pf[2] = D_0047F158;
    pf[3] = D_0047F15C;
    V100.x = *(f32 *)(o + 0x0);
    V100.y = *(f32 *)(o + 0x4) + *(f32 *)(o + 0xC);
    V100.z = *(f32 *)(o + 0x8);
    DrawListAddTexLoad_1418c0(mgr, 0x284, 1.0f);
    *(f32 *)((u8 *)e + 0x448) = *(f32 *)(o + 0x84) / 128.0f;
    pf = (f32 *)&vA0;
    pf[0] = D_0047F130;
    pf[1] = D_0047F134;
    pf[2] = D_0047F138;
    pf[3] = D_0047F13C;
    vA0.x = V100.x;
    vA0.y = V100.y - 5.0f;
    vA0.z = V100.z;
    ModelSetPos_151110(e, &vA0.x);
    r = AngleWrap_1cbf30(D_0047D858 * (f32)(*(s16 *)(o + 0x20) % 120) / 120.0f);
    {
        u8 *p_ = (u8 *)v90;
        u32 n_ = 0x10;
        if (p_) {
            while (n_) {
                *p_ = 0;
                n_--;
                p_++;
            }
        }
    }
    v90[1] = r;
    v90[0] = 0.0f;
    v90[2] = 0.0f;
    ModelSetRot_151080(e, v90);
    e->f4(1.0f);
    e->f7();
    g = GetCurrentScene_1f5be0();
    ObjRecGetLiveObject_1c3bc0(g, *(s32 *)(g + 0x4344));
    c = DrawListBeginPrim_141b00(mgr);
    W = DrawEnvGetWidth_1451e0(mgr) << 4;
    H = DrawEnvGetHeight_1451d0(mgr) << 4;
    ProjectToScreenOffset_15d160(sF0, &V110.x);
    ProjectToScreenOffset_15d160(sE0, &V100.x);
    if (sE0[2] > 0) {
        f20 = 30.0f;
        if (GetAspectMode_1c6aa0() == 1) {
            f20 = f20 * rg_hud_xscale_world();
        }
        NameTableFindByName_159fb0(GetDrawCtxNameTable_15de40(), D_004621F0, 0x32B);
        GsPktSetOriginMode_13e2f0(c, 0);
        GsPktEnableAlphaTest_13e4d0(c, 1);
        GsPktSetAlphaTestFunc_13e4c0(c, 6, 1);
        GsPktSetGouraud_13e3b0(c, 1);
        GsPktSetTexFilter_13e3d0(c, 1);
        GsPktSetAlphaBlend_13e500(c, 1);
        GsPktSetBlendMode_13e4f0(c, 2);
        GsPktSetTextured_13e400(c, 0);
        GsPktSetZTest_13e450(c, 0);
        GsPktSetZWriteMask_13e430(c, 1);
        pf = (f32 *)&col;
        pf[0] = D_0047F160;
        pf[1] = D_0047F164;
        pf[2] = D_0047F168;
        pf[3] = D_0047F16C;
        for (i = 0; i < 2; i++) {
            a = *(f32 *)(o + 0x14 + i * 4);
            if (a <= 1.0f) {
                continue;
            }
        *(u128 *)D0 = *(u128 *)sF0;
        w = (s32)(8.0f * f20 * a);
        D0[0] = D0[0] - w;
        h = (s32)(320.0f * a);
        D0[1] = D0[1] - h;
        *(u128 *)C0 = *(u128 *)sF0;
        C0[0] = C0[0] + w;
        C0[1] = C0[1] + h;
            if (D0[0] < W && D0[1] < H && C0[0] >= 0 && C0[1] >= 0) {
                GsPktOpenPrim_13f730(c, 2);
                GsPktSetRGBAQVec_13edd0(c, &col.x);
                GsPktSetXYZ_13ef10(c, D0[0], D0[1], sF0[2]);
                GsPktSetXYZ_13ef10(c, C0[0], D0[1], sF0[2]);
                GsPktSetXYZ_13ef10(c, sF0[0], C0[1], sF0[2]);
                GsPktSetXYZ_13ef10(c, D0[0], D0[1], sF0[2]);
                D0[0] = D0[0] - 16;
                D0[1] = D0[1] - 16;
                C0[0] = C0[0] + 16;
                C0[1] = C0[1] + 16;
                GsPktSetXYZ_13ef10(c, D0[0], D0[1], sF0[2]);
                GsPktSetXYZ_13ef10(c, C0[0], D0[1], sF0[2]);
                GsPktSetXYZ_13ef10(c, sF0[0], C0[1], sF0[2]);
                GsPktSetXYZ_13ef10(c, D0[0], D0[1], sF0[2]);
                GsPktClose_13f5b0(c);
            }
        }
        for (i = 0; i < 12; i++) {
            p = (f32 *)(o + 0x24 + i * 4);
            if (*p <= 0.0f) {
                continue;
            }
            a = *(f32 *)(o + 0x54 + i * 4);
            if (a <= 1.0f) {
                continue;
            }
            *(u128 *)D0 = *(u128 *)sF0;
            w = (s32)(8.0f * f20 * a);
            D0[0] = D0[0] - w;
            h = (s32)(320.0f * a);
            D0[1] = D0[1] - h;
            *(u128 *)C0 = *(u128 *)sF0;
            C0[0] = C0[0] + w;
            C0[1] = C0[1] + h;
            if (D0[0] < W && D0[1] < H && C0[0] >= 0 && C0[1] >= 0) {
                GsPktOpenPrim_13f730(c, 2);
                col.w = *p;
                GsPktSetRGBAQVec_13edd0(c, &col.x);
                GsPktSetXYZ_13ef10(c, D0[0], D0[1], sF0[2]);
                GsPktSetXYZ_13ef10(c, C0[0], D0[1], sF0[2]);
                GsPktSetXYZ_13ef10(c, sF0[0], C0[1], sF0[2]);
                GsPktSetXYZ_13ef10(c, D0[0], D0[1], sF0[2]);
                GsPktClose_13f5b0(c);
            }
        }
    }
    DrawListEndPrim_141a20(mgr);
}
/* rg-override: widescreen stage 2 (src/settings/rg_layout.h): a world-anchored element
 * (positioned by projecting a world point; it narrows itself about that point with
 * rg_hud_xscale_world()), so the 2D layout transform leaves its packets alone */
extern "C" void DoorCursorDraw_304aa0(u8 *o)
{
    rg_layout_suppress(1);
    rg_wide_DoorCursorDraw_304aa0(o);
    rg_layout_suppress(0);
}

