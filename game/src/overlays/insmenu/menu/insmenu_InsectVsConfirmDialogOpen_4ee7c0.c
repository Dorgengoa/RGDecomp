/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsConfirmDialogOpen_4ee7c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insmenu 0x004EE7C0 -- six calls in sequence; the parameter is held in $16
 * (sq/lq) because two of them take it. */
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
void insmenu_InsectVsConfirmDialogOpen_4ee7c0(s32 a)
{
    insmenu_InsectVsConfirmDialogLayout_4ee9e0();
    insmenu_InsectVsConfirmDialogFadeIn_4ee990();
    insmenu_InsectVsConfirmDialogSetMessage_4ee810(a);
    insmenu_InsectVsYesNoCursorHide_4ee750();
    insmenu_InsectVsMenuEnterConfirm_4ee850();
    insmenu_InsectVsYesNoCursorPlace_4ee6b0();
}
