/* rgp:protos */
#define RGP_SELF_factory_MotionEventEffectFireThunk_504df0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x0000504DF0 -- forwarder to func_1B0DC0.
 *
 * Pass-27 conversion (session 7).  `j func_1B0DC0` with a NOP delay slot: no
 * argument is marshalled, so every parameter is passed straight through and
 * mwcc turns the tail `return` into the jump.
 */

/*rgp*/

s32 factory_MotionEventEffectFireThunk_504df0(void *p, void *rgp_a1)
{
    return MotionEventEffectFire_1b0dc0(p, (void *)rgp_a1);
}
