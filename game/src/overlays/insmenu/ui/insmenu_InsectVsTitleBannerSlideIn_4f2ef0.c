/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsTitleBannerSlideIn_4f2ef0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insmenu 0x004F2EF0 -- insmenu_InsectVsTitleBannerSlideOut_4f2ed0 with a leading call and -1 for
 * the fourth argument, so it needs a frame and the call is not a tail call. */
extern u8 insmenu_D_004FA180[];
extern f32 D_0047D1E8;
/*rgp*/
/*rgp*/

void insmenu_InsectVsTitleBannerSlideIn_4f2ef0(void)
{
    insmenu_InsectVsTitleBannerLayout_4ea600();
    UiMoveWidgetUniform_290f50(insmenu_D_004FA180, 0x39, 0, -1, D_0047D1E8, 0);
}
