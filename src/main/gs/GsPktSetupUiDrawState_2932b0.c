#include "types.h"

extern void GsPktSetBlendMode_13e4f0(s32, s32);
extern void GsPktSetAlphaBlend_13e500(s32, s32);
extern void GsPktSetAntialias_13e390(s32, s32);
extern void GsPktEnableAlphaTest_13e4d0(s32, s32);
extern void GsPktEnableZTest_13e460(s32, s32);
extern void GsPktSetTextured_13e400(s32, s32);
extern void GsPktSetUseUV_13e3e0(s32, s32);
extern void GsPktSetOriginMode_13e2f0(s32, s32);
extern void GsPktSetZWriteMask_13e430(s32, s32);
extern void GsPktSetGouraud_13e3b0(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void GsPktSetupUiDrawState_2932b0(s32 p0)
{
    GsPktSetBlendMode_13e4f0(p0, 1);
    GsPktSetAlphaBlend_13e500(p0, 1);
    GsPktSetAntialias_13e390(p0, 0);
    GsPktEnableAlphaTest_13e4d0(p0, 1);
    GsPktEnableZTest_13e460(p0, 0);
    GsPktSetTextured_13e400(p0, 1);
    GsPktSetUseUV_13e3e0(p0, 1);
    GsPktSetOriginMode_13e2f0(p0, 0);
    GsPktSetZWriteMask_13e430(p0, 1);
    GsPktSetGouraud_13e3b0(p0, 0);
}
