/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsTwoPlayerPanelIsOpaque_4f1b60 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insmenu 0x4F1B60 -- `func_290770(insmenu_D_004FA180, 0x3F) >= 1.0f` returned as 0/1 through
 * c.lt.s + bc1f.
 * The return type is s32, NOT u8: a u8 return adds
 * `andi $2, $2, 0xFF` after the epilogue load, one word retail
 * does not have.  Measured both ways on insmenu_InsectVsConfirmDialogIsHidden_4ee8a0. */
extern u8 insmenu_D_004FA180[];
/*rgp*/
s32 insmenu_InsectVsTwoPlayerPanelIsOpaque_4f1b60(void) { return UiGetWidgetAlpha_290770(insmenu_D_004FA180, 0x3F) >= 1.0f; }
