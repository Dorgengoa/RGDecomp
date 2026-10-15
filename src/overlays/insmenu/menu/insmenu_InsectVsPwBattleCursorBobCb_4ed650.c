#include "types.h"
/* insmenu 0x004ED650 (pass-27 window) -- tail call, `j insmenu_InsectVsMenuCursorBob_4ee610`
 * with `addiu $6, $0, 0x23` in the delay slot.  $4 and $5 are passed
 * straight through and leave no trace, so their types are the
 * callee's and are not otherwise constrained. */
extern s32 insmenu_InsectVsMenuCursorBob_4ee610(void *o, s32 unused, s32 colour);
s32 insmenu_InsectVsPwBattleCursorBobCb_4ed650(void *o, s32 unused)
{
    return insmenu_InsectVsMenuCursorBob_4ee610(o, unused, 0x23);
}
