#include "types.h"

/* title.bin overlay, 0x004E9FD0.  Ghidra missed the function at 0x004E9FF0, so
 * the previous symbol absorbed it and this SLOT HOLDS TWO FUNCTIONS -- the
 * recorded overlay-only defect where title's clamped `size:` attributes swallow
 * whatever follows the first `jr $31`.  Both are written here, in address
 * order; nothing in the overlay references the second one.
 */

extern void func_2F5AC0(void);

s32 title_TitleDemoMenuCursorMoveCb_4e9fd0(void)
{
    func_2F5AC0();
    return 1;
}

s32 title_FUN_004e9ff0(void)
{
    return 1;
}
