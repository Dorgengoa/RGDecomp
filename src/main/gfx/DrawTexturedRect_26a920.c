#include "types.h"

extern void *GetDrawCtx_15de80(void);
extern void DrawListAddTexLoad_1418c0(void *ctx, s32 id, f32 t);
extern void *DrawListBeginPrim_141b00(void *ctx);
extern void GsPktSetAlphaBlend_13e500(void *dl, s32 v);
extern void GsPktSetBlendMode_13e4f0(void *dl, s32 v);
extern void GsPktEnableAlphaTest_13e4d0(void *dl, s32 v);
extern void GsPktSetAlphaTestFunc_13e4c0(void *dl, s32 v, s32 w);
extern void GsPktEnableZTest_13e460(void *dl, s32 v);
extern void GsPktSetZWriteMask_13e430(void *dl, s32 v);
extern void GsPktSetTextured_13e400(void *dl, s32 v);
extern void GsPktSetTexFilter_13e3d0(void *dl, s32 v);
extern void GsPktOpenPrim_13f730(void *dl, s32 v);
extern void GsPktSetTexture_13ec00(void *dl, void *h);
extern void GsPktSetRGBAQ_13ee40(void *dl, s32 r, s32 g, s32 b, s32 a);
extern void GsPktSetUVFixed_13ed90(void *dl, s32 u, s32 v);
extern void GsPktSetXYZPixel_13f110(void *dl, s32 a, s32 b, s32 c);
extern void GsPktClose_13f5b0(void *dl);
extern void DrawListEndPrim_141a20(void *ctx);

void DrawTexturedRect_26a920(s32 x, s32 y, s32 w, s32 h, s32 cr, s32 cg, s32 cb, s32 ca,
                  s16 *tex)
{
    void *ctx;
    void *dl;

    ctx = GetDrawCtx_15de80();
    if (tex != 0) {
        DrawListAddTexLoad_1418c0(ctx, tex[0], 1.0f);
        dl = DrawListBeginPrim_141b00(ctx);
        GsPktSetAlphaBlend_13e500(dl, 1);
        GsPktSetBlendMode_13e4f0(dl, 1);
        GsPktEnableAlphaTest_13e4d0(dl, 1);
        GsPktSetAlphaTestFunc_13e4c0(dl, 1, 0);
        GsPktEnableZTest_13e460(dl, 0);
        GsPktSetZWriteMask_13e430(dl, 1);
        GsPktSetTextured_13e400(dl, 1);
        GsPktSetTexFilter_13e3d0(dl, 0);
        GsPktOpenPrim_13f730(dl, 6);
        GsPktSetTexture_13ec00(dl, tex);
        GsPktSetRGBAQ_13ee40(dl, cr, cg, cb, ca);
        GsPktSetUVFixed_13ed90(dl, 0, 0);
        GsPktSetXYZPixel_13f110(dl, x, y, 0);
        GsPktSetUVFixed_13ed90(dl, ((tex[1] - 1) << 4) + 8, ((tex[2] - 1) << 4) + 8);
        GsPktSetXYZPixel_13f110(dl, x + w - 1, y + h - 1, 0);
        GsPktClose_13f5b0(dl);
        DrawListEndPrim_141a20(ctx);
    } else {
        dl = DrawListBeginPrim_141b00(ctx);
        GsPktSetAlphaBlend_13e500(dl, 1);
        GsPktSetBlendMode_13e4f0(dl, 1);
        GsPktEnableAlphaTest_13e4d0(dl, 1);
        GsPktSetAlphaTestFunc_13e4c0(dl, 1, 0);
        GsPktEnableZTest_13e460(dl, 0);
        GsPktSetZWriteMask_13e430(dl, 1);
        GsPktSetTextured_13e400(dl, 0);
        GsPktOpenPrim_13f730(dl, 6);
        GsPktSetTexture_13ec00(dl, 0);
        GsPktSetRGBAQ_13ee40(dl, cr, cg, cb, ca);
        GsPktSetXYZPixel_13f110(dl, x, y, 0);
        GsPktSetXYZPixel_13f110(dl, x + w, y + h, 0);
        GsPktClose_13f5b0(dl);
        DrawListEndPrim_141a20(ctx);
    }
}
