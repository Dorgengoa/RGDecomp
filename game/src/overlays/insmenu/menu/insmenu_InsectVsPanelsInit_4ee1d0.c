/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsPanelsInit_4ee1d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* insmenu 0x004EE1D0 (120 bytes, 30 instructions, 12 calls) -- rebuild every
 * panel of the page, in order.
 */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 insmenu_InsectVsPanelsInit_4ee1d0(void)
{
    GetGameData_1fede0();
    insmenu_InsectVsTitleBannerHide_4f2e80();
    insmenu_InsectVsTopPanelHide_4f2b40();
    insmenu_InsectVsRegisterPanelHide_4f2420();
    insmenu_InsectVsTwoPlayerPanelHide_4f1ba0();
    insmenu_InsectVsPwWatchPanelHide_4f10d0();
    insmenu_InsectVsRegPwPanelHide_4f05c0();
    insmenu_InsectVsRegSavePanelHide_4efcb0();
    insmenu_InsectVsRegTeamPanelHide_4ef120();
    insmenu_InsectVsConfirmDialogHide_4ee920();
    insmenu_InsectVsBackGuideInit_4ea060();
    insmenu_InsectVsTitleBannerOpen_4f2e50();
    return 1;
}
