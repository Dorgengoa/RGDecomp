/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsConfirmDialogFadeIn_4ee990 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insmenu 0x004EE990 -- the insmenu_FUN_004EFD20 guard shape with only the
 * second call: `bnel $2, $0, <epilogue>` carrying `ld $31`, so the body is the
 * == 0 arm. */
/*rgp*/
extern u8 insmenu_D_004FA180[];
extern f32 D_0047D240;
extern u8 D_0048430C;
/*rgp*/
void insmenu_InsectVsConfirmDialogFadeIn_4ee990(void)
{
    if (insmenu_InsectVsConfirmDialogIsOpaque_4ee8e0() == 0) {
        UiFadeWidgetAlpha_290690(insmenu_D_004FA180, 6, 1.0f, D_0047D240, 0.0f);
        D_0048430C = 1;
    }
}
