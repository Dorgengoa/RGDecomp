/* rgp:protos */
#define RGP_SELF_DrawColorRect_1cc040 1
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

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void DrawColorRect_1cc040(s32 p0, s32 p1, s32 p2, s32 p3, s32 p4)
{
    s32 r0;
    s32 r1;

    r0 = GetDrawCtx_15de80();
    r1 = ((s32)DrawListBeginPrim_141b00(r0));
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
