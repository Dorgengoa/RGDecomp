/* rgp:protos */
#define RGP_SELF_factory_MotionEventTexAnimeFireThunk_504e30 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x0000504E30 -- forwarder to func_1B1130.
 *
 * Pass-27 conversion (session 7).  `j func_1B1130` with a NOP delay slot: no
 * argument is marshalled, so every parameter is passed straight through and
 * mwcc turns the tail `return` into the jump.
 */

/*rgp*/

s32 factory_MotionEventTexAnimeFireThunk_504e30(void *p, void *rgp_a1)
{
    return MotionEventTexAnimeFire_1b1130(p, (void *)rgp_a1);
}
