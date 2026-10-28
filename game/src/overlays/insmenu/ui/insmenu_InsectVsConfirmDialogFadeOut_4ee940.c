/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsConfirmDialogFadeOut_4ee940 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insmenu 0x004EE940 -- the 004EE770 shape with a 0.0f first float, so the
 * literal is `mtc1 $0, $f12` and the lui disappears: 17 words, not 18. */
/*rgp*/
extern u8 insmenu_D_004FA180[];
extern f32 D_0047D49C;
/*rgp*/
void insmenu_InsectVsConfirmDialogFadeOut_4ee940(void)
{
    if (insmenu_InsectVsConfirmDialogIsHidden_4ee8a0() == 0) {
        UiFadeWidgetAlpha_290690(insmenu_D_004FA180, 6, 0.0f, D_0047D49C, -1.0f);
    }
}
