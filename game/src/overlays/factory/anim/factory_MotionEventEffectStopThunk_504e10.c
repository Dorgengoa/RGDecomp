/* rgp:protos */
#define RGP_SELF_factory_MotionEventEffectStopThunk_504e10 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x0000504E10 -- forwarder to func_1B0CF0.
 *
 * Pass-27 conversion (session 7).  `j func_1B0CF0` with a NOP delay slot: no
 * argument is marshalled, so every parameter is passed straight through and
 * mwcc turns the tail `return` into the jump.
 */

/*rgp*/

s32 factory_MotionEventEffectStopThunk_504e10(void *p, void *rgp_a1)
{
    return MotionEventEffectStop_1b0cf0(p, (void *)rgp_a1);
}
