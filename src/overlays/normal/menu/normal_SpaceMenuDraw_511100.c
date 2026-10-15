#include "types.h"
/* normal 0x00511100 -- the guard's `lw` lands DIRECTLY in `$4` because the
 * global is also the first call's argument; the second call takes none, which
 * is why its delay slot is a bare nop with no reload.  Two `addiu $2,$0,1`
 * = two separate returns, and the frame is 0x10 with no callee-saved reg. */

extern void *D_004846B8;          /* gp - 0xAB8 */

extern s32  func_201A90(void);
extern void func_1E2680(s32 h);
extern void normal_SpaceMenuWidgetsDraw_511910(void *p);
extern void normal_SpaceMenuRouteDraw_511150(void);

s32 normal_SpaceMenuDraw_511100(void)
{
    if (D_004846B8 == NULL) {
        func_1E2680(func_201A90());
        return 1;
    }
    normal_SpaceMenuWidgetsDraw_511910(D_004846B8);
    normal_SpaceMenuRouteDraw_511150();
    return 1;
}
