/* rgp:protos */
#define RGP_SELF_normal_BtlChgPageSetCursorPosFromWidget_505e10 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00505E10 -- queries func_290FC0 for the two-coordinate origin of
 * `id` on the handle at +0x00 and forwards it.  The out-params sit at sp+0x2C
 * and sp+0x28: locals go from the TOP of the frame downward in DECLARATION
 * order, so `x` (0x2C) is declared FIRST.  `$5` is passed through untouched. */

typedef struct Ctx { void *f000; } Ctx;

/*rgp*/
/*rgp*/

s32 normal_BtlChgPageSetCursorPosFromWidget_505e10(Ctx *p, u16 id)
{
    s32 x;
    s32 y;

    UiGetWidgetAbsPos_290fc0(p->f000, id, &x, &y);
    normal_BtlChgPageSetCursorPos_505e60(p, x, y);
    return 1;
}
