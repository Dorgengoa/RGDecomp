/* rgp:protos */
#define RGP_SELF_normal_SpaceMenuDraw_511100 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00511100 -- the guard's `lw` lands DIRECTLY in `$4` because the
 * global is also the first call's argument; the second call takes none, which
 * is why its delay slot is a bare nop with no reload.  Two `addiu $2,$0,1`
 * = two separate returns, and the frame is 0x10 with no callee-saved reg. */

extern void *D_004846B8;          /* gp - 0xAB8 */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 normal_SpaceMenuDraw_511100(void)
{
    if (D_004846B8 == NULL) {
        MapMgrWarpMenuDraw_1e2680(((s32)GetMapMgr_201a90()));
        return 1;
    }
    normal_SpaceMenuWidgetsDraw_511910(D_004846B8);
    normal_SpaceMenuRouteDraw_511150();
    return 1;
}
