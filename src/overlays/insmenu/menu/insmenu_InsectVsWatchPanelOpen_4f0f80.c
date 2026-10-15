#include "types.h"
/* insmenu 0x4F0F80 -- four calls in sequence. */
extern void insmenu_InsectVsWatchPanelLayout_4f11d0(void);
extern void insmenu_InsectVsPwWatchPanelFadeIn_4f1140(void);
extern void insmenu_InsectVsMenuEnterRecordStep_4f1040(void);
extern void insmenu_InsectVsPwWatchCursorHide_4f0e00(void);
void insmenu_InsectVsWatchPanelOpen_4f0f80(void)
{
    insmenu_InsectVsWatchPanelLayout_4f11d0();
    insmenu_InsectVsPwWatchPanelFadeIn_4f1140();
    insmenu_InsectVsMenuEnterRecordStep_4f1040();
    insmenu_InsectVsPwWatchCursorHide_4f0e00();
}
