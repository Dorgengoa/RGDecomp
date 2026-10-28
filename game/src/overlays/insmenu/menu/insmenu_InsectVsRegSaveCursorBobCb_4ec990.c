/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsRegSaveCursorBobCb_4ec990 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insmenu 0x004EC990 (pass-27 window) -- tail call, `j insmenu_InsectVsMenuCursorBob_4ee610`
 * with `addiu $6, $0, 0x29` in the delay slot.  $4 and $5 are passed
 * straight through and leave no trace, so their types are the
 * callee's and are not otherwise constrained. */
/*rgp*/
s32 insmenu_InsectVsRegSaveCursorBobCb_4ec990(void *o, s32 unused)
{
    return insmenu_InsectVsMenuCursorBob_4ee610(o, unused, 0x29);
}
