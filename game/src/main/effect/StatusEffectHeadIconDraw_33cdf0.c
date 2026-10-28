/* rgp:protos */
#define RGP_SELF_StatusEffectHeadIconDraw_33cdf0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef rg_u128 u128;

typedef struct V33cdf0 {
    f32 x, y, z, w;
} __attribute__((aligned(16))) V33cdf0;

extern f64 D_0047D190;
extern u8 D_00462628[];

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
/*rgp*/

void StatusEffectHeadIconDraw_33cdf0(void *p)
{
    V33cdf0 c __attribute__((aligned(16)));
    V33cdf0 b __attribute__((aligned(16)));
    V33cdf0 a __attribute__((aligned(16)));
    u8 *q;
    u8 *r;
    void *ctx;
    void *dl;
    void *h;

    q = (u8 *)p;
    r = (u8 *)ObjRecGetLiveObject_1c4a90(GetStaticScene_1c6c70(), *(s16 *)(q + 0x14));
    if (r == 0) {
        return;
    }
    *(u128 *)&c = *(u128 *)(r + 0x180);
    c.y += (f32)(5.0 + dpmul(D_0047D190, *(f32 *)(r + 0x4CC)));
    ctx = GetDrawCtx_15de80();
    dl = DrawListBeginPrim_141b00(ctx);
    GsPktSetOriginMode_13e2f0(dl, 1);
    GsPktSetTextured_13e400(dl, 1);
    GsPktSetAlphaBlend_13e500(dl, 1);
    GsPktSetBlendMode_13e4f0(dl, 1);
    GsPktEnableAlphaTest_13e4d0(dl, 1);
    GsPktSetGouraud_13e3b0(dl, 0);
    GsPktSetTexFilter_13e3d0(dl, 1);
    GsPktSetZWriteMask_13e430(dl, 1);
    GsPktEnableZTest_13e460(dl, 1);
    if (CameraProjectBillboardRect_15cde0(&b, &a, 6.0f, 6.0f, &c) != 0) {
        h = NameTableFindByName_159fb0(GetDrawCtxNameTable_15de40(), D_00462628, 0x2A6);
        GsPktOpenPrim_13f730(dl, 6);
        GsPktSetTexture_13ec00(dl, h);
        GsPktSetUV_13ed60(dl, 0x20, 0x40);
        GsPktSetRGBAQ_13ee40(dl, 0x80, 0x80, 0x80, 0x80);
        GsPktSetXYZVecI_13eeb0(dl, &b);
        GsPktSetUV_13ed60(dl, 0x3F, 0x5F);
        GsPktSetRGBAQ_13ee40(dl, 0x80, 0x80, 0x80, 0x80);
        GsPktSetXYZVecI_13eeb0(dl, &a);
        GsPktClose_13f5b0(dl);
    }
    DrawListEndPrim_141a20(ctx);
}
