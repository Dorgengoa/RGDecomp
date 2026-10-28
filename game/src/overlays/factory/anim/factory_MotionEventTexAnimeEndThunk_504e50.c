/* rgp:protos */
#define RGP_SELF_factory_MotionEventTexAnimeEndThunk_504e50 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x0000504E50 -- forwarder to func_1B1030.
 *
 * Pass-27 conversion (session 7).  `j func_1B1030` with a NOP delay slot: no
 * argument is marshalled, so every parameter is passed straight through and
 * mwcc turns the tail `return` into the jump.
 */

/*rgp*/

s32 factory_MotionEventTexAnimeEndThunk_504e50(void *p, void *rgp_a1)
{
    return MotionEventTexAnimeEnd_1b1030(p, (void *)rgp_a1);
}
