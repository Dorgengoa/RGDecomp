#include "types.h"

/* insmenu 0x004F9580 (68 bytes) -- if the fifth parameter is set, read one
 * widget's value and push it at the object the first parameter names.
 *
 * ★ The guard tests $8, which is argument FIVE: mwcc's PS2 target is EABI and
 * passes eight integer arguments in $4..$11.  Four of the five parameters are
 * never read, and only the count is recoverable from the object. */

extern const u8 D_004FA180[];

extern f32  func_290770(const void *a, s32 b);
extern void func_3768D0(void *o, f32 v);

s32 insmenu_InsectVsSaveDrawBgCb_4f9580(void *obj, s32 b, s32 c, s32 d, s32 on)
{
    if (on) {
        func_3768D0(obj, func_290770(D_004FA180, 0x88B9));
    }
    return 0;
}
