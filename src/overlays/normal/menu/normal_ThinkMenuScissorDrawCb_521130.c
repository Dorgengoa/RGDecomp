#include "types.h"
/* normal 0x00521130 -- five-integer-argument forwarder; only the first and the
 * FIFTH ($8 under the PS2 EABI) are read. */

extern const u8 D_00528070[];

extern void func_28C2D0(void *a, const u8 *p, s32 e);

s32 normal_ThinkMenuScissorDrawCb_521130(void *a, s32 b, s32 c, s32 d, s32 e)
{
    func_28C2D0(a, D_00528070, e);
    return 1;
}
