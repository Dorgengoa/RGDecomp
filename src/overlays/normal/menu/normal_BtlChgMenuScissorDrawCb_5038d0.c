#include "types.h"
/* normal 0x005038D0 -- twin of normal_FUN_005038A0, one gp displacement apart
 * (gp-0x4C40 instead of gp-0x4C30). */

extern s32 D_00480530;            /* gp - 0x4C40 */

extern void func_28C2E0(void *a, void *p, s32 x, s32 y);

s32 normal_BtlChgMenuScissorDrawCb_5038d0(void *a, s32 b, s32 c, s32 d, s32 e)
{
    func_28C2E0(a, &D_00480530, e, 0);
    return 1;
}
