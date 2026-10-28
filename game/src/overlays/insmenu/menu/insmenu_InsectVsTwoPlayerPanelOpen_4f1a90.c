/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsTwoPlayerPanelOpen_4f1a90 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insmenu 0x4F1A90 -- four calls in sequence. */
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
void insmenu_InsectVsTwoPlayerPanelOpen_4f1a90(void)
{
    insmenu_InsectVsTwoPlayerPanelLayout_4f1c80();
    insmenu_InsectVsTwoPlayerPanelFadeIn_4f1c10();
    insmenu_InsectVsMenuEnterRecordStep_4f1b10();
    insmenu_InsectVsTwoPlayerCursorHide_4f1910();
}
