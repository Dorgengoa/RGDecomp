/* rgp:protos */
#define RGP_SELF_TaskDrawPauseFilter_2f5ae0 1
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

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void TaskDrawPauseFilter_2f5ae0(void)
{
    s32 r0;
    s32 r1;

    r0 = GetDrawCtx_15de80();
    r1 = ((s32)DrawListBeginPrim_141b00(r0));
    GsPktSetTextured_13e400(r1, 0);
    GsPktSetOriginMode_13e2f0(r1, 0);
    GsPktSetAlphaBlend_13e500(r1, 1);
    GsPktSetBlendMode_13e4f0(r1, 1);
    GsPktEnableAlphaTest_13e4d0(r1, 1);
    GsPktSetZWriteMask_13e430(r1, 0);
    GsPktEnableZTest_13e460(r1, 0);
    GsPktSetTexFilter_13e3d0(r1, 0);
    GsPktOpenPrim_13f730(r1, 6);
    GsPktSetRGBAQ_13ee40(r1, 0, 0, 0, 0x40);
    GsPktSetXYZPixel_13f110(r1, 0, 0, 0);
    GsPktSetXYZPixel_13f110(r1, 0x1FF, 0x1BF, 0);
    GsPktClose_13f5b0(r1);
    DrawListEndPrim_141a20(r0);
}
