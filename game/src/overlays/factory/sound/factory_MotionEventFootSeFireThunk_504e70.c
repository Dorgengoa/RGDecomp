/* rgp:protos */
#define RGP_SELF_factory_MotionEventFootSeFireThunk_504e70 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x0000504E70 -- forwarder to func_1B1190.
 *
 * Pass-27 conversion (session 7).  `j func_1B1190` with a NOP delay slot: no
 * argument is marshalled, so every parameter is passed straight through and
 * mwcc turns the tail `return` into the jump.
 */

/*rgp*/

s32 factory_MotionEventFootSeFireThunk_504e70(void *p, void *rgp_a1)
{
    return MotionEventFootSeFire_1b1190(p, (void *)rgp_a1);
}
