#include "types.h"

/* factory.bin overlay, 0x00504EB0 -- forward to func_1B1250 with a 1 flag.
 *
 * Pass-27 conversion (session 7).  Twin of factory_MotionEventSeFireThunk_504ea0; the only difference
 * is the constant the delay slot puts in `$6`.
 */

extern s32 func_1B1250(void *p, s32 a, s32 flag);

s32 factory_MotionEventSeBeginThunk_504eb0(void *p, s32 a)
{
    return func_1B1250(p, a, 1);
}
