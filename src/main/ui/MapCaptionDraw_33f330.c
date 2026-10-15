#include "types.h"

typedef struct {
    u8 pad0[0x18];
    s32 unk18;
    u8 pad1C[0x20 - 0x1C];
    f32 unk20;
} Obj;

extern s32 GsPktSetOriginMode_13e2f0(s32, s32);
extern s32 GsPktSetUseUV_13e3e0(s32, s32);
extern s32 GsPktSetTextured_13e400(s32, s32);
extern s32 GsPktSetZWriteMask_13e430(s32, s32);
extern s32 GsPktEnableZTest_13e460(s32, s32);
extern s32 GsPktEnableAlphaTest_13e4d0(s32, s32);
extern s32 GsPktSetBlendMode_13e4f0(s32, s32);
extern s32 GsPktSetAlphaBlend_13e500(s32, s32);
extern s32 GsPktSetTexture_13ec00(s32, s32);
extern s32 GsPktSetUV_13ed60(s32, s32, s32);
extern s32 GsPktSetRGBAQ_13ee40(s32, s32, s32, s32, s32);
extern s32 GsPktSetXYZPixel_13f110(s32, s32, s32, s32);
extern s32 GsPktClose_13f5b0(s32);
extern s32 GsPktOpenPrim_13f730(s32, s32);
extern s32 DrawListAddTexLoad_1418c0(s32, s32, f32);
extern s32 DrawListEndPrim_141a20(s32);
extern s32 DrawListBeginPrim_141b00(s32);
extern s32 NameTableFindByName_159fb0(s32, s32, s32);
extern s32 GetDrawCtxNameTable_15de40(void);
extern s32 GetDrawCtx_15de80(void);
extern s32 UiPanelDraw_33ddc0(s32);
extern s16 MapCaptionGetImageMode_33f1a0(Obj *);
extern s32 MapCaptionGetOffsetX_33f1c0(Obj *);
extern s32 MapCaptionGetOffsetY_33f1e0(Obj *);
extern s32 MapCaptionGetImageSize_33f200(Obj *, s32 *, s32 *);
extern s32 CaptionCalcBottomY_33f250(Obj *, s32);
extern s32 CaptionCalcCenterX_33f2c0(Obj *);
extern s32 CaptionCfgGetTexName_340220(s32);
extern s32 GetCaptionPanel_340420(void);
extern s32 GetCaptionCfg_340430(s32);

void MapCaptionDraw_33f330(Obj *arg0) {
    s32 sp7C;
    s32 sp78;
    s32 a;
    s32 b;
    s32 c;
    s32 d;
    s32 e;
    s32 x;
    s32 y;
    s32 t;

    t = arg0->unk18;
    if (t != 4) {
        return;
    }
    a = GetCaptionCfg_340430(t);
    b = GetDrawCtx_15de80();
    c = GetDrawCtxNameTable_15de40();
    DrawListAddTexLoad_1418c0(b, 0x1C8, 1.0f);
    d = NameTableFindByName_159fb0(c, CaptionCfgGetTexName_340220(a), 0x1C8);
    if (d == 0) {
        return;
    }
    e = DrawListBeginPrim_141b00(b);
    GsPktSetTextured_13e400(e, 1);
    GsPktSetUseUV_13e3e0(e, 1);
    GsPktSetOriginMode_13e2f0(e, 0);
    GsPktSetAlphaBlend_13e500(e, 1);
    GsPktSetBlendMode_13e4f0(e, 1);
    GsPktEnableAlphaTest_13e4d0(e, 1);
    GsPktSetZWriteMask_13e430(e, 0);
    GsPktEnableZTest_13e460(e, 0);
    x = CaptionCalcBottomY_33f250(arg0, 0x50);
    x += MapCaptionGetOffsetY_33f1e0(arg0);
    CaptionCalcCenterX_33f2c0(arg0);
    y = 0x10;
    y += MapCaptionGetOffsetX_33f1c0(arg0);
    MapCaptionGetImageSize_33f200(arg0, &sp7C, &sp78);
    if (MapCaptionGetImageMode_33f1a0(arg0) == 1) {
        GsPktOpenPrim_13f730(e, 6);
        GsPktSetTexture_13ec00(e, d);
        GsPktSetRGBAQ_13ee40(e, 0x80, 0x80, 0x80, (s32)(128.0f * arg0->unk20));
        GsPktSetUV_13ed60(e, 0, 0);
        GsPktSetXYZPixel_13f110(e, y, x, 0);
        GsPktSetUV_13ed60(e, sp7C - 1, sp78 - 1);
        GsPktSetXYZPixel_13f110(e, y + sp7C, x + sp78, 0);
        GsPktClose_13f5b0(e);
    } else {
        t = GetCaptionPanel_340420();
        if (t != 0) {
            UiPanelDraw_33ddc0(t);
        }
    }
    DrawListEndPrim_141a20(b);
}
