#include "types.h"
/* insmenu 0x004EDE90 (pass-27 window) -- tail call, `j insmenu_InsectVsMenuBarToRowSetW_4ee570`
 * with `addiu $6, $0, 0x2` in the delay slot.  $4 and $5 are passed
 * straight through and leave no trace, so their types are the
 * callee's and are not otherwise constrained. */
extern s32 insmenu_InsectVsMenuBarToRowSetW_4ee570(void *o, s32 unused, s32 colour);
s32 insmenu_InsectVsTopCursorMoveCb_4ede90(void *o, s32 unused)
{
    return insmenu_InsectVsMenuBarToRowSetW_4ee570(o, unused, 0x2);
}
