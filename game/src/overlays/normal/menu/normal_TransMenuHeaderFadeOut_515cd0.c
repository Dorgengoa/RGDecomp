/* rgp:protos */
#define RGP_SELF_normal_TransMenuHeaderFadeOut_515cd0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00515CD0 -- widget tint/alpha pass.  No callee-saved frame at all,
 * so both gp pointers are RE-READ at every call site rather than held. */
extern void *D_004846E8;
extern void *D_004846EC;
extern f32   D_0047DA08;
extern f32   D_0047DA18;

/*rgp*/
/*rgp*/
/*rgp*/

s32 normal_TransMenuHeaderFadeOut_515cd0(void)
{
    UiSetWidgetsVisibleById_291110(D_004846E8, 0x754C, 0, 1);
    UiSetWidgetsVisibleById_291110(D_004846E8, 0x754B, 0, 1);
    UiFadeWidgetAlpha_290690(D_004846EC, 0x84D1, 0.0f, D_0047DA08, 1.0f);
    UiFadeWidgetAlpha_290690(D_004846E8, 0x7532, 0.0f, D_0047DA08, 1.0f);
    UiMoveWidgetUniform_290f50(D_004846E8, 0x7534, -0x30, -0xF, D_0047DA18, 0);
    UiFadeWidgetAlpha_290690(D_004846E8, 0x7534, 0.0f, D_0047DA08, -1.0f);
    UiFadeWidgetAlpha_290690(D_004846E8, 0x7533, 0.0f, D_0047DA08, -1.0f);
    return 1;
}
