/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsRegTeamPanelIsHidden_4ef050 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insmenu 0x4EF050 -- `func_290770(insmenu_D_004FA180, 0x53) <= 0.0f` returned as 0/1 through
 * c.le.s + bc1t.
 * The return type is s32, NOT u8: a u8 return adds
 * `andi $2, $2, 0xFF` after the epilogue load, one word retail
 * does not have.  Measured both ways on insmenu_InsectVsConfirmDialogIsHidden_4ee8a0. */
extern u8 insmenu_D_004FA180[];
/*rgp*/
s32 insmenu_InsectVsRegTeamPanelIsHidden_4ef050(void) { return UiGetWidgetAlpha_290770(insmenu_D_004FA180, 0x53) <= 0.0f; }
