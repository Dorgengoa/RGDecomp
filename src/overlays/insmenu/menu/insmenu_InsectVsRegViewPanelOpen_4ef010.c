#include "types.h"
/* insmenu 0x4EF010 -- four calls in sequence. */
extern void insmenu_InsectVsRegViewPanelLayout_4ef4c0(void);
extern void insmenu_InsectVsRegTeamPanelFadeIn_4ef190(void);
extern void insmenu_InsectVsMenuEnterRecordStep_4ef090(void);
extern void insmenu_InsectVsRegTeamCursorHide_4eee50(void);
void insmenu_InsectVsRegViewPanelOpen_4ef010(void)
{
    insmenu_InsectVsRegViewPanelLayout_4ef4c0();
    insmenu_InsectVsRegTeamPanelFadeIn_4ef190();
    insmenu_InsectVsMenuEnterRecordStep_4ef090();
    insmenu_InsectVsRegTeamCursorHide_4eee50();
}
