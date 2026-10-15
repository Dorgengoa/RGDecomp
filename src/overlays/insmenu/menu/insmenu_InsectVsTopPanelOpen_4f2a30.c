#include "types.h"
/* insmenu 0x4F2A30 -- four calls in sequence. */
extern void insmenu_InsectVsTopPanelLayout_4f2c20(void);
extern void insmenu_InsectVsTopPanelFadeIn_4f2bb0(void);
extern void insmenu_InsectVsMenuEnterRecordStep_4f2ab0(void);
extern void insmenu_InsectVsTopCursorHide_4f2890(void);
void insmenu_InsectVsTopPanelOpen_4f2a30(void)
{
    insmenu_InsectVsTopPanelLayout_4f2c20();
    insmenu_InsectVsTopPanelFadeIn_4f2bb0();
    insmenu_InsectVsMenuEnterRecordStep_4f2ab0();
    insmenu_InsectVsTopCursorHide_4f2890();
}
