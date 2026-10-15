#include "types.h"
/* insmenu 0x4F0FC0 -- four calls in sequence. */
extern void insmenu_InsectVsPwBattlePanelLayout_4f1430(void);
extern void insmenu_InsectVsPwWatchPanelFadeIn_4f1140(void);
extern void insmenu_InsectVsMenuEnterRecordStep_4f1040(void);
extern void insmenu_InsectVsPwWatchCursorHide_4f0e00(void);
void insmenu_InsectVsPwBattlePanelOpen_4f0fc0(void)
{
    insmenu_InsectVsPwBattlePanelLayout_4f1430();
    insmenu_InsectVsPwWatchPanelFadeIn_4f1140();
    insmenu_InsectVsMenuEnterRecordStep_4f1040();
    insmenu_InsectVsPwWatchCursorHide_4f0e00();
}
