#include "types.h"
typedef unsigned __int128 u128;

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

extern void GsPktSetOriginMode_13e2f0(s32, s32);
extern void GsPktSetGouraud_13e3b0(s32, s32);
extern void GsPktSetUseUV_13e3e0(s32, s32);
extern void GsPktSetTextured_13e400(s32, s32);
extern void GsPktSetZWriteMask_13e430(s32, s32);
extern void GsPktEnableZTest_13e460(s32, s32);
extern void GsPktEnableAlphaTest_13e4d0(s32, s32);
extern void GsPktSetAlphaBlend_13e500(s32, s32);
extern void GsPktSetTexture_13ec00(s32, s32);
extern void GsPktSetUV_13ed60(s32, s32, s32);
extern void GsPktSetRGBAQVec_13edd0(s32, s32 *);
extern void GsPktSetXYZ_13ef10(s32, s32, s32, s32);
extern void GsPktClose_13f5b0(s32);
extern void GsPktOpenPrim_13f730(s32, s32);
extern void DrawListAddTexLoad_1418c0(Sys *, s32, f32);
extern void DrawListEndPrim_141a20(Sys *);
extern s32 DrawListBeginPrim_141b00(Sys *);
extern s32 NameTableFindByName_159fb0(s32, char *, s32);
extern s32 CameraProjectBillboardRect_15cde0(P4 *, P4 *, u128 *, s32, f32, f32);
extern s32 ProjectToScreenOffset_15d160(P4 *, u128 *);
extern Sys *GetDrawCtx_15de80(void);
extern s32 IsWidescreen_1c6ab0();
extern void TargetRefResolve_2e5ed0(Obj *, s32);
extern s32 TargetRefGetPos_2e6a60(Obj *, u128 *);
extern u8 D_00452660[];
extern u8 D_004526A0[];
extern char D_004623E0[];
extern f32 D_0047D7EC;
extern const f32 D_0047D868 __attribute__((section(".sdata")));
extern const f32 D_0047D86C __attribute__((section(".sdata")));

void TargetSlotDraw_320b00(Obj *o) {
    u128 q;
    u128 v;
    P4 a;
    P4 b;
    Tbl A;
    Tbl B;
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
        sys = GetDrawCtx_15de80();
        h = sys->f3BA0;
        v = o->q50;
        if (ProjectToScreenOffset_15d160(&a, &v) == 0) {
            return;
        }
        DrawListAddTexLoad_1418c0(sys, 0x32B, 1.0f);
        g = DrawListBeginPrim_141b00(sys);
        GsPktSetOriginMode_13e2f0(g, 1);
        GsPktSetTextured_13e400(g, 1);
        GsPktSetZWriteMask_13e430(g, 1);
        GsPktSetAlphaBlend_13e500(g, 1);
        GsPktEnableAlphaTest_13e4d0(g, 1);
        GsPktEnableZTest_13e460(g, 0);
        GsPktSetUseUV_13e3e0(g, 1);
        GsPktSetGouraud_13e3b0(g, 0);
        t = NameTableFindByName_159fb0(h, D_004623E0, 0x32B);
        GsPktOpenPrim_13f730(g, 6);
        GsPktSetTexture_13ec00(g, t);
        A = *(Tbl *)D_00452660;
        B = *(Tbl *)D_004526A0;
        r = 5.0f + (o->f3C + 120.0f * o->f38);
        sc = 1.0f;
        if (IsWidescreen_1c6ab0() != 0) {
            sc = 0.75f;
        }
        yo = (s32)D_0047D868;
        o->f60[3] = o->f60[2];
        o->f60[2] = o->f60[1];
        o->f60[1] = o->f60[0];
        o->f60[0] = (s32)(10.0f * o->f40) << 4;
        ho = (s32)D_0047D86C;
        for (i = 0; i < 4; i++) {
            if (CameraProjectBillboardRect_15cde0(&a, &b, &v, 0, r, r) == 0) {
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
