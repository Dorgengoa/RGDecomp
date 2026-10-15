#include "types.h"
/* insmenu 0x4F04B0 -- four calls in sequence. */
extern void insmenu_InsectVsRegPwPanelLayout_4f06a0(void);
extern void insmenu_InsectVsRegPwPanelFadeIn_4f0630(void);
extern void insmenu_InsectVsMenuEnterRecordStep_4f0530(void);
extern void insmenu_InsectVsRegPwCursorHide_4f0330(void);
void insmenu_InsectVsRegPwPanelOpen_4f04b0(void)
{
    insmenu_InsectVsRegPwPanelLayout_4f06a0();
    insmenu_InsectVsRegPwPanelFadeIn_4f0630();
    insmenu_InsectVsMenuEnterRecordStep_4f0530();
    insmenu_InsectVsRegPwCursorHide_4f0330();
}
