#include "types.h"

/* factory.bin overlay, 0x0000504E10 -- forwarder to func_1B0CF0.
 *
 * Pass-27 conversion (session 7).  `j func_1B0CF0` with a NOP delay slot: no
 * argument is marshalled, so every parameter is passed straight through and
 * mwcc turns the tail `return` into the jump.
 */

extern s32 func_1B0CF0(void *p);

s32 factory_MotionEventEffectStopThunk_504e10(void *p)
{
    return func_1B0CF0(p);
}
