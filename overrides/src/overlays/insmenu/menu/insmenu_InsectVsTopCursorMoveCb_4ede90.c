/* rg-override: replaces game/src/overlays/insmenu/menu/insmenu_InsectVsTopCursorMoveCb_4ede90.c sha256 9b21b9e78ff5a8bcdaa3a51a9a88dbb412c51b8fa7f707c3126c7cd7ef8d0a2d
 * why: the mode list's highlight bar: wide on rows 0..4 (Online Battle is row 4), short on Return to
 * title (row 5); the shared insmenu_InsectVsMenuBarToRowSetW_4ee570 keeps its 4-row rule */
/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsTopCursorMoveCb_4ede90 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insmenu 0x004EDE90 (pass-27 window) -- tail call, `j insmenu_InsectVsMenuBarToRowSetW_4ee570`
 * with `addiu $6, $0, 0x2` in the delay slot.  $4 and $5 are passed
 * straight through and leave no trace, so their types are the
 * callee's and are not otherwise constrained. */
/*rgp*/
typedef struct RgRow { u8 pad00[6]; s16 field06; u8 pad08[0xA]; s16 field12; } RgRow;   /* rg-override */
extern u8 insmenu_D_004FA180[];
s32 insmenu_InsectVsTopCursorMoveCb_4ede90(void *o, s32 unused)
{
    RgRow *r = (RgRow *)o;
    (void)unused;
    UiSetWidgetPos_290f60(insmenu_D_004FA180, 2, 0, r->field12 * r->field06);
    UiSetSpriteW_28fbf0(insmenu_D_004FA180, 2, r->field12 < 5 ? 0x126 : 0x76, 0);
    return 1;
}
