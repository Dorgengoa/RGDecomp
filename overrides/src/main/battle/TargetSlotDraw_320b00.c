/* rg-override: replaces game/src/main/battle/TargetSlotDraw_320b00.c sha256 5620ac73114aa8cbb4d50fa5a6c2bd590293a5457a646e9127deb2f179deff8a
 * why: widescreen stage 1 (docs/WIDESCREEN.md "Stage 1"): WIDE width factor rg_hud_xscale() instead of 0.75 (the same value at 16:9) */
/* rgp:protos */
#define RGP_SELF_TargetSlotDraw_320b00 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* rg-override: widescreen stage 1 (src/settings/rg_aspect.h) */
extern float rg_aspect_d(void);
extern float rg_hud_xscale(void);
extern void rg_layout_suppress(int on);
extern float rg_hud_xscale_world(void);
typedef rg_u128 u128;

typedef struct { s32 x, y, z, w; } P4;
typedef struct { s32 r[4][4]; } Tbl;

typedef struct {
    u8 pad0[0x30];
    s32 f30;
    s32 f34;
    f32 f38;
    f32 f3C;
    f32 f40;
    u8 pad44[0x50 - 0x44];
    u128 q50;
    s32 f60[4];
} Obj;

typedef struct {
    u8 pad0[0x3BA0];
    s32 f3BA0;
} Sys;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern u8 D_00452660[];
extern u8 D_004526A0[];
extern char D_004623E0[];
extern f32 D_0047D7EC;
extern const f32 D_0047D868 __attribute__((section(".sdata")));
extern const f32 D_0047D86C __attribute__((section(".sdata")));

static void rg_wide_TargetSlotDraw_320b00(Obj *o) {
    u128 q;
    u128 v;
    P4 a __attribute__((aligned(16)));
    P4 b __attribute__((aligned(16)));
    Tbl A __attribute__((aligned(16)));
    Tbl B __attribute__((aligned(16)));
    Sys *sys;
    s32 h;
    s32 g;
    s32 t;
    f32 r;
    f32 sc;
    s32 i;
    s32 w;
    s32 d;
    s32 *p;
    s32 k;
    s32 yo;
    s32 ho;

    if (o->f34 != 0 && o->f30 != -1) {
        TargetRefResolve_2e5ed0(o, 0);
        if (TargetRefGetPos_2e6a60(o, &q) == 0) {
            return;
        }
        o->q50 = q;
        sys = ((Sys *)GetDrawCtx_15de80());
        h = sys->f3BA0;
        v = o->q50;
        if (ProjectToScreenOffset_15d160(&a, &v) == 0) {
            return;
        }
        DrawListAddTexLoad_1418c0(sys, 0x32B, 1.0f);
        g = ((s32)DrawListBeginPrim_141b00(sys));
        GsPktSetOriginMode_13e2f0(g, 1);
        GsPktSetTextured_13e400(g, 1);
        GsPktSetZWriteMask_13e430(g, 1);
        GsPktSetAlphaBlend_13e500(g, 1);
        GsPktEnableAlphaTest_13e4d0(g, 1);
        GsPktEnableZTest_13e460(g, 0);
        GsPktSetUseUV_13e3e0(g, 1);
        GsPktSetGouraud_13e3b0(g, 0);
        t = ((s32)NameTableFindByName_159fb0(h, D_004623E0, 0x32B));
        GsPktOpenPrim_13f730(g, 6);
        GsPktSetTexture_13ec00(g, t);
        A = *(Tbl *)D_00452660;
        B = *(Tbl *)D_004526A0;
        r = 5.0f + (o->f3C + 120.0f * o->f38);
        sc = 1.0f;
        if (((unsigned char)IsWidescreen_1c6ab0()) != 0) {
            sc = rg_hud_xscale_world();
        }
        yo = (s32)D_0047D868;
        o->f60[3] = o->f60[2];
        o->f60[2] = o->f60[1];
        o->f60[1] = o->f60[0];
        o->f60[0] = (s32)(10.0f * o->f40) << 4;
        ho = (s32)D_0047D86C;
        for (i = 0; i < 4; i++) {
            if (CameraProjectBillboardRect_15cde0(&a, &b, r, r, &v) == 0) {
                continue;
            }
            if (o->f34 != 2) {
                w = b.x - a.x;
                d = b.y - a.y;
                if (w < 640) {
                    k = (640 - w) / 2;
                    a.x -= k;
                    b.x += k;
                }
                if (d < ho) {
                    k = (ho - d) / 2;
                    a.y -= k;
                    b.y += k;
                }
            }
            p = &o->f60[i];
            k = (s32)(D_0047D7EC * (f32)*p);
            GsPktSetRGBAQVec_13edd0(g, B.r[i]);
            GsPktSetUV_13ed60(g, A.r[0][0], A.r[0][1]);
            GsPktSetXYZ_13ef10(g, a.x + (s32)(sc * (f32)(*p - 160)), k + (a.y - yo), 0);
            GsPktSetUV_13ed60(g, A.r[0][0] + A.r[0][2], A.r[0][1] + A.r[0][3]);
            GsPktSetXYZ_13ef10(g, a.x + (s32)(sc * (f32)(*p + 160)), k + (a.y + yo), 0);
            GsPktSetUV_13ed60(g, A.r[1][0], A.r[1][1]);
            GsPktSetXYZ_13ef10(g, b.x + (s32)(sc * (f32)-(*p + 160)), k + (a.y - yo), 0);
            GsPktSetUV_13ed60(g, A.r[1][0] + A.r[1][2], A.r[1][1] + A.r[1][3]);
            GsPktSetXYZ_13ef10(g, b.x + (s32)(sc * (f32)(160 - *p)), k + (a.y + yo), 0);
            GsPktSetUV_13ed60(g, A.r[2][0], A.r[2][1]);
            GsPktSetXYZ_13ef10(g, a.x + (s32)(sc * (f32)(*p - 160)), (b.y - yo) - k, 0);
            GsPktSetUV_13ed60(g, A.r[2][0] + A.r[2][2], A.r[2][1] + A.r[2][3]);
            GsPktSetXYZ_13ef10(g, a.x + (s32)(sc * (f32)(*p + 160)), (b.y + yo) - k, 0);
            GsPktSetUV_13ed60(g, A.r[3][0], A.r[3][1]);
            GsPktSetXYZ_13ef10(g, b.x + (s32)(sc * (f32)-(*p + 160)), (b.y - yo) - k, 0);
            GsPktSetUV_13ed60(g, A.r[3][0] + A.r[3][2], A.r[3][1] + A.r[3][3]);
            GsPktSetXYZ_13ef10(g, b.x + (s32)(sc * (f32)(160 - *p)), (b.y + yo) - k, 0);
        }
        GsPktClose_13f5b0(g);
        DrawListEndPrim_141a20(sys);
    }
}
/* rg-override: widescreen stage 2 (src/settings/rg_layout.h): a world-anchored element
 * (positioned by projecting a world point; it narrows itself about that point with
 * rg_hud_xscale_world()), so the 2D layout transform leaves its packets alone */
void TargetSlotDraw_320b00(Obj *o)
{
    rg_layout_suppress(1);
    rg_wide_TargetSlotDraw_320b00(o);
    rg_layout_suppress(0);
}

