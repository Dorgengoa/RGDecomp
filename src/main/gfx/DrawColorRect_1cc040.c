#include "types.h"

extern s32 GetDrawCtx_15de80(void);
extern s32 DrawListBeginPrim_141b00(s32);
extern void GsPktSetOriginMode_13e2f0(s32, s32);
extern void GsPktSetZWriteMask_13e430(s32, s32);
extern void GsPktSetTextured_13e400(s32, s32);
extern void GsPktSetAlphaBlend_13e500(s32, s32);
extern void GsPktSetBlendMode_13e4f0(s32, s32);
extern void GsPktEnableAlphaTest_13e4d0(s32, s32);
extern void GsPktEnableZTest_13e460(s32, s32);
extern void GsPktOpenPrim_13f730(s32, s32);
extern void GsPktSetRGBAQVec_13edd0(s32, s32);
extern void GsPktSetXYZPixel_13f110(s32, s32, s32, s32);
extern void GsPktClose_13f5b0(s32);
extern void DrawListEndPrim_141a20(s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void DrawColorRect_1cc040(s32 p0, s32 p1, s32 p2, s32 p3, s32 p4)
{
    s32 r0;
    s32 r1;

    r0 = GetDrawCtx_15de80();
    r1 = DrawListBeginPrim_141b00(r0);
    GsPktSetOriginMode_13e2f0(r1, 0);
    GsPktSetZWriteMask_13e430(r1, 1);
    GsPktSetTextured_13e400(r1, 0);
    GsPktSetAlphaBlend_13e500(r1, 1);
    GsPktSetBlendMode_13e4f0(r1, 1);
    GsPktEnableAlphaTest_13e4d0(r1, 1);
    GsPktEnableZTest_13e460(r1, 0);
    GsPktOpenPrim_13f730(r1, 6);
    GsPktSetRGBAQVec_13edd0(r1, p4);
    GsPktSetXYZPixel_13f110(r1, p0, p1, 0);
    GsPktSetXYZPixel_13f110(r1, (p0 + p2), (p1 + p3), 0);
    GsPktClose_13f5b0(r1);
    DrawListEndPrim_141a20(r0);
}
