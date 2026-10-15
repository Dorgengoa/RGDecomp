#include "types.h"
/* insmenu 0x004EEFD0 -- four calls in sequence, nothing else. */
extern void insmenu_InsectVsRegDeletePanelLayout_4ef220(void);
extern void insmenu_InsectVsRegTeamPanelFadeIn_4ef190(void);
extern void insmenu_InsectVsMenuEnterRecordStep_4ef090(void);
extern void insmenu_InsectVsRegTeamCursorHide_4eee50(void);
void insmenu_InsectVsRegDeletePanelOpen_4eefd0(void)
{
    insmenu_InsectVsRegDeletePanelLayout_4ef220();
    insmenu_InsectVsRegTeamPanelFadeIn_4ef190();
    insmenu_InsectVsMenuEnterRecordStep_4ef090();
    insmenu_InsectVsRegTeamCursorHide_4eee50();
}
