/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsRegDeletePanelOpen_4eefd0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insmenu 0x004EEFD0 -- four calls in sequence, nothing else. */
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
void insmenu_InsectVsRegDeletePanelOpen_4eefd0(void)
{
    insmenu_InsectVsRegDeletePanelLayout_4ef220();
    insmenu_InsectVsRegTeamPanelFadeIn_4ef190();
    insmenu_InsectVsMenuEnterRecordStep_4ef090();
    insmenu_InsectVsRegTeamCursorHide_4eee50();
}
