/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsRegPwPanelFadeOut_4f05e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insmenu 0x004F05E0 -- the 004EE770 shape with a 0.0f first float, so that
 * literal is `mtc1 $0, $f12` and its lui disappears: 17 words. */
/*rgp*/
extern u8 insmenu_D_004FA180[];
extern f32 D_0047D3D8;
/*rgp*/
void insmenu_InsectVsRegPwPanelFadeOut_4f05e0(void)
{
    if (insmenu_InsectVsRegPwPanelIsHidden_4f04f0() == 0) {
        UiFadeWidgetAlpha_290690(insmenu_D_004FA180, 0x4C, 0.0f, D_0047D3D8, -1.0f);
    }
}
