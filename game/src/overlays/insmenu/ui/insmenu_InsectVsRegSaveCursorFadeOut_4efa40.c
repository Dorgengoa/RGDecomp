/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsRegSaveCursorFadeOut_4efa40 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insmenu 0x004EFA40 (pass-27 window) -- one of seven identical members.
 * The guard is `bnel $2, $0, <epilogue>` with `ld $31` in the delay
 * slot, so the body is the FALL-THROUGH and the source condition is
 * `== 0`.  The five-argument call is the matched insmenu_InsectVsBackGuideHide_4ea000
 * verbatim: D_0047D3D8 is gp - 0x7D98, inside the gp window, so it is
 * NOT const, and the 0.0f / -1.0f are inline literals. */
extern u8 insmenu_D_004FA180[];
extern f32 D_0047D3D8;
/*rgp*/
/*rgp*/
void insmenu_InsectVsRegSaveCursorFadeOut_4efa40(void)
{
    if (insmenu_InsectVsRegSaveCursorIsHidden_4ef9a0() == 0) {
        UiFadeWidgetAlpha_290690(insmenu_D_004FA180, 0x29, 0.0f, D_0047D3D8, -1.0f);
    }
}
