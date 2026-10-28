/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsTeamInfoEnterCb_4f45e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* insmenu 0x004F45E0 (204 bytes, 51 instructions, 9 calls) -- enter the detail
 * pane: hide the four list widgets, drop the page, show the pane widget and
 * hand the opened record to the pane driver.  Every id is `ori` because none
 * of them fits a signed 16-bit immediate.
 */

extern u8 insmenu_D_004FA180[];

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 insmenu_InsectVsTeamInfoEnterCb_4f45e0(void)
{
    void *r;

    r = insmenu_InsectVsTeamListGetSelRec_4f93b0();
    UiSetWidgetsVisibleById_291110(insmenu_D_004FA180, 0x9CAA, 0, 1);
    UiSetWidgetsVisibleById_291110(insmenu_D_004FA180, 0x88CC, 0, 1);
    UiSetWidgetsVisibleById_291110(insmenu_D_004FA180, 0x88E0, 0, 1);
    UiSetWidgetsVisibleById_291110(insmenu_D_004FA180, 0x88F4, 0, 1);
    SaveUiHideWidget_37b460(0x890D);
    UiSetWidgetsVisibleById_291110(insmenu_D_004FA180, 0x9CA7, 1, 1);
    UiSetWidgetAlpha_2907a0(insmenu_D_004FA180, 0x9CA7, 1.0f);
    InsectVsTeamInfoLayoutMaybe_379400(r, 1);
    return 1;
}
