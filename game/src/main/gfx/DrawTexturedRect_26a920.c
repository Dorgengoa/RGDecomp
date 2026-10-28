/* rgp:protos */
#define RGP_SELF_DrawTexturedRect_26a920 1
#include "port/game_protos.h"
#line 1
#include "types.h"

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
