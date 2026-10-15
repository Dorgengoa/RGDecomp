#include "types.h"
/* insmenu 0x004EE7C0 -- six calls in sequence; the parameter is held in $16
 * (sq/lq) because two of them take it. */
extern void insmenu_InsectVsConfirmDialogLayout_4ee9e0(s32 a);
extern void insmenu_InsectVsConfirmDialogFadeIn_4ee990(void);
extern void insmenu_InsectVsConfirmDialogSetMessage_4ee810(s32 a);
extern void insmenu_InsectVsYesNoCursorHide_4ee750(void);
extern void insmenu_InsectVsMenuEnterConfirm_4ee850(void);
extern void insmenu_InsectVsYesNoCursorPlace_4ee6b0(void);
void insmenu_InsectVsConfirmDialogOpen_4ee7c0(s32 a)
{
    insmenu_InsectVsConfirmDialogLayout_4ee9e0(a);
    insmenu_InsectVsConfirmDialogFadeIn_4ee990();
    insmenu_InsectVsConfirmDialogSetMessage_4ee810(a);
    insmenu_InsectVsYesNoCursorHide_4ee750();
    insmenu_InsectVsMenuEnterConfirm_4ee850();
    insmenu_InsectVsYesNoCursorPlace_4ee6b0();
}
