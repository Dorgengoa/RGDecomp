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

extern void *GetDrawCtx_15de80(void);
extern void  DrawListAddTexLoad_1418c0(void *p, s32 id, f32 v);
extern void *DrawListBeginPrim_141b00(void *p);
extern void  GsPktSetAlphaBlend_13e500(void *h, s32 v);
extern void  GsPktSetBlendMode_13e4f0(void *h, s32 v);
extern void  GsPktEnableAlphaTest_13e4d0(void *h, s32 v);
extern void  GsPktSetAlphaTestFunc_13e4c0(void *h, s32 a, s32 b);
extern void  GsPktEnableZTest_13e460(void *h, s32 v);
extern void  GsPktSetZWriteMask_13e430(void *h, s32 v);
extern void  GsPktSetTexFilter_13e3d0(void *h, s32 v);
extern void  GsPktSetTextured_13e400(void *h, s32 v);
extern void  GsPktSetOriginMode_13e2f0(void *h, s32 v);
extern void  GsPktOpenPrim_13f730(void *h, s32 v);
extern s32   CameraProjectBillboardRect_15cde0(Quad *a, Quad *b, s32 c, s32 d, f32 x, f32 y);
extern void  GsPktSetTexture_13ec00(void *h, void *p);
extern void  GsPktSetRGBAQVec_13edd0(void *h, s32 v);
extern void  GsPktSetUV_13ed60(void *h, s32 a, s32 b);
extern void  GsPktSetXYZVecI_13eeb0(void *h, Quad *q);
extern void  GsPktClose_13f5b0(void *h);
extern void  DrawListEndPrim_141a20(void *p);

void DrawBillboard32_2783c0(s32 a0, s32 a1, s16 *a2, f32 x, f32 y, f32 z, f32 w)
{
    Quad v0;
    Quad v1;
    Quad v2;
    Quad v3;
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
    if (CameraProjectBillboardRect_15cde0(&v0, &v3, a0, 0, x, y) != 0) {
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
