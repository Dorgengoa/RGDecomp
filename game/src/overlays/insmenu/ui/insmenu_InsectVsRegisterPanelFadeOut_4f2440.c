/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsRegisterPanelFadeOut_4f2440 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insmenu 0x004F2440 -- the 004EE770 shape with a 0.0f first float, so that
 * literal is `mtc1 $0, $f12` and its lui disappears: 17 words. */
/*rgp*/
extern u8 insmenu_D_004FA180[];
extern f32 D_0047D3E0;
/*rgp*/
void insmenu_InsectVsRegisterPanelFadeOut_4f2440(void)
{
    if (insmenu_InsectVsRegisterPanelIsHidden_4f23a0() == 0) {
        UiFadeWidgetAlpha_290690(insmenu_D_004FA180, 0x15, 0.0f, D_0047D3E0, -1.0f);
    }
}
