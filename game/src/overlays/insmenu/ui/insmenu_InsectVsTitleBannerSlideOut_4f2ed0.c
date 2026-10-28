/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsTitleBannerSlideOut_4f2ed0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insmenu 0x004F2ED0 -- a single six-argument tail call.  D_0047D1E8 is
 * gp - 0x7F88, inside the gp window, so it is NOT const. */
extern u8 insmenu_D_004FA180[];
extern f32 D_0047D1E8;
/*rgp*/

void insmenu_InsectVsTitleBannerSlideOut_4f2ed0(void)
{
    UiMoveWidgetUniform_290f50(insmenu_D_004FA180, 0x39, 0, -0x3C, D_0047D1E8, 0);
}
