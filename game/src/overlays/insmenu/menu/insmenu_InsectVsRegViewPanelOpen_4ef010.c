/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsRegViewPanelOpen_4ef010 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insmenu 0x4EF010 -- four calls in sequence. */
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
void insmenu_InsectVsRegViewPanelOpen_4ef010(void)
{
    insmenu_InsectVsRegViewPanelLayout_4ef4c0();
    insmenu_InsectVsRegTeamPanelFadeIn_4ef190();
    insmenu_InsectVsMenuEnterRecordStep_4ef090();
    insmenu_InsectVsRegTeamCursorHide_4eee50();
}
