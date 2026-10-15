#include "types.h"
#pragma opt_dead_assignments off

typedef struct Tex {
    s16 x0;
    s16 x2;
    s16 x4;
    s16 x6;
    char name[0x20];                    /* 0x08 */
    u16 x28;
    u8 x2A;
    u8 x2B;
    s32 x2C;
    s16 x30;
    u8 x32;
    u8 x33;
    s16 x34;
    s16 x36;
    u64 x38;
    u64 x40;
    u64 x48;
    struct { f32 x, y, z, w; } x50;
    s32 x60;
    s32 x64;
} Tex;

typedef struct Alpha {
    u8 a : 2;
    u8 b : 2;
    u8 c : 2;
    u8 d : 2;
    u8 pad1[3];
    u8 fix;
} Alpha;

typedef struct Rect {
    s32 x0;
    s32 y0;
    s32 x1;
    s32 y1;
} Rect;

typedef struct Arg {
    Tex *t0;
    Tex *t1;
    s32 x8;
    f32 xC;
    f32 x10;
    f32 x14;
} Arg;

extern "C" {
s32 GetDrawCtx_15de80(void);
void NameTableNodeCtor_15ae50(Tex *);
void DrawEnvGetFrameTexDesc_144cc0(s32, Tex *);
void DrawEnvGetFrameRect_145040(s32, Rect *);
void DrawEnvPush_144830(s32);
void DrawEnvPop_144800(s32);
void DrawEnvSetFrameFromDesc_144fe0(s32, Tex *, s32);
void DrawListAddEnv_1421d0(s32);
s32 DrawListBeginPrim_141b00(s32);
void DrawListEndPrim_141a20(s32);
void GsPktSetOriginMode_13e2f0(s32, s32);
void GsPktEnableZTest_13e460(s32, s32);
void GsPktSetZWriteMask_13e430(s32, s32);
void GsPktSetZTest_13e450(s32, s32);
void GsPktSetAlphaBlend_13e500(s32, s32);
void GsPktEnableAlphaTest_13e4d0(s32, s32);
void GsPktSetTextured_13e400(s32, s32);
void GsPktSetAlphaTestFunc_13e4c0(s32, s32, s32);
void GsPktSetAlphaReg_13e4e0(s32, Alpha *);
void GsPktSetBlendMode_13e4f0(s32, s32);
void GsPktOpenPrim_13f730(s32, s32);
void GsPktSetTexture_13ec00(s32, Tex *);
void GsPktSetRGBAQ_13ee40(s32, s32, s32, s32, s32);
void GsPktSetXYZPixel_13f110(s32, s32, s32, s32);
void GsPktClose_13f5b0(s32);
void GsPktSpriteSplitU_17adf0(s32, s32, s32, s32, s32, s32, s32, s32, s32);
}


extern "C" void GlareFilterDrawMaybe_17a0d0(Arg *arg)
{
    Tex t1;
    Tex t2;
    Tex work;
    Rect r1;
    Rect r0;
    s32 x0;
    s32 gp;
    s32 lo;
    s32 hi;
    s32 c;
    s32 w;
    s32 pk;
    f32 k;
    s32 dh;
    s32 y1;
    s32 x1;
    s32 y0;
    s32 dw;
    f32 kc;
    s32 o;
    s32 i;
    s32 h;

    if (arg->t0 == 0 || arg->t1 == 0) {
        return;
    }
    gp = GetDrawCtx_15de80();
    t1 = *arg->t0;
    t2 = *arg->t1;
    {
    Tex *tp[2] = {0};
    Alpha al1;
    Alpha al2;
    tp[0] = &t1;
    tp[1] = &t2;
    al1.a = 2;
    al1.b = 0;
    al1.c = 2;
    al1.d = 1;
    al1.fix = 0x80;
    al2.a = 0;
    al2.b = 2;
    al2.c = 2;
    al2.d = 1;
    al2.fix = 0x80;
    NameTableNodeCtor_15ae50(&work);
    DrawEnvGetFrameTexDesc_144cc0(gp, &work);
    DrawEnvGetFrameRect_145040(gp, &r1);
    DrawEnvPush_144830(gp);
    DrawEnvSetFrameFromDesc_144fe0(gp, tp[0], 0);
    DrawListAddEnv_1421d0(gp);
    DrawEnvGetFrameRect_145040(gp, &r0);

    pk = DrawListBeginPrim_141b00(gp);
    GsPktSetOriginMode_13e2f0(pk, 0);
    GsPktEnableZTest_13e460(pk, 0);
    GsPktSetZWriteMask_13e430(pk, 1);
    GsPktSetZTest_13e450(pk, 0);
    GsPktSetAlphaBlend_13e500(pk, 0);
    GsPktEnableAlphaTest_13e4d0(pk, 0);
    GsPktSetTextured_13e400(pk, 0);
    GsPktOpenPrim_13f730(pk, 6);
    GsPktSetRGBAQ_13ee40(pk, 0, 0, 0, 0x80);
    GsPktSetXYZPixel_13f110(pk, r0.y0, r0.x0, 0);
    GsPktSetXYZPixel_13f110(pk, r0.y1, r0.x1, 0);
    GsPktClose_13f5b0(pk);
    DrawListEndPrim_141a20(gp);

    pk = DrawListBeginPrim_141b00(gp);
    GsPktSetOriginMode_13e2f0(pk, 0);
    GsPktEnableZTest_13e460(pk, 0);
    GsPktSetZWriteMask_13e430(pk, 1);
    GsPktSetZTest_13e450(pk, 0);
    GsPktSetAlphaBlend_13e500(pk, 0);
    GsPktEnableAlphaTest_13e4d0(pk, 0);
    GsPktSetTextured_13e400(pk, 0);
    GsPktEnableAlphaTest_13e4d0(pk, 1);
    GsPktSetAlphaTestFunc_13e4c0(pk, 6, arg->x8);
    GsPktSetTextured_13e400(pk, 1);
    GsPktSetAlphaBlend_13e500(pk, 0);
    GsPktOpenPrim_13f730(pk, 6);
    GsPktSetTexture_13ec00(pk, &work);
    GsPktSetRGBAQ_13ee40(pk, 0x80, 0x80, 0x80, 0x80);
    GsPktSpriteSplitU_17adf0(pk, r0.y0 * 16 - 8, r0.x0 * 16 - 8, r0.y1 * 16 - 8, r0.x1 * 16 - 8, 0, 0,
                 (r1.y1 - r1.y0) * 16, (r1.x1 - r1.x0) * 16);
    GsPktClose_13f5b0(pk);
    DrawListEndPrim_141a20(gp);

    DrawEnvSetFrameFromDesc_144fe0(gp, tp[1], 0);
    DrawListAddEnv_1421d0(gp);
    pk = DrawListBeginPrim_141b00(gp);
    w = r0.y1 - r0.y0;
    h = r0.x1 - r0.x0;
    GsPktSetOriginMode_13e2f0(pk, 0);
    GsPktEnableZTest_13e460(pk, 0);
    GsPktSetZWriteMask_13e430(pk, 1);
    GsPktSetZTest_13e450(pk, 0);
    GsPktSetAlphaBlend_13e500(pk, 0);
    GsPktEnableAlphaTest_13e4d0(pk, 0);
    GsPktSetTextured_13e400(pk, 0);
    GsPktSetTextured_13e400(pk, 1);
    GsPktSetAlphaBlend_13e500(pk, 1);
    GsPktSetBlendMode_13e4f0(pk, 8);
    GsPktOpenPrim_13f730(pk, 6);
    GsPktSetTexture_13ec00(pk, tp[0]);
    GsPktSetRGBAQ_13ee40(pk, 0x40, 0x40, 0x40, 0x80);
    GsPktSpriteSplitU_17adf0(pk, r0.y0 * 16 - 4, r0.x0 * 16 - 4, r0.y1 * 16 - 4, r0.x1 * 16 - 4, 0, 0,
                 (r0.y1 - r0.y0) * 16, (r0.x1 - r0.x0) * 16);
    GsPktClose_13f5b0(pk);
    GsPktSetAlphaBlend_13e500(pk, 1);
    GsPktSetAlphaReg_13e4e0(pk, &al1);
    GsPktOpenPrim_13f730(pk, 6);
    GsPktSetTexture_13ec00(pk, tp[0]);
    GsPktSetRGBAQ_13ee40(pk, 0x40, 0x40, 0x40, 0x80);
    GsPktSpriteSplitU_17adf0(pk, r0.y0 * 16 - 4, r0.x0 * 16 - 4, r0.y1 * 16 - 4, r0.x1 * 16 - 4, 0, 0,
                 (r0.y1 - r0.y0) * 16, (r0.x1 - r0.x0) * 16);
    GsPktClose_13f5b0(pk);
    GsPktSetOriginMode_13e2f0(pk, 0);
    GsPktEnableZTest_13e460(pk, 0);
    GsPktSetZWriteMask_13e430(pk, 1);
    GsPktSetZTest_13e450(pk, 0);
    GsPktSetAlphaBlend_13e500(pk, 0);
    GsPktEnableAlphaTest_13e4d0(pk, 0);
    GsPktSetTextured_13e400(pk, 0);
    GsPktOpenPrim_13f730(pk, 6);
    GsPktSetRGBAQ_13ee40(pk, 0, 0, 0, 0);
    GsPktSetXYZPixel_13f110(pk, -1, -1, 0);
    GsPktSetXYZPixel_13f110(pk, w + 1, 1, 0);
    GsPktSetXYZPixel_13f110(pk, -1, -1, 0);
    GsPktSetXYZPixel_13f110(pk, 1, h + 1, 0);
    GsPktSetXYZPixel_13f110(pk, w - 1, -1, 0);
    GsPktSetXYZPixel_13f110(pk, w + 1, h + 1, 0);
    GsPktSetXYZPixel_13f110(pk, -1, h - 1, 0);
    GsPktSetXYZPixel_13f110(pk, w + 1, h + 1, 0);
    GsPktClose_13f5b0(pk);
    DrawListEndPrim_141a20(gp);

    y0 = r0.y0 * 16 - 4;
    x0 = r0.x0 * 16 - 4;
    k = 24.0f * arg->x10;
    y1 = r0.y1 * 16 - 4;
    x1 = r0.x1 * 16 - 4;
    kc = 128.0f * arg->xC;
    DrawEnvSetFrameFromDesc_144fe0(gp, tp[1], 0);
    DrawListAddEnv_1421d0(gp);
    for (i = 0; i < 5; i++) {
        pk = DrawListBeginPrim_141b00(gp);
        GsPktSetOriginMode_13e2f0(pk, 0);
        GsPktEnableZTest_13e460(pk, 0);
        GsPktSetZWriteMask_13e430(pk, 1);
        GsPktSetZTest_13e450(pk, 0);
        GsPktSetAlphaBlend_13e500(pk, 0);
        GsPktEnableAlphaTest_13e4d0(pk, 0);
        GsPktSetTextured_13e400(pk, 0);
        GsPktSetTextured_13e400(pk, 1);
        o = (s32)((f32)(i + 1) * k);
        hi = o - 8;
        lo = -8 - o;
        c = (s32)(kc * ((f32)(5 - i) / 5.0f));
        GsPktSetAlphaBlend_13e500(pk, 1);
        GsPktSetAlphaReg_13e4e0(pk, &al2);
        GsPktOpenPrim_13f730(pk, 6);
        GsPktSetTexture_13ec00(pk, tp[1]);
        GsPktSetRGBAQ_13ee40(pk, c, c, c, 0x80);
        dw = (r0.y1 - r0.y0 - 1) * 16;
        dh = (r0.x1 - r0.x0 - 1) * 16;
        GsPktSpriteSplitU_17adf0(pk, y0 + hi / 2, x0 + hi / 2, y1 + hi / 2, x1 + hi / 4, 0x10, 0x10, dw, dh);
        GsPktSpriteSplitU_17adf0(pk, y0 + lo / 2, x0 + lo / 2, y1 + lo / 2, x1 + lo / 4, 0x10, 0x10, dw, dh);
        GsPktSpriteSplitU_17adf0(pk, y0 + lo, x0 + hi, y1 + lo, x1 + hi, 0x10, 0x10, dw, dh);
        GsPktSpriteSplitU_17adf0(pk, y0 + hi, x0 + lo, y1 + hi, x1 + lo, 0x10, 0x10, dw, dh);
        GsPktClose_13f5b0(pk);
        DrawListEndPrim_141a20(gp);
    }
    DrawEnvPop_144800(gp);
    DrawListAddEnv_1421d0(gp);
    pk = DrawListBeginPrim_141b00(gp);
    GsPktSetOriginMode_13e2f0(pk, 0);
    GsPktEnableZTest_13e460(pk, 0);
    GsPktSetZWriteMask_13e430(pk, 1);
    GsPktSetZTest_13e450(pk, 0);
    GsPktSetAlphaBlend_13e500(pk, 0);
    GsPktEnableAlphaTest_13e4d0(pk, 0);
    GsPktSetTextured_13e400(pk, 0);
    GsPktSetOriginMode_13e2f0(pk, 0);
    GsPktSetZWriteMask_13e430(pk, 1);
    GsPktEnableZTest_13e460(pk, 0);
    GsPktSetZTest_13e450(pk, 0);
    GsPktSetAlphaTestFunc_13e4c0(pk, 0, 0);
    GsPktSetAlphaBlend_13e500(pk, 1);
    GsPktSetAlphaReg_13e4e0(pk, &al2);
    GsPktSetTextured_13e400(pk, 1);
    GsPktOpenPrim_13f730(pk, 6);
    GsPktSetTexture_13ec00(pk, tp[1]);
    c = (s32)(128.0f * arg->x14);
    if (c > 255) {
        c = 0xFF;
    }
    if (c < 0) {
        c = 0;
    }
    GsPktSetRGBAQ_13ee40(pk, c, c, c, 0x80);
    GsPktSpriteSplitU_17adf0(pk, 0, 0, (r1.y1 - r1.y0) * 16, (r1.x1 - r1.x0) * 16, 0x10, 0x10,
                 (r0.y1 - r0.y0 - 1) * 16, (r0.x1 - r0.x0 - 1) * 16);
    GsPktClose_13f5b0(pk);
    DrawListEndPrim_141a20(gp);
}
}
