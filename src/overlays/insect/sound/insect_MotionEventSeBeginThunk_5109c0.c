#include "types.h"
/* insect 0x005109C0 -- pass-28 unnamed-listing conversion.  The 0x005109B0
 * thunk with 1 for the third argument instead of 0; the pair is what shows
 * the constant is the argument and not part of the callee. */
extern s32 func_1B1250(void *a, void *b, s32 c);

s32 insect_MotionEventSeBeginThunk_5109c0(void *a, void *b)
{
    return func_1B1250(a, b, 1);
}
