#include "types.h"
/* insmenu 0x4F2310 -- four calls in sequence. */
extern void insmenu_InsectVsRegisterPanelLayout_4f2500(void);
extern void insmenu_InsectVsRegisterPanelFadeIn_4f2490(void);
extern void insmenu_InsectVsMenuEnterRecordStep_4f2350(void);
extern void insmenu_InsectVsRegisterCursorHide_4f2190(void);
void insmenu_InsectVsRegisterPanelOpen_4f2310(void)
{
    insmenu_InsectVsRegisterPanelLayout_4f2500();
    insmenu_InsectVsRegisterPanelFadeIn_4f2490();
    insmenu_InsectVsMenuEnterRecordStep_4f2350();
    insmenu_InsectVsRegisterCursorHide_4f2190();
}
