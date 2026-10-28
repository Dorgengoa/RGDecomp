/* rgp:protos */
#define RGP_SELF_factory_MotionEventSeBeginThunk_504eb0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x00504EB0 -- forward to func_1B1250 with a 1 flag.
 *
 * Pass-27 conversion (session 7).  Twin of factory_MotionEventSeFireThunk_504ea0; the only difference
 * is the constant the delay slot puts in `$6`.
 */

/*rgp*/

s32 factory_MotionEventSeBeginThunk_504eb0(void *p, s32 a)
{
    return MotionEventSePlay_1b1250(p, a, 1);
}
