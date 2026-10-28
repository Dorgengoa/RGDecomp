/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsRegPwPanelFadeIn_4f0630 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insmenu 0x004F0630 -- guarded pair of calls plus a gp byte latch.
 * Same guard shape as 004EE770: `bnel $2, $0, <epilogue>` with
 * `ld $31` in the delay slot, so the body is the == 0 arm. */
/*rgp*/
extern u8 insmenu_D_004FA180[];
extern f32 D_0047D240;
extern u8 D_0048430C;
/*rgp*/
/*rgp*/
void insmenu_InsectVsRegPwPanelFadeIn_4f0630(void)
{
    if (insmenu_InsectVsRegPwPanelIsOpaque_4f0580() == 0) {
        UiSetWidgetVisible_290010(insmenu_D_004FA180, 0x4C, 1, -1);
        UiFadeWidgetAlpha_290690(insmenu_D_004FA180, 0x4C, 1.0f, D_0047D240, 0.0f);
        D_0048430C = 1;
    }
}
