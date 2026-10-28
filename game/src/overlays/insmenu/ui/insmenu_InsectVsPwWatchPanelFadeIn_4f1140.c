/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsPwWatchPanelFadeIn_4f1140 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insmenu 0x004F1140 -- guarded triple: a fade setup, a four-way 1.0f colour
 * write and a placement, then the gp byte latch.  Same guard shape as
 * 004EFD20 -- `bnel $2, $0, <epilogue>` with `ld $31` in the delay slot,
 * so the body is the == 0 arm. */
/*rgp*/
extern u8 insmenu_D_004FA180[];
extern f32 D_0047D240;
extern u8 D_0048430C;
/*rgp*/
/*rgp*/
/*rgp*/
void insmenu_InsectVsPwWatchPanelFadeIn_4f1140(void)
{
    if (insmenu_InsectVsPwWatchPanelIsOpaque_4f1090() == 0) {
        UiSetWidgetVisible_290010(insmenu_D_004FA180, 0x1F, 1, -1);
        UiSetWidgetColor_2905b0(insmenu_D_004FA180, 0x1F, 1.0f, 1.0f, 1.0f, 1.0f);
        UiFadeWidgetAlpha_290690(insmenu_D_004FA180, 0x1F, 1.0f, D_0047D240, 0.0f);
        D_0048430C = 1;
    }
}
