/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsRegisterPanelIsVisible_4f2360 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insmenu 0x004F2360 (pass-27 window) -- `c.le.s $f0, $f1` + `bc1f` is
 * `> 0.0f`, returned as 0/1.  The return is s32, NOT u8: a u8 return
 * adds `andi $2, $2, 0xFF` after the epilogue load.  Shape-identical to
 * the matched insmenu_InsectVsConfirmDialogIsVisible_4ee860. */
extern u8 insmenu_D_004FA180[];
/*rgp*/
s32 insmenu_InsectVsRegisterPanelIsVisible_4f2360(void) { return UiGetWidgetAlpha_290770(insmenu_D_004FA180, 0x15) > 0.0f; }
