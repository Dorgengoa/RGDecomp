#include "types.h"
/* insmenu 0x4EFBA0 -- four calls in sequence. */
extern void insmenu_InsectVsRegSavePanelLayout_4efd90(void);
extern void insmenu_InsectVsRegSavePanelFadeIn_4efd20(void);
extern void insmenu_InsectVsMenuEnterRecordStep_4efc20(void);
extern void insmenu_InsectVsRegSaveCursorHide_4efa20(void);
void insmenu_InsectVsRegSavePanelOpen_4efba0(void)
{
    insmenu_InsectVsRegSavePanelLayout_4efd90();
    insmenu_InsectVsRegSavePanelFadeIn_4efd20();
    insmenu_InsectVsMenuEnterRecordStep_4efc20();
    insmenu_InsectVsRegSaveCursorHide_4efa20();
}
