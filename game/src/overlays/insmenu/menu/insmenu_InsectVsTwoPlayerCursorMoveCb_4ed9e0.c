/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsTwoPlayerCursorMoveCb_4ed9e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insmenu 0x004ED9E0 (pass-27 window) -- tail call, `j insmenu_InsectVsMenuBarToRowResize_4ee450`
 * with `addiu $6, $0, 0x13` in the delay slot.  $4 and $5 are passed
 * straight through and leave no trace, so their types are the
 * callee's and are not otherwise constrained. */
/*rgp*/
s32 insmenu_InsectVsTwoPlayerCursorMoveCb_4ed9e0(void *o, s32 unused)
{
    return insmenu_InsectVsMenuBarToRowResize_4ee450(o, unused, 0x13);
}
