/* rgp:protos */
#define RGP_SELF_GsPktSetup2DState_3892a0 1
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

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void GsPktSetup2DState_3892a0(s32 p0)
{
    GsPktSetAlphaBlend_13e500(p0, 1);
    GsPktSetAntialias_13e390(p0, 0);
    GsPktEnableAlphaTest_13e4d0(p0, 1);
    GsPktEnableZTest_13e460(p0, 0);
    GsPktSetTextured_13e400(p0, 1);
    GsPktSetUseUV_13e3e0(p0, 1);
    GsPktSetOriginMode_13e2f0(p0, 1);
    GsPktSetTexFilter_13e3d0(p0, 1);
    GsPktSetZWriteMask_13e430(p0, 1);
    GsPktSetGouraud_13e3b0(p0, 0);
}
