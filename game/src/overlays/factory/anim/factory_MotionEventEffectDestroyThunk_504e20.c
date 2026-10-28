/* rgp:protos */
#define RGP_SELF_factory_MotionEventEffectDestroyThunk_504e20 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x0000504E20 -- forwarder to func_1B0CA0.
 *
 * Pass-27 conversion (session 7).  `j func_1B0CA0` with a NOP delay slot: no
 * argument is marshalled, so every parameter is passed straight through and
 * mwcc turns the tail `return` into the jump.
 */

/*rgp*/

s32 factory_MotionEventEffectDestroyThunk_504e20(void *p, void *rgp_a1)
{
    return MotionEventEffectDestroy_1b0ca0(p, (void *)rgp_a1);
}
