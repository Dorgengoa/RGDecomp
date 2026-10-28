/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsTeamListCancel_4f4ea0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* insmenu 0x004F4EA0 (96 bytes, 24 instructions, 5 calls) -- enter the page:
 * set the mode, run the page builder, cue the two widget animations.
 * 0x9CAA and 0x88B9 do not fit a signed 16-bit immediate, which is why they
 * are `ori` and not `addiu`.
 */

extern u8 insmenu_D_004FA180[];
extern u8 insmenu_D_004FA1A0[];
extern f32 D_0047D3BC;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 insmenu_InsectVsTeamListCancel_4f4ea0(void)
{
    PlayMenuSeThunk_289ef0(6);
    insmenu_InsectVsLoadWidgetsFade_4f6ac0(2);
    UiFadeWidgetAlpha_290690(insmenu_D_004FA180, 0x9CAA, 0.0f, D_0047D3BC, 0.0f);
    insmenu_InsectVsLoadPanelLayout_4f7dd0();
    UiEntryListSelectByTag_28ea90(insmenu_D_004FA1A0, 0x88B9, 0);
    return 1;
}
