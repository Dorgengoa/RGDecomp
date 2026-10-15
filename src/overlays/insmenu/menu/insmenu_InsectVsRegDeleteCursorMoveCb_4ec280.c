#include "types.h"
/* insmenu 0x004EC280 (pass-27 window) -- tail call, `j insmenu_InsectVsMenuBarToRow_4ee250`
 * with `addiu $6, $0, 0x54` in the delay slot.  $4 and $5 are passed
 * straight through and leave no trace, so their types are the
 * callee's and are not otherwise constrained. */
extern s32 insmenu_InsectVsMenuBarToRow_4ee250(void *o, s32 unused, s32 colour);
s32 insmenu_InsectVsRegDeleteCursorMoveCb_4ec280(void *o, s32 unused)
{
    return insmenu_InsectVsMenuBarToRow_4ee250(o, unused, 0x54);
}
