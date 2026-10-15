#pragma divbyzerocheck on
#include "types.h"

typedef __int128 s128;

typedef struct {
    s16 unk0;
    s16 w;
    s16 h;
} Img;

typedef struct {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    u8 pad6[0x70 - 0x6];
} Info;

typedef struct {
    s32 x;
    s32 y;
    s32 w;
    s32 h;
} Rect;

typedef struct {
    s32 unk0;
    u8 pad4[4];
    u8 name0[0x20];
    u8 name1[0x20];
    u8 name2[0x20];
    s32 unk68;
} Obj;

typedef struct {
    u8 pad0[0x3BA0];
    s32 unk3BA0;
} Ctx;

typedef struct {
    f32 r;
    f32 g;
    f32 b;
    f32 a;
} Col;

extern void GsPktSetTextured_13e400(s32, s32);
extern void GsPktSetFrameMask_13e420(s32, s32);
extern void GsPktSetZWriteMask_13e430(s32, s32);
extern void GsPktSetZTest_13e450(s32, s32);
extern void GsPktEnableZTest_13e460(s32, s32);
extern void GsPktEnableAlphaTest_13e4d0(s32, s32);
extern void GsPktSetBlendMode_13e4f0(s32, s32);
extern void GsPktSetAlphaBlend_13e500(s32, s32);
extern void GsPktSetTexture_13ec00(s32, Img *);
extern void GsPktSetUV_13ed60(s32, s32, s32);
extern void GsPktSetRGBAQ_13ee40(s32, s32, s32, s32, s32);
extern void GsPktSetXYZ_13ef10(s32, s32, s32, s32);
extern void GsPktSetXYZPixel_13f110(s32, s32, s32, s32);
extern void GsPktClose_13f5b0(s32);
extern void GsPktOpenPrim_13f730(s32, s32);
extern void GsPktDisableTests_13f9e0(s32);
extern void GfxBlitTexRectPixels_141710(Ctx *, Info *, Rect *, Img *, Rect *);
extern void DrawListAddTexLoad_1418c0(Ctx *, s32, f32);
extern void DrawListEndPrim_141a20(Ctx *);
extern s32 DrawListBeginPrim_141b00(Ctx *);
extern void DrawListAddEnv_1421d0(Ctx *);
extern void DrawEnvPop_144800(Ctx *);
extern void DrawEnvPush_144830(Ctx *);
extern void DrawEnvGetDispFbTexDesc_144a00(Ctx *, Info *);
extern void DrawEnvSetFrameFromDesc_144fe0(Ctx *, Img *, s32);
extern s32 DrawEnvGetHeight_1451d0(Ctx *);
extern s32 DrawEnvGetWidth_1451e0(Ctx *);
extern Img *NameTableFindByName_159fb0(s32, u8 *, s32);
extern void NameTableNodeCtor_15ae50(Info *);
extern Ctx *GetDrawCtx_15de80(void);

void CBlurDrawMaybe_1784e0(Obj *arg0, Col *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5)
{
    Info info;
    Col *col;
    Ctx *ctx;
    s32 d;
    Img *img;
    Img *spr;
    s32 iw;
    s32 ih;
    s32 cr;
    s32 cg;
    s32 H;
    s32 w;
    s32 h;
    s32 tbl;
    s32 cb;
    Rect r2;
    Rect r1;
    s32 W;
    s32 ca;

    if (arg0->unk0 == 0) {
        return;
    }
    if (arg0->unk68 != 0) {
        return;
    }
    col = arg1;
    ctx = GetDrawCtx_15de80();
    tbl = ctx->unk3BA0;
    img = NameTableFindByName_159fb0(tbl, arg0->name0, -1);
    if (img == NULL) {
        return;
    }
    iw = img->w;
    ih = img->h;
    NameTableNodeCtor_15ae50(&info);
    if (arg3 != 0) {
        spr = NameTableFindByName_159fb0(tbl, arg0->name1, -1);
    } else {
        spr = NameTableFindByName_159fb0(tbl, arg0->name2, -1);
    }
    if (spr == NULL) {
        return;
    }
    W = DrawEnvGetWidth_1451e0(ctx);
    H = DrawEnvGetHeight_1451d0(ctx);
    w = spr->w;
    h = spr->h;
    if (arg3 != 0) {
        arg4 = arg4 * w / W;
        arg5 = arg5 * h / H;
        col = arg1;
    }
    DrawListAddTexLoad_1418c0(ctx, spr->unk0, 1.0f);
    DrawEnvGetDispFbTexDesc_144a00(ctx, &info);
    r2.x = 0;
    r2.w = H;
    r2.y = 0;
    r1.x = 0;
    r2.h = W;
    r1.y = 0;
    r1.w = info.unk4;
    r1.h = info.unk2;
    if (arg3 == 0) {
        GfxBlitTexRectPixels_141710(ctx, &info, &r1, spr, &r2);
    }
    DrawEnvPush_144830(ctx);
    DrawEnvSetFrameFromDesc_144fe0(ctx, spr, 0);
    DrawListAddEnv_1421d0(ctx);
    d = DrawListBeginPrim_141b00(ctx);
    GsPktDisableTests_13f9e0(d);
    if (arg3 != 0) {
        GsPktOpenPrim_13f730(d, 6);
        GsPktSetRGBAQ_13ee40(d, 0x80, 0x80, 0x80, 0x80);
        GsPktSetXYZPixel_13f110(d, 0, 0, 0);
        GsPktSetXYZPixel_13f110(d, w, h, 0);
        GsPktClose_13f5b0(d);
    }
    GsPktSetFrameMask_13e420(d, 2);
    if (arg4 != 0 || arg5 != 0) {
        GsPktSetTextured_13e400(d, 0);
        GsPktOpenPrim_13f730(d, 6);
        GsPktSetRGBAQ_13ee40(d, 0x80, 0x80, 0x80, 0);
        GsPktSetXYZPixel_13f110(d, 0, 0, 0);
        GsPktSetXYZPixel_13f110(d, w, h, 0);
        GsPktClose_13f5b0(d);
    }
    GsPktSetTextured_13e400(d, 1);
    GsPktSetFrameMask_13e420(d, 2);
    GsPktOpenPrim_13f730(d, 6);
    GsPktSetTexture_13ec00(d, img);
    GsPktSetRGBAQ_13ee40(d, 0x80, 0x80, 0x80, 0x80);
    GsPktSetUV_13ed60(d, 0, 0);
    GsPktSetXYZPixel_13f110(d, arg4, arg5, 0);
    GsPktSetUV_13ed60(d, iw, ih);
    GsPktSetXYZPixel_13f110(d, w + arg4, h + arg5, 0);
    GsPktClose_13f5b0(d);
    DrawListEndPrim_141a20(ctx);
    DrawEnvPop_144800(ctx);
    DrawListAddEnv_1421d0(ctx);
    d = DrawListBeginPrim_141b00(ctx);
    GsPktEnableZTest_13e460(d, 0);
    GsPktSetZWriteMask_13e430(d, 1);
    GsPktSetZTest_13e450(d, 0);
    GsPktSetTextured_13e400(d, 1);
    GsPktSetAlphaBlend_13e500(d, 1);
    GsPktEnableAlphaTest_13e4d0(d, 0);
    GsPktSetBlendMode_13e4f0(d, arg2);
    GsPktSetFrameMask_13e420(d, 1);
    cr = 128.0f * col->r;
    cg = 128.0f * col->g;
    cb = 128.0f * col->b;
    ca = 64.0f * col->a;
    GsPktOpenPrim_13f730(d, 6);
    GsPktSetTexture_13ec00(d, spr);
    GsPktSetRGBAQ_13ee40(d, cr, cg, cb, ca);
    GsPktSetUV_13ed60(d, 0, 0);
    GsPktSetXYZ_13ef10(d, -0x10 - arg4 * 0x10, -0x20 - arg5 * 0x10, 0);
    GsPktSetUV_13ed60(d, w, h);
    GsPktSetXYZ_13ef10(d, (W - arg4) * 0x10 - 0x10, (H - arg5) * 0x10 - 0x20, 0);
    GsPktClose_13f5b0(d);
    DrawListEndPrim_141a20(ctx);
}
