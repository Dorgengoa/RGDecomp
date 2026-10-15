#include "types.h"

typedef struct Alpha {
    u8 a : 2;
    u8 b : 2;
    u8 c : 2;
    u8 d : 2;
    u8 pad1[3];
    u8 fix;
} Alpha;

typedef struct Tex {
    u8 pad0[0x38];
    u16 tbp : 14;
    u16 tbph : 2;
    u16 g0 : 4;
    u16 g4 : 6;
    u16 g10 : 6;
    u8 pad3C[4];
    u16 f0 : 5;
    u16 f5 : 1;
    u16 f6 : 3;
    u16 f9 : 7;
    u8 pad42[0x70 - 0x42];
} Tex;

typedef struct TexA {
    u8 pad0[0x38];
    u16 tbp : 14;
    u16 tbph : 2;
    u16 g0 : 4;
    u16 g4 : 6;
    u16 g10 : 6;
    u8 pad3C[0x68 - 0x3C];
} TexA;

typedef struct Rect {
    s32 x, y, h, w;
} Rect;

typedef struct Ctx {
    u8 pad0[4];
} Ctx;

void GsPktSetOriginMode_13e2f0(s32, s32);
void GsPktSetTextured_13e400(s32, s32);
void GsPktSetZWriteMask_13e430(s32, s32);
void GsPktSetZTest_13e450(s32, s32);
void GsPktEnableZTest_13e460(s32, s32);
void GsPktEnableAlphaTest_13e4d0(s32, s32);
void GsPktSetAlphaReg_13e4e0(s32, Alpha *);
void GsPktSetAlphaBlend_13e500(s32, s32);
void GsPktSetTexture_13ec00(s32, void *);
void GsPktSetTexa_13eca0(s32, s64);
void GsPktSetUV_13ed60(s32, s32, s32);
void GsPktSetUVFixed_13ed90(s32, s32, s32);
void GsPktSetRGBAQ_13ee40(s32, u8, u8, u8, s32);
void GsPktSetXYZPixel_13f110(s32, s32, s32, s32);
void GsPktClose_13f5b0(s32);
void GsPktOpenPrim_13f730(s32, s32);
void DrawListEndPrim_141a20(Ctx *);
s32 DrawListBeginPrim_141b00(Ctx *);
void DrawListAddEnv_1421d0(Ctx *);
void DrawEnvPop_144800(Ctx *);
void DrawEnvPush_144830(Ctx *);
void DrawEnvGetFrameTexDesc_144cc0(Ctx *, Tex *);
void DrawEnvSetFrameFromDesc_144fe0(Ctx *, void *, s32);
void DrawEnvGetFrameRect_145040(Ctx *, Rect *);
void NameTableNodeSetImage_15a640(Tex *, s32, void *, s32, s32, s32, s32, s32, s64, s64);
void NameTableNodeCtor_15ae50(Tex *);
Ctx *GetDrawCtx_15de80(void);
extern u8 D_00459618[];

void ScreenColorFilterMaybe_179c60(s32 r, s32 g, s32 b)
{
    Alpha al;
    TexA ta;
    Tex tb;
    Rect rc;
    Tex tc;
    Ctx *ctx;
    s32 d;
    s32 i;
    s32 j;
    s32 d2;
    s32 hh;
    s32 h2;
    s32 v2;
    s32 wd;

    ctx = GetDrawCtx_15de80();
    NameTableNodeCtor_15ae50((Tex *)&ta);
    NameTableNodeCtor_15ae50(&tb);
    DrawEnvGetFrameRect_145040(ctx, &rc);
    DrawEnvGetFrameTexDesc_144cc0(ctx, &tb);
    ta.g4 = 0x3A;
    NameTableNodeCtor_15ae50(&tc);
    tc.f5 = 0;
    tc.f6 = 0;
    NameTableNodeSetImage_15a640(&tc, 0, D_00459618, 0, rc.w - rc.y, (rc.h - rc.x) << 1, 0x10, 0, 0, 0);
    tc.tbp = tb.tbp;
    DrawEnvPush_144830(ctx);
    DrawEnvSetFrameFromDesc_144fe0(ctx, &tc, 0);
    DrawListAddEnv_1421d0(ctx);
    d = DrawListBeginPrim_141b00(ctx);
    GsPktSetOriginMode_13e2f0(d, 0);
    GsPktEnableZTest_13e460(d, 0);
    GsPktSetZWriteMask_13e430(d, 1);
    GsPktSetZTest_13e450(d, 0);
    GsPktSetAlphaBlend_13e500(d, 0);
    GsPktEnableAlphaTest_13e4d0(d, 0);
    GsPktSetTextured_13e400(d, 0);
    GsPktSetTextured_13e400(d, 1);
    GsPktOpenPrim_13f730(d, 6);
    GsPktSetTexa_13eca0(d, (s64)0x80 << 32);
    GsPktSetTexture_13ec00(d, &tc);
    GsPktSetRGBAQ_13ee40(d, 0x80, 0x80, 0x80, 0x80);
    wd = rc.w - rc.y;
    hh = rc.h - rc.x;
    h2 = hh << 1;
    v2 = (hh << 5) + 9;
    for (i = 0; i < wd; i += 16) {
        GsPktSetUVFixed_13ed90(d, (i << 4) + 8, 8);
        GsPktSetXYZPixel_13f110(d, i + 8, 0, 0);
        GsPktSetUVFixed_13ed90(d, ((i + 8) << 4) + 8, v2);
        GsPktSetXYZPixel_13f110(d, i + 16, h2, 0);
    }
    GsPktClose_13f5b0(d);
    DrawListEndPrim_141a20(ctx);
    DrawEnvPop_144800(ctx);
    DrawListAddEnv_1421d0(ctx);
    al.a = 0;
    al.fix = 0;
    al.b = 2;
    al.c = 1;
    al.d = 2;
    d2 = DrawListBeginPrim_141b00(ctx);
    GsPktSetOriginMode_13e2f0(d2, 0);
    GsPktEnableZTest_13e460(d2, 0);
    GsPktSetZWriteMask_13e430(d2, 1);
    GsPktSetZTest_13e450(d2, 0);
    GsPktSetAlphaBlend_13e500(d2, 0);
    GsPktEnableAlphaTest_13e4d0(d2, 0);
    GsPktSetTextured_13e400(d2, 0);
    GsPktEnableZTest_13e460(d2, 0);
    GsPktSetAlphaBlend_13e500(d2, 1);
    GsPktSetAlphaReg_13e4e0(d2, &al);
    GsPktSetTextured_13e400(d2, 0);
    GsPktOpenPrim_13f730(d2, 6);
    GsPktSetRGBAQ_13ee40(d2, r, g, b, 0x80);
    for (j = 0; j < rc.w - rc.y; j += 32) {
        GsPktSetUV_13ed60(d2, j, 0);
        GsPktSetXYZPixel_13f110(d2, j, 0, 0);
        GsPktSetUV_13ed60(d2, j + 32, rc.h - rc.x);
        GsPktSetXYZPixel_13f110(d2, j + 32, rc.h - rc.x, 0);
    }
    GsPktClose_13f5b0(d2);
    DrawListEndPrim_141a20(ctx);
}
