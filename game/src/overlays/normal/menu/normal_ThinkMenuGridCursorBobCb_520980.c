/* rgp:protos */
#define RGP_SELF_normal_ThinkMenuGridCursorBobCb_520980 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00520980 -- the two-argument forwarder onto normal_ThinkMenuGridCursorBobToCell_5209c0
 * with both trailing counters zero, then the shared 0x753B notify. */

extern u8 normal_D_00528060[];

/*rgp*/
/*rgp*/

s32 normal_ThinkMenuGridCursorBobCb_520980(void *a, void *b)
{
    normal_ThinkMenuGridCursorBobToCell_5209c0(a, b, 0, 0);
    UiSelFrameAnimStep_28d820(normal_D_00528060, 0x753B);
    return 1;
}
