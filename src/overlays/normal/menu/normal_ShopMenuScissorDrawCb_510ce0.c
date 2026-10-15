#include "types.h"
/* normal 0x00510CE0 -- pass-through: `$4` is forwarded untouched and the
 * FIFTH integer parameter (EABI `$8`) becomes argument three. */
extern const u8 D_00527E80[];
extern void func_28C2D0(void *a, const void *b, s32 c);

s32 normal_ShopMenuScissorDrawCb_510ce0(void *a, s32 b, s32 c, s32 d, s32 e)
{
    func_28C2D0(a, D_00527E80, e);
    return 1;
}
