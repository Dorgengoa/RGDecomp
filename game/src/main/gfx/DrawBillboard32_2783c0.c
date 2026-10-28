/* rgp:protos */
#define RGP_SELF_DrawBillboard32_2783c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Four stack quads: the LAST-declared local takes the LOWEST address, so
   v0=0xA0, v1=0x90, v2=0x80, v3=0x70.  The two "= 1" stores are hoisted
   constants; source order is v2 then v1. */

typedef struct Quad {
    s32 x;
    s32 y;
    s32 z;
    s32 w;
} Quad;

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

void DrawBillboard32_2783c0(s32 a0, s32 a1, s16 *a2, f32 x, f32 y, f32 z, f32 w)
{
    Quad v0 __attribute__((aligned(16)));
    Quad v1 __attribute__((aligned(16)));
    Quad v2 __attribute__((aligned(16)));
    Quad v3 __attribute__((aligned(16)));
    void *p;
    void *h;

    p = GetDrawCtx_15de80();
    if (a2 != 0) {
        DrawListAddTexLoad_1418c0(p, *a2, 1.0f);
    }
    h = DrawListBeginPrim_141b00(p);
    GsPktSetAlphaBlend_13e500(h, 1);
    GsPktSetBlendMode_13e4f0(h, 1);
    GsPktEnableAlphaTest_13e4d0(h, 1);
    GsPktSetAlphaTestFunc_13e4c0(h, 6, 0x10);
    GsPktEnableZTest_13e460(h, 1);
    GsPktSetZWriteMask_13e430(h, 0);
    GsPktSetTexFilter_13e3d0(h, 1);
    if (a2 != 0) {
        GsPktSetTextured_13e400(h, 1);
    } else {
        GsPktSetTextured_13e400(h, 0);
    }
    GsPktSetOriginMode_13e2f0(h, 1);
    GsPktOpenPrim_13f730(h, 4);
    if (CameraProjectBillboardRect_15cde0(&v0, &v3, x, y, a0) != 0) {
        if (a2 != 0) {
            GsPktSetTexture_13ec00(h, a2);
        }
        GsPktSetRGBAQVec_13edd0(h, a1);
        v2.x = v0.x;
        v2.y = v3.y;
        v2.z = v0.z;
        v2.w = 1;
        v1.x = v3.x;
        v1.y = v0.y;
        v1.z = v3.z;
        v1.w = 1;
        GsPktSetUV_13ed60(h, (s32)z, (s32)w);
        GsPktSetXYZVecI_13eeb0(h, &v0);
        GsPktSetUV_13ed60(h, (s32)z, (s32)(31.0f + w));
        GsPktSetXYZVecI_13eeb0(h, &v2);
        GsPktSetUV_13ed60(h, (s32)(32.0f + z), (s32)w);
        GsPktSetXYZVecI_13eeb0(h, &v1);
        GsPktSetUV_13ed60(h, (s32)(32.0f + z), (s32)(31.0f + w));
        GsPktSetXYZVecI_13eeb0(h, &v3);
    }
    GsPktClose_13f5b0(h);
    DrawListEndPrim_141a20(p);
}
