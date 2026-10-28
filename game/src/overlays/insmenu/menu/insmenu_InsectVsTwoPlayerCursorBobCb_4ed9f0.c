/* rgp:protos */
#define RGP_SELF_insmenu_InsectVsTwoPlayerCursorBobCb_4ed9f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insmenu 0x004ED9F0 (pass-27 window) -- tail call, `j insmenu_InsectVsMenuCursorBob_4ee610`
 * with `addiu $6, $0, 0x14` in the delay slot.  $4 and $5 are passed
 * straight through and leave no trace, so their types are the
 * callee's and are not otherwise constrained. */
/*rgp*/
s32 insmenu_InsectVsTwoPlayerCursorBobCb_4ed9f0(void *o, s32 unused)
{
    return insmenu_InsectVsMenuCursorBob_4ee610(o, unused, 0x14);
}
