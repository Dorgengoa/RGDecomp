#include "types.h"

typedef struct V2 {
    f32 x;
    f32 y;
} V2;

typedef struct V9 {
    V2 v[9];
} V9;

typedef struct Title {
    u8 pad0[0xC];
    s32 tex;
    u8 pad10[8];
    f32 x18;
    f32 x1C;
    f32 x20;
    f32 x24;
    f32 fade;
    s32 x2C;
    s32 cur;
    char names[14][0x40];
    f32 alpha[14];
    s32 x3EC[14];
    s32 n;
    s32 x428;
    s32 pad42C;
    s32 x430;
    f32 x434;
} Title;

typedef struct Game {
    u8 pad0[0x3BA0];
    s32 mgr;
} Game;

extern Title D_004E8960;
extern f32 D_0045B078[];
extern f32 D_00453840[];
extern u8 D_004B2570[];
extern char D_004627F0[];
extern char D_00462810[];
extern char D_00462828[];
extern f32 D_0047D1FC;
extern f32 D_0047D904;
extern f32 D_0047DA38;
extern f32 D_0047DC98;
extern f32 D_0047DCD4;
extern f32 D_0047DCD8;
extern f32 D_0047DCDC;
extern u8 D_0047F654;
extern f32 D_0047F658;
extern u8 D_0047F65C;
extern s32 D_00482D78;
extern f32 D_00482D7C;
extern f32 D_00482D80;
extern f32 D_00482D84;
extern f32 D_00482D88;
extern char *D_00482D8C;

Game *GetDrawCtx_15de80(void);
s32 GetLoadingResReady_1f69c0(void);
void PadUpdateVibration_184250(void *, s32);
void PadUpdate_1843a0(void *);
s32 PadIsAnalogMode_184960(void *);
s32 PadIsTriggered_1839f0(void *, s32);
void PauseReasonDrawMaybe_2f5c40(s32);
s32 LoadingScreenTryFinish_3430c0(void);
void *SceneSoundGetSlot0HandleCur_207df0(void);
void SoundPlayScaledVolume_1b9520(void *, s32, f32, s32);
s32 DoubleGreaterEqual_100230(f64, f64);
void DrawListAddTexLoad_1418c0(Game *, s32, f32);
s32 NameTableFindByName_159fb0(s32, char *, s32);
s32 DrawListBeginPrim_141b00(Game *);
void GsPktSetOriginMode_13e2f0(s32, s32);
void GsPktSetTextured_13e400(s32, s32);
void GsPktSetAlphaBlend_13e500(s32, s32);
void GsPktSetBlendMode_13e4f0(s32, s32);
void GsPktEnableAlphaTest_13e4d0(s32, s32);
void GsPktSetTexFilter_13e3d0(s32, s32);
void GsPktSetZWriteMask_13e430(s32, s32);
void GsPktEnableZTest_13e460(s32, s32);
f32 Sinf_128fd0(f32);
f32 Cosf_128d30(f32);
void GsPktOpenPrim_13f730(s32, s32);
void GsPktSetTexture_13ec00(s32, s32);
void GsPktSetRGBAQ_13ee40(s32, s32, s32, s32, s32);
void GsPktSetUV_13ed60(s32, s32, s32);
void GsPktSetXYZf_13f060(s32, f32, f32, f32);
void GsPktSetXYZPixel_13f110(s32, s32, s32, s32);
void GsPktClose_13f5b0(s32);
s32 IsTgsDemoBuild_207f20(void);
void DrawListEndPrim_141a20(Game *);
s32 GetSysTextStyle_313570(void);
s32 DrawEnvGetWidth_1451e0(Game *);
s32 DrawEnvGetHeight_1451d0(Game *);
void TextStyleInit_26c610(s32);
void TextStyleSetFontType_26edf0(s32, s32);
void TextStyleAddSpacing_26f2b0(s32, s32, s32);
void TextStyleSetRgbaU32_26f210(s32, u32);
void TextStyleSetGradRgbaU32_26f170(s32, u32);
void TextStyleSetAlpha_26dd40(s32, s32);
void FontDrawText_26cdc0(s32, char *, s32, s32);

inline static void Rot(f32 *ox, f32 *oy, f32 y, f32 x)
{
    f32 s, c;
    s = Sinf_128fd0(D_0047F658);
    c = Cosf_128d30(D_0047F658);
    *ox = x * c - y * s;
    s = Sinf_128fd0(D_0047F658);
    c = Cosf_128d30(D_0047F658);
    *oy = y * c + x * s;
    *ox = *ox + 256.0f;
    *oy = *oy + 224.0f;
}

s32 LoadingScreenFrame_3435d0(void)
{
    Game *g;
    s32 mgr;
    s32 t1, t2, t3, t4;
    s32 d;
    s32 a;
    V9 base;
    V2 pt[9];
    s32 i;
    f32 y0, y1, x1, y2, x2, y4, x4, y3, x3, y5, x5, y6, x6, y7, x7, y8, x8;
    s32 y;
    s32 v;
    s32 m;
    s32 x;

    g = GetDrawCtx_15de80();
    if (GetLoadingResReady_1f69c0() != 0) {
        PadUpdateVibration_184250(D_004B2570, 0);
        PadUpdate_1843a0(D_004B2570);
        if (D_0047F65C != 0) {
            if (PadIsAnalogMode_184960(D_004B2570) == 0) D_0047F65C = 0;
        }
        if (D_0047F65C == 0) {
            if (PadIsAnalogMode_184960(D_004B2570) != 0 && PadIsTriggered_1839f0(D_004B2570, 0x40) != 0) D_0047F65C = 1;
        }
        if (D_0047F65C == 0) {
            PauseReasonDrawMaybe_2f5c40(4);
            return 0;
        }
    }
    if (D_00482D78 == 5) {
        if ((PadIsTriggered_1839f0(D_004B2570, 0x40) != 0 || PadIsTriggered_1839f0(D_004B2570, 0x800) != 0) && LoadingScreenTryFinish_3430c0() != 0) {
            SoundPlayScaledVolume_1b9520(SceneSoundGetSlot0HandleCur_207df0(), 5, 1.0f, 0);
        }
    }
    switch (D_00482D78) {
    case 0:
        D_004E8960.fade = 0.0f;
        D_00482D78 = 1;
        break;
    case 1:
        { f32 dd = D_0045B078[0]; D_004E8960.fade = D_004E8960.fade + 1.0f / dd; }
        if (!(D_004E8960.fade <= 1.0f)) {
            D_004E8960.fade = 1.0f;
            if (D_004E8960.x430 == 0) {
                D_00482D78 = 3;
            } else {
                D_00482D78 = 4;
            }
        }
        break;
    case 3:
    case 4:
        D_004E8960.x1C = D_004E8960.x1C + D_004E8960.x24;
        if (!(D_004E8960.x1C < D_004E8960.x20)) {
            D_004E8960.x1C = D_004E8960.x20;
        }
        if (D_00482D78 == 3) {
            if (PadIsTriggered_1839f0(D_004B2570, 0x840) != 0) {
                D_00482D88 = 0.0f;
                D_00482D78 = 4;
            }
        }
        if (D_00482D78 == 4) {
            { f32 dd = D_0045B078[0]; D_00482D88 = D_00482D88 + 1.0f / dd; }
            if (!(D_00482D88 <= 1.0f)) {
                D_00482D88 = 1.0f;
            }
        }
        break;
    case 5:
    case 6:
        if (!(D_00482D88 <= 0.0f)) {
            D_00482D88 = D_00482D88 - 1.0f / D_0045B078[0];
        } else {
            { f32 dd = D_0045B078[0]; D_004E8960.x434 = D_004E8960.x434 + 1.0f / dd; }
        }
        break;
    case 7:
        D_004E8960.fade = D_004E8960.fade - 3.0f * (1.0f / D_0045B078[0]);
        if (D_004E8960.fade < 0.0f) {
            D_004E8960.fade = 0.0f;
            D_00482D78 = 8;
        }
        for (i = 0; i < 14; i++) {
            D_004E8960.alpha[i] = D_004E8960.fade;
        }
        break;
    case 2:
    case 8:
        break;
    }
    D_0047F658 = D_0047F658 + D_0047DCD4;
    if (!(D_0047F658 <= D_0047DCD8)) {
        D_0047F658 = D_0047F658 - D_0047DCD8;
    }
    D_004E8960.x18 = D_004E8960.x18 + D_0047DCDC;
    if (DoubleGreaterEqual_100230(D_004E8960.x18, 0.5)) {
        D_004E8960.x18 = 0.5f;
    }
    if (D_00482D78 == 4) D_00482D84 = 1.0f;
    if (D_00482D78 == 6) D_00482D84 = 1.0f;
    if (D_00482D84 < 1.0f) {
        { f32 dd = D_0045B078[0]; D_00482D84 = D_00482D84 + 1.0f / dd; }
        if (!(D_00482D84 <= 1.0f)) {
            D_00482D84 = 1.0f;
        }
    }
    DrawListAddTexLoad_1418c0(g, D_004E8960.tex, 1.0f);
    mgr = g->mgr;
    t1 = NameTableFindByName_159fb0(mgr, D_004627F0, D_004E8960.tex);
    t2 = NameTableFindByName_159fb0(mgr, D_00462810, D_004E8960.tex);
    t3 = NameTableFindByName_159fb0(mgr, D_00462828, D_004E8960.tex);
    t4 = 0;
    if (D_00482D8C != 0) {
        t4 = NameTableFindByName_159fb0(mgr, D_00482D8C, D_004E8960.tex);
    }
    d = DrawListBeginPrim_141b00(g);
    a = 128.0f * D_004E8960.fade;
    GsPktSetOriginMode_13e2f0(d, 0);
    GsPktSetTextured_13e400(d, 1);
    GsPktSetAlphaBlend_13e500(d, 1);
    GsPktSetBlendMode_13e4f0(d, 1);
    GsPktEnableAlphaTest_13e4d0(d, 1);
    GsPktSetTexFilter_13e3d0(d, 1);
    GsPktSetZWriteMask_13e430(d, 0);
    GsPktEnableZTest_13e460(d, 0);
    if (D_0047F654 != 0) {
        base = *(V9 *)D_00453840;
        for (i = 0; i < 9; i++) {
            f32 y = base.v[i].y, x = base.v[i].x, s, c;
            V2 *p = &pt[i];
            f32 *q;
            s = Sinf_128fd0(D_0047F658);
            c = Cosf_128d30(D_0047F658);
            p->x = x * c - y * s;
            q = &p->y;
            s = Sinf_128fd0(D_0047F658);
            c = Cosf_128d30(D_0047F658);
            *q = x * s + y * c;
            p->x = p->x + 256.0f;
            *q = *q + 224.0f;
        }
        GsPktOpenPrim_13f730(d, 4);
        GsPktSetTexture_13ec00(d, t2);
        GsPktSetRGBAQ_13ee40(d, a, a, a, 0x80);
        GsPktSetUV_13ed60(d, 0, 0);
        y0 = pt[0].y;
        GsPktSetXYZf_13f060(d, pt[0].x, y0, 0.0f);
        GsPktSetUV_13ed60(d, 0xFF, 0);
        y2 = pt[2].y;
        x2 = pt[2].x;
        GsPktSetXYZf_13f060(d, x2, y2, 0.0f);
        GsPktSetUV_13ed60(d, 0, 0xFF);
        y6 = pt[6].y;
        x6 = pt[6].x;
        GsPktSetXYZf_13f060(d, x6, y6, 0.0f);
        GsPktSetUV_13ed60(d, 0xFF, 0xFF);
        y8 = pt[8].y;
        x8 = pt[8].x;
        GsPktSetXYZf_13f060(d, x8, y8, 0.0f);
        GsPktClose_13f5b0(d);
        GsPktOpenPrim_13f730(d, 4);
        GsPktSetTexture_13ec00(d, t1);
        GsPktSetRGBAQ_13ee40(d, a, a, a, 0x80);
        GsPktSetUV_13ed60(d, 0, 0);
        GsPktSetXYZf_13f060(d, pt[0].x, y0, 0.0f);
        GsPktSetUV_13ed60(d, 0x17F, 0);
        y1 = pt[1].y;
        x1 = pt[1].x;
        GsPktSetXYZf_13f060(d, x1, y1, 0.0f);
        GsPktSetUV_13ed60(d, 0, 0x17F);
        y3 = pt[3].y;
        x3 = pt[3].x;
        GsPktSetXYZf_13f060(d, x3, y3, 0.0f);
        GsPktSetUV_13ed60(d, 0x17F, 0x17F);
        y4 = pt[4].y;
        x4 = pt[4].x;
        GsPktSetXYZf_13f060(d, x4, y4, 0.0f);
        GsPktClose_13f5b0(d);
        GsPktOpenPrim_13f730(d, 4);
        GsPktSetUV_13ed60(d, 0, 0);
        GsPktSetXYZf_13f060(d, x1, y1, 0.0f);
        GsPktSetUV_13ed60(d, 0x17F, 0);
        GsPktSetXYZf_13f060(d, x2, y2, 0.0f);
        GsPktSetUV_13ed60(d, 0, 0x17F);
        GsPktSetXYZf_13f060(d, x4, y4, 0.0f);
        GsPktSetUV_13ed60(d, 0x17F, 0x17F);
        y5 = pt[5].y;
        x5 = pt[5].x;
        GsPktSetXYZf_13f060(d, x5, y5, 0.0f);
        GsPktClose_13f5b0(d);
        GsPktOpenPrim_13f730(d, 4);
        GsPktSetUV_13ed60(d, 0, 0);
        GsPktSetXYZf_13f060(d, x3, y3, 0.0f);
        GsPktSetUV_13ed60(d, 0x17F, 0);
        GsPktSetXYZf_13f060(d, x4, y4, 0.0f);
        GsPktSetUV_13ed60(d, 0, 0x17F);
        GsPktSetXYZf_13f060(d, x6, y6, 0.0f);
        GsPktSetUV_13ed60(d, 0x17F, 0x17F);
        y7 = pt[7].y;
        x7 = pt[7].x;
        GsPktSetXYZf_13f060(d, x7, y7, 0.0f);
        GsPktClose_13f5b0(d);
        GsPktOpenPrim_13f730(d, 4);
        GsPktSetUV_13ed60(d, 0, 0);
        GsPktSetXYZf_13f060(d, x4, y4, 0.0f);
        GsPktSetUV_13ed60(d, 0x17F, 0);
        GsPktSetXYZf_13f060(d, x5, y5, 0.0f);
        GsPktSetUV_13ed60(d, 0, 0x17F);
        GsPktSetXYZf_13f060(d, x7, y7, 0.0f);
        GsPktSetUV_13ed60(d, 0x17F, 0x17F);
        GsPktSetXYZf_13f060(d, x8, y8, 0.0f);
        GsPktClose_13f5b0(d);
    }
    if (t4 != 0) {
        GsPktOpenPrim_13f730(d, 6);
        GsPktSetTexture_13ec00(d, t4);
        GsPktSetRGBAQ_13ee40(d, 0x80, 0x80, 0x80, a);
        GsPktSetUV_13ed60(d, 0, 0);
        GsPktSetXYZPixel_13f110(d, 0, 0, 0);
        GsPktSetUV_13ed60(d, 0x1FF, 0x1BF);
        GsPktSetXYZPixel_13f110(d, 0x1FF, 0x1BF, 0);
        GsPktClose_13f5b0(d);
    }
    if (D_004E8960.x430 == 0 && !(D_00482D84 <= 0.0f)) {
        GsPktSetTexFilter_13e3d0(d, 1);
        GsPktOpenPrim_13f730(d, 6);
        GsPktSetTexture_13ec00(d, t3);
        GsPktSetRGBAQ_13ee40(d, a, a, a, 128.0f * D_00482D84);
        GsPktSetUV_13ed60(d, 0x18, 0);
        GsPktSetXYZPixel_13f110(d, 0xCC, 0x28, 0);
        GsPktSetUV_13ed60(d, 0x7F, 0x1B);
        GsPktSetXYZPixel_13f110(d, 0x133, 0x43, 0);
        GsPktClose_13f5b0(d);
    }
    if (!(D_00482D88 <= 0.0f)) {
        y = 0x188;
        if (IsTgsDemoBuild_207f20() != 0) y += 6;
        GsPktSetTexFilter_13e3d0(d, 1);
        GsPktOpenPrim_13f730(d, 6);
        GsPktSetTexture_13ec00(d, t3);
        GsPktSetRGBAQ_13ee40(d, a, a, a, 128.0f * D_00482D88);
        GsPktSetUV_13ed60(d, 0, 0);
        GsPktSetXYZPixel_13f110(d, 0x80, y, 0);
        GsPktSetUV_13ed60(d, 7, 0x11);
        GsPktSetXYZPixel_13f110(d, 0x88, y + 0x11, 0);
        GsPktSetUV_13ed60(d, 8, 0);
        GsPktSetXYZPixel_13f110(d, 0x88, y, 0);
        GsPktSetUV_13ed60(d, 0x10, 0x11);
        GsPktSetXYZPixel_13f110(d, 0x178, y + 0x11, 0);
        GsPktSetUV_13ed60(d, 0x10, 0);
        GsPktSetXYZPixel_13f110(d, 0x178, y, 0);
        GsPktSetUV_13ed60(d, 0x17, 0x11);
        GsPktSetXYZPixel_13f110(d, 0x180, y + 0x11, 0);
        GsPktSetUV_13ed60(d, 0, 0x22);
        GsPktSetXYZPixel_13f110(d, 0x86, y + 6, 0);
        GsPktSetUV_13ed60(d, 0x3F, 0x28);
        GsPktSetXYZPixel_13f110(d, (s32)(246.0f * D_004E8960.x1C) + 0x86, y + 0xC, 0);
        GsPktClose_13f5b0(d);
    }
    if ((u32)(D_00482D78 - 5) < 2) {
        if (D_004E8960.cur == D_004E8960.n) {
            D_00482D80 = D_00482D80 + D_0047D904;
            if (!(D_00482D80 <= 1.0f)) {
                D_00482D80 = 1.0f;
                D_00482D7C = D_00482D7C + D_0047DC98;
                if (!(D_00482D7C <= D_0047D1FC)) {
                    D_00482D7C = D_00482D7C - D_0047D1FC;
                }
            }
            { f32 w = (f32)(s32)(64.0f + 64.0f * Sinf_128fd0(D_00482D7C)); v = w * D_00482D80; }
            GsPktSetTexFilter_13e3d0(d, 1);
            GsPktOpenPrim_13f730(d, 6);
            GsPktSetTexture_13ec00(d, t3);
            GsPktSetRGBAQ_13ee40(d, v, v, v, v);
            GsPktSetUV_13ed60(d, 0, 0x28);
            GsPktSetXYZPixel_13f110(d, 0xC0, 0x188, 0);
            GsPktSetUV_13ed60(d, 0x7F, 0x3F);
            GsPktSetXYZPixel_13f110(d, 0x13F, 0x19F, 0);
            GsPktClose_13f5b0(d);
        }
    }
    DrawListEndPrim_141a20(g);
    if (D_004E8960.x430 == 0) {
        m = GetSysTextStyle_313570();
        if (m == 0) goto ret;
    } else {
        return 0;
    }
    if (D_004E8960.x2C != 0 && D_004E8960.n > 0 && !(D_00482D84 < 1.0f)) {
        { s32 t_bt = DrawEnvGetWidth_1451e0(g); x = t_bt; }
        DrawEnvGetHeight_1451d0(g);
        x = (x - D_004E8960.x428) / 2;
        TextStyleInit_26c610(m);
        TextStyleSetFontType_26edf0(m, 1);
        TextStyleAddSpacing_26f2b0(m, 3, 0);
        TextStyleSetRgbaU32_26f210(m, 0x80686A6B);
        TextStyleSetGradRgbaU32_26f170(m, 0x80686A6B);
        DrawListAddTexLoad_1418c0(g, 0x338, 1.0f);
        for (i = 0; i < D_004E8960.n; i++) {
            if (D_004E8960.alpha[i] <= 0.0f) continue;
            TextStyleSetAlpha_26dd40(m, 96.0f * D_004E8960.alpha[i]);
            FontDrawText_26cdc0(m, D_004E8960.names[i], x, D_004E8960.x3EC[i]);
        }
        if (D_004E8960.cur < D_004E8960.n) {
            D_004E8960.alpha[D_004E8960.cur] = D_004E8960.alpha[D_004E8960.cur] + D_0047DA38;
            if (!(D_004E8960.alpha[D_004E8960.cur] < 1.0f)) {
                D_004E8960.alpha[D_004E8960.cur] = 1.0f;
                D_004E8960.cur++;
            }
        }
    }
ret:
    return 0;
}
