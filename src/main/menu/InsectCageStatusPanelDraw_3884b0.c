#include "types.h"

extern s32 BitArrayTest_384320(void *, s32);
extern s32 InsectCageMenuGetCursorObj_390f70(void);
extern s32 GetDrawCtxNameTable_15de40(void);
extern s16 *NameTableFindByName_159fb0(s32, void *, s32);
extern s32 GetDrawCtx_15de80(void);
extern void DrawListAddTexLoad_1418c0(s32, s32, f32);
extern s32 DrawListBeginPrim_141b00(s32);
extern void GsPktSetup2DState_3892a0(s32);
extern void GsPktSetOriginMode_13e2f0(s32, s32);
extern void GsPktSetTexFilter_13e3d0(s32, s32);
extern s32 MenuObjInsectIsAdult_386c90(s32);
extern s32 MenuObjInsectGetSex_386cf0(s32);
extern s32 MenuObjInsectGetSatiety_386c00(s32);
extern void GsPktOpenPrim_13f730(s32, s32);
extern void GsPktSetTexture_13ec00(s32, s16 *);
extern void GsPktSetRGBAQ_13ee40(s32, s32, s32, s32, s32);
extern void GsPktSetUV_13ed60(s32, s32, s32);
extern void GsPktSetXYZPixel_13f110(s32, s32, s32, s32);
extern f32 Sinf_128fd0(f32);
extern s32 MenuObjInsectSatietyUnderCap_386bd0(s32);
extern void GsPktClose_13f5b0(s32);
extern void GsPktSetXYZf_13f060(s32, f32, f32, f32);
extern void DrawListEndPrim_141a20(s32);
extern u8 D_0048335C;
extern u8 D_00463F40[];
extern s16 D_0047FCA0;
extern s16 D_0047FCA2;
extern s16 D_0047FCA8;
extern s16 D_0047FCAA;
extern f32 D_004832E0;

void InsectCageStatusPanelDraw_3884b0(void) {
    s32 obj;
    s16 *res;
    s32 ctx;
    s32 w;
    s16 *py;
    s16 *px;
    s32 a;
    s32 b;
    s32 c;
    s32 alpha;
    f32 r;

    if (BitArrayTest_384320(&D_0048335C, 2) == 0) return;
    obj = InsectCageMenuGetCursorObj_390f70();
    res = NameTableFindByName_159fb0(GetDrawCtxNameTable_15de40(), D_00463F40, -1);
    if (res == 0 || obj == 0) return;
    ctx = GetDrawCtx_15de80();
    DrawListAddTexLoad_1418c0(ctx, *res, 1.0f);
    w = DrawListBeginPrim_141b00(ctx);
    GsPktSetup2DState_3892a0(w);
    GsPktSetOriginMode_13e2f0(w, 0);
    GsPktSetTexFilter_13e3d0(w, 0);
    a = MenuObjInsectIsAdult_386c90(obj);
    b = MenuObjInsectGetSex_386cf0(obj);
    c = MenuObjInsectGetSatiety_386c00(obj);
    GsPktOpenPrim_13f730(w, 6);
    GsPktSetTexture_13ec00(w, res);
    GsPktSetRGBAQ_13ee40(w, 0x80, 0x80, 0x80, 0x80);
    py = &(&D_0047FCAA)[b * 2];
    px = &(&D_0047FCA8)[b * 2];
    GsPktSetUV_13ed60(w, *px, *py);
    GsPktSetXYZPixel_13f110(w, 0x26, 0x56, 0);
    GsPktSetUV_13ed60(w, *px + 0x2A, *py + 0x16);
    GsPktSetXYZPixel_13f110(w, 0x50, 0x6C, 0);
    py = &(&D_0047FCA2)[a * 2];
    px = &(&D_0047FCA0)[a * 2];
    GsPktSetUV_13ed60(w, *px, *py);
    GsPktSetXYZPixel_13f110(w, 0x26, 0x6C, 0);
    GsPktSetUV_13ed60(w, *px + 0x2A, *py + 0x16);
    GsPktSetXYZPixel_13f110(w, 0x50, 0x82, 0);
    alpha = (s32)(64.0f * Sinf_128fd0(D_004832E0)) + 0x80;
    if (MenuObjInsectSatietyUnderCap_386bd0(obj) != 0) {
        GsPktSetRGBAQ_13ee40(w, (s32)(100.0f * Sinf_128fd0(D_004832E0)) + 0x80, 0x80, 0x80, 0x80);
    } else {
        GsPktSetRGBAQ_13ee40(w, 0x80, 0x80, 0x80, 0x80);
    }
    GsPktSetUV_13ed60(w, 0x54, 0x22);
    GsPktSetXYZPixel_13f110(w, 0x22, 0x82, 0);
    GsPktSetUV_13ed60(w, 0x86, 0x34);
    GsPktSetXYZPixel_13f110(w, 0x54, 0x94, 0);
    GsPktSetUV_13ed60(w, 0xA8, 0xAE);
    GsPktSetXYZPixel_13f110(w, 0x22, 0x94, 0);
    GsPktSetUV_13ed60(w, 0xDA, 0xB8);
    GsPktSetXYZPixel_13f110(w, 0x54, 0x9E, 0);
    GsPktClose_13f5b0(w);
    GsPktSetTexFilter_13e3d0(w, 1);
    GsPktOpenPrim_13f730(w, 6);
    if ((void *)MenuObjInsectSatietyUnderCap_386bd0(obj) != 0) {
        GsPktSetRGBAQ_13ee40(w, 0x80, 0x80, 0x80, alpha);
    }
    r = (f32)c / 100.0f;
    if (1.0f <= r) r = 1.0f;
    GsPktSetUV_13ed60(w, 0xAA, 0xBC);
    GsPktSetXYZf_13f060(w, 37.0f, 151.0f, 0.0f);
    GsPktSetUV_13ed60(w, 0xD8, 0xC2);
    GsPktSetXYZf_13f060(w, 37.0f + 47.0f * r, 157.0f, 0.0f);
    GsPktClose_13f5b0(w);
    DrawListEndPrim_141a20(ctx);

}
