/* rgp:protos */
#define RGP_SELF_MenuTestDraw_2038f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern s32 D_00481C58;
extern s32 D_00481C54;
extern struct { void *v; s32 pad[3]; } D_0044B774;
extern s16 D_0044B778[];
extern s16 D_0044B77A[];

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
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

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
    h = ((s16 *)NameTableFindByName_159fb0(s, D_0044B774.v, -1));
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
