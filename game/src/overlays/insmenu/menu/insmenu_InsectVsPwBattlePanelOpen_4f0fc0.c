/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsPwBattlePanelOpen_4f0fc0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insmenu 0x4F0FC0 -- four calls in sequence. */
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
void insmenu_InsectVsPwBattlePanelOpen_4f0fc0(void)
{
    insmenu_InsectVsPwBattlePanelLayout_4f1430();
    insmenu_InsectVsPwWatchPanelFadeIn_4f1140();
    insmenu_InsectVsMenuEnterRecordStep_4f1040();
    insmenu_InsectVsPwWatchCursorHide_4f0e00();
}
