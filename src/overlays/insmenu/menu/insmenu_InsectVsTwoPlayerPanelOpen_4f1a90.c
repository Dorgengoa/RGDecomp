#include "types.h"
/* insmenu 0x4F1A90 -- four calls in sequence. */
extern void insmenu_InsectVsTwoPlayerPanelLayout_4f1c80(void);
extern void insmenu_InsectVsTwoPlayerPanelFadeIn_4f1c10(void);
extern void insmenu_InsectVsMenuEnterRecordStep_4f1b10(void);
extern void insmenu_InsectVsTwoPlayerCursorHide_4f1910(void);
void insmenu_InsectVsTwoPlayerPanelOpen_4f1a90(void)
{
    insmenu_InsectVsTwoPlayerPanelLayout_4f1c80();
    insmenu_InsectVsTwoPlayerPanelFadeIn_4f1c10();
    insmenu_InsectVsMenuEnterRecordStep_4f1b10();
    insmenu_InsectVsTwoPlayerCursorHide_4f1910();
}
