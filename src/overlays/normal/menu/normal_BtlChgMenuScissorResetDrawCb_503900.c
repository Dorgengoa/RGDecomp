#include "types.h"
/* normal 0x00503900 -- third member of the 0x005038A0 forwarder family, but
 * into func_28C2D0 (THREE arguments, $7 never set) and against an absolute
 * rodata object rather than a gp datum. */

extern const u8 D_005278F0;

extern void func_28C2D0(void *a, const u8 *p, s32 x);

s32 normal_BtlChgMenuScissorResetDrawCb_503900(void *a, s32 b, s32 c, s32 d, s32 e)
{
    func_28C2D0(a, &D_005278F0, e);
    return 1;
}
