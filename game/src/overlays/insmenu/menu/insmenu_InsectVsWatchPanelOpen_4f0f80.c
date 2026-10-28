/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsWatchPanelOpen_4f0f80 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insmenu 0x4F0F80 -- four calls in sequence. */
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
void insmenu_InsectVsWatchPanelOpen_4f0f80(void)
{
    insmenu_InsectVsWatchPanelLayout_4f11d0();
    insmenu_InsectVsPwWatchPanelFadeIn_4f1140();
    insmenu_InsectVsMenuEnterRecordStep_4f1040();
    insmenu_InsectVsPwWatchCursorHide_4f0e00();
}
