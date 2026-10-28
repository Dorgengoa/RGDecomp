/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsTeamPwEnterCb_4f43c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insmenu 0x004F43C0 -- feed one call's result straight into the next
 * (`daddu $4, $2, $0` in the second jal's delay slot), return 1. */
/*rgp*/
/*rgp*/
s32 insmenu_InsectVsTeamPwEnterCb_4f43c0(void)
{
    InsectVsTeamPanelSetupMaybe_379000(insmenu_InsectVsTeamListGetSelRec_4f93b0(), 1);
    return 1;
}
