/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsRegisterPanelOpen_4f2310 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insmenu 0x4F2310 -- four calls in sequence. */
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
void insmenu_InsectVsRegisterPanelOpen_4f2310(void)
{
    insmenu_InsectVsRegisterPanelLayout_4f2500();
    insmenu_InsectVsRegisterPanelFadeIn_4f2490();
    insmenu_InsectVsMenuEnterRecordStep_4f2350();
    insmenu_InsectVsRegisterCursorHide_4f2190();
}
