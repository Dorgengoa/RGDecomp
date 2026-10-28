/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsTopCursorFadeOut_4f28b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insmenu 0x004F28B0 (pass-27 window) -- one of seven identical members.
 * The guard is `bnel $2, $0, <epilogue>` with `ld $31` in the delay
 * slot, so the body is the FALL-THROUGH and the source condition is
 * `== 0`.  The five-argument call is the matched insmenu_InsectVsBackGuideHide_4ea000
 * verbatim: D_0047D3E0 is gp - 0x7D90, inside the gp window, so it is
 * NOT const, and the 0.0f / -1.0f are inline literals. */
extern u8 insmenu_D_004FA180[];
extern f32 D_0047D3E0;
/*rgp*/
/*rgp*/
void insmenu_InsectVsTopCursorFadeOut_4f28b0(void)
{
    if (insmenu_InsectVsTopCursorIsHidden_4f2810() == 0) {
        UiFadeWidgetAlpha_290690(insmenu_D_004FA180, 0x4, 0.0f, D_0047D3E0, -1.0f);
    }
}
