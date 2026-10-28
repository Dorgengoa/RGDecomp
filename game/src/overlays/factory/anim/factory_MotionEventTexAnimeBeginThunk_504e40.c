/* rgp:protos */
#define RGP_SELF_factory_MotionEventTexAnimeBeginThunk_504e40 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x0000504E40 -- forwarder to func_1B10B0.
 *
 * Pass-27 conversion (session 7).  `j func_1B10B0` with a NOP delay slot: no
 * argument is marshalled, so every parameter is passed straight through and
 * mwcc turns the tail `return` into the jump.
 */

/*rgp*/

s32 factory_MotionEventTexAnimeBeginThunk_504e40(void *p, void *rgp_a1)
{
    return MotionEventTexAnimeBegin_1b10b0(p, (void *)rgp_a1);
}
