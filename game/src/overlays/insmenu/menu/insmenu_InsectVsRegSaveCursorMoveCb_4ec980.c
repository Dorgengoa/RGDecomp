/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsRegSaveCursorMoveCb_4ec980 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insmenu 0x004EC980 (pass-27 window) -- tail call, `j insmenu_InsectVsMenuBarToRow_4ee2d0`
 * with `addiu $6, $0, 0x26` in the delay slot.  $4 and $5 are passed
 * straight through and leave no trace, so their types are the
 * callee's and are not otherwise constrained. */
/*rgp*/
s32 insmenu_InsectVsRegSaveCursorMoveCb_4ec980(void *o, s32 unused)
{
    return insmenu_InsectVsMenuBarToRow_4ee2d0(o, unused, 0x26);
}
