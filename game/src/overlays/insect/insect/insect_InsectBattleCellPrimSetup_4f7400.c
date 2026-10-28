/* rgp:protos */
#define RGP_SELF_insect_InsectBattleCellPrimSetup_4f7400 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x004F7400 -- 292 bytes, 73 instructions.
 * Resets a widget then re-applies the bits of the mask; -1 means "leave
 * everything reset".  The first parameter is unused. */

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

void insect_InsectBattleCellPrimSetup_4f7400(void *a, void *p, s32 mask)
{
    if (p != 0) {
        GsPktSetAlphaBlend_13e500(p, 1);
        GsPktSetBlendMode_13e4f0(p, 1);
        GsPktEnableAlphaTest_13e4d0(p, 1);
        GsPktSetAlphaTestFunc_13e4c0(p, 6, 0);
        GsPktSetOriginMode_13e2f0(p, 1);
        GsPktSetGouraud_13e3b0(p, 1);
        GsPktEnableZTest_13e460(p, 1);
        GsPktSetZTest_13e450(p, 2);
        GsPktSetZWriteMask_13e430(p, 0);
        GsPktSetTextured_13e400(p, 1);
        GsPktSetUseUV_13e3e0(p, 1);
        if (mask != -1) {
            if (mask & 1) {
                GsPktSetAlphaBlend_13e500(p, 0);
            }
            if (mask & 2) {
                GsPktSetBlendMode_13e4f0(p, 2);
            }
            if (mask & 4) {
                GsPktSetTexFilter_13e3d0(p, 0);
            }
            if (mask & 8) {
                GsPktSetUseUV_13e3e0(p, 0);
            }
        }
    }
}
