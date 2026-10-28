/* rgp:protos */
#define RGP_SELF_title_FUN_004e9ff0 1
#define RGP_SELF_title_TitleDemoMenuCursorMoveCb_4e9fd0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* title.bin overlay, 0x004E9FD0.  Ghidra missed the function at 0x004E9FF0, so
 * the previous symbol absorbed it and this SLOT HOLDS TWO FUNCTIONS -- the
 * recorded overlay-only defect where title's clamped `size:` attributes swallow
 * whatever follows the first `jr $31`.  Both are written here, in address
 * order; nothing in the overlay references the second one.
 */

/*rgp*/

s32 title_TitleDemoMenuCursorMoveCb_4e9fd0(void)
{
    PadIdleTimerReset_2f5ac0();
    return 1;
}

s32 title_FUN_004e9ff0(void)
{
    return 1;
}
