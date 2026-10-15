#include "types.h"

extern s32 D_00481C58;
extern s32 D_00481C54;
extern struct { void *v; s32 pad[3]; } D_0044B774;
extern s16 D_0044B778[];
extern s16 D_0044B77A[];

extern void *GetDrawCtxNameTable_15de40(void);
extern void *GetDrawCtx_15de80(void);
extern void *DrawListBeginPrim_141b00(void *ctx);
extern s16 *NameTableFindByName_159fb0(void *s, void *name, s32 id);
extern void DrawListAddTexLoad_1418c0(void *ctx, s32 id, f32 t);
extern void GsPktSetBlendMode_13e4f0(void *dl, s32 v);
extern void GsPktSetAlphaBlend_13e500(void *dl, s32 v);
extern void GsPktSetAntialias_13e390(void *dl, s32 v);
extern void GsPktEnableAlphaTest_13e4d0(void *dl, s32 v);
extern void GsPktEnableZTest_13e460(void *dl, s32 v);
extern void GsPktSetTextured_13e400(void *dl, s32 v);
extern void GsPktSetUseUV_13e3e0(void *dl, s32 v);
extern void GsPktSetOriginMode_13e2f0(void *dl, s32 v);
extern void GsPktSetTexFilter_13e3d0(void *dl, s32 v);
extern void GsPktSetZWriteMask_13e430(void *dl, s32 v);
extern void GsPktSetGouraud_13e3b0(void *dl, s32 v);
extern void GsPktOpenPrim_13f730(void *dl, s32 v);
extern void GsPktSetTexture_13ec00(void *dl, void *h);
extern void GsPktSetRGBAQ_13ee40(void *dl, s32 r, s32 g, s32 b, s32 a);
extern void GsPktSetUV_13ed60(void *dl, s32 u, s32 v);
extern void GsPktSetXYZPixel_13f110(void *dl, s32 a, s32 b, s32 c);
extern void GsPktClose_13f5b0(void *dl);
extern void DrawListEndPrim_141a20(void *ctx);

void MenuTestDraw_2038f0(void)
{
    void *s;
    void *ctx;
    void *dl;
    s16 *h;
    s32 i;

    if (D_00481C58 == 0) {
        return;
    }
    s = GetDrawCtxNameTable_15de40();
    ctx = GetDrawCtx_15de80();
    dl = DrawListBeginPrim_141b00(ctx);
    D_00481C54 = 0;
    h = NameTableFindByName_159fb0(s, D_0044B774.v, -1);
    if (h != 0) {
        DrawListAddTexLoad_1418c0(ctx, h[0], 1.0f);
    }
    GsPktSetBlendMode_13e4f0(dl, 1);
    GsPktSetAlphaBlend_13e500(dl, 1);
    GsPktSetAntialias_13e390(dl, 0);
    GsPktEnableAlphaTest_13e4d0(dl, 1);
    GsPktEnableZTest_13e460(dl, 0);
    GsPktSetTextured_13e400(dl, 1);
    GsPktSetUseUV_13e3e0(dl, 1);
    GsPktSetOriginMode_13e2f0(dl, 0);
    GsPktSetTexFilter_13e3d0(dl, 0);
    GsPktSetZWriteMask_13e430(dl, 0);
    GsPktSetGouraud_13e3b0(dl, 0);
    GsPktOpenPrim_13f730(dl, 6);
    GsPktSetTexture_13ec00(dl, h);
    GsPktSetRGBAQ_13ee40(dl, 0x80, 0x80, 0x80, 0x80);
    GsPktSetUV_13ed60(dl, 0, 0);
    GsPktSetXYZPixel_13f110(dl, 0, 0, 0);
    i = D_00481C54;
    GsPktSetUV_13ed60(dl, D_0044B778[i * 6], D_0044B77A[i * 6]);
    GsPktSetXYZPixel_13f110(dl, 0x200, 0x1C0, 0);
    GsPktClose_13f5b0(dl);
    DrawListEndPrim_141a20(ctx);
}
