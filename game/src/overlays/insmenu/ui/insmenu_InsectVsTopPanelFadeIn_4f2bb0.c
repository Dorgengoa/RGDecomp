/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsTopPanelFadeIn_4f2bb0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insmenu 0x004F2BB0 -- the insmenu_FUN_004EFD20 guard shape.  The third
 * argument of func_290010 is `daddu $6, $5, $0` -- mwcc reuses the 1 already
 * materialised for $5 rather than re-materialising it, which is why this
 * function's mnemonic sequence does not hash into that family. */
/*rgp*/
extern u8 insmenu_D_004FA180[];
extern f32 D_0047D240;
extern u8 D_0048430C;
/*rgp*/
/*rgp*/
void insmenu_InsectVsTopPanelFadeIn_4f2bb0(void)
{
    if (insmenu_InsectVsTopPanelIsOpaque_4f2b00() == 0) {
        UiSetWidgetVisible_290010(insmenu_D_004FA180, 1, 1, -1);
        UiFadeWidgetAlpha_290690(insmenu_D_004FA180, 1, 1.0f, D_0047D240, 0.0f);
        D_0048430C = 1;
    }
}
