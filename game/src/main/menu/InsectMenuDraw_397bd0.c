/* rgp:protos */
#define RGP_SELF_InsectMenuDraw_397bd0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern s16 D_00483504;
extern u8 D_0048352C;
extern u8 D_0048350C;
extern u8 D_004E95C0[];
extern void *D_00483518;
extern f32 D_00483520;
extern f32 D_00483524;
extern f32 D_0047FF44;

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

void InsectMenuDraw_397bd0(void)
{
    void *ctx;
    void *a;
    void *b;
    void *dl;

    if (D_00483504 == 0) {
        return;
    }
    UiDrawWidgets_291910(D_004E95C0);
    if (D_0048352C == 0) {
        return;
    }
    if (D_0048350C == 0) {
        return;
    }
    ctx = GetDrawCtx_15de80();
    a = DrawEnvGetWidth_1451e0(ctx);
    b = DrawEnvGetHeight_1451d0(ctx);
    dl = DrawListBeginPrim_141b00(ctx);
    GsPktSetDefaultState_13fa80(dl);
    GsPktEnableZTest_13e460(dl, 0);
    GsPktSetZTest_13e450(dl, 0);
    GsPktSetZWriteMask_13e430(dl, 0);
    GsPktSetTextured_13e400(dl, 0);
    GsPktSetAlphaBlend_13e500(dl, 0);
    GsPktSetFrameMask_13e420(dl, 2);
    GsPktOpenPrim_13f730(dl, 6);
    GsPktSetRGBAQ_13ee40(dl, 0, 0, 0, 0);
    GsPktSetXYZPixel_13f110(dl, 0, 0, 0);
    GsPktSetXYZPixel_13f110(dl, (s32)a, (s32)b, 0);
    GsPktClose_13f5b0(dl);
    DrawListEndPrim_141a20(ctx);
    *(f32 *)((u8 *)D_00483518 + 0x448) = D_0047FF44;
    DrawModelPreview_28be80(D_00483518, D_00483520, D_00483524);
}
