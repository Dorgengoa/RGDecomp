/* rgp:protos */
#define RGP_SELF_factory_MotionEventEffectStartThunk_504e00 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x0000504E00 -- forwarder to func_1B0D40.
 *
 * Pass-27 conversion (session 7).  `j func_1B0D40` with a NOP delay slot: no
 * argument is marshalled, so every parameter is passed straight through and
 * mwcc turns the tail `return` into the jump.
 */

/*rgp*/

s32 factory_MotionEventEffectStartThunk_504e00(void *p, void *rgp_a1)
{
    return MotionEventEffectStart_1b0d40(p, (void *)rgp_a1);
}
