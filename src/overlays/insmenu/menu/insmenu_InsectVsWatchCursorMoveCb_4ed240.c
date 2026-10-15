#include "types.h"
/* insmenu 0x004ED240 (pass-27 window) -- tail call, `j insmenu_InsectVsMenuBarToRowResize_4ee350`
 * with `addiu $6, $0, 0x21` in the delay slot.  $4 and $5 are passed
 * straight through and leave no trace, so their types are the
 * callee's and are not otherwise constrained. */
extern s32 insmenu_InsectVsMenuBarToRowResize_4ee350(void *o, s32 unused, s32 colour);
s32 insmenu_InsectVsWatchCursorMoveCb_4ed240(void *o, s32 unused)
{
    return insmenu_InsectVsMenuBarToRowResize_4ee350(o, unused, 0x21);
}
