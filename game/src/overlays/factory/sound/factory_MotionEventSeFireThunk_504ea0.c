/* rgp:protos */
#define RGP_SELF_factory_MotionEventSeFireThunk_504ea0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* factory.bin overlay, 0x00504EA0 -- forward to func_1B1250 with a 0 flag.
 *
 * Pass-27 conversion (session 7).  `$4`/`$5` pass through untouched and only
 * `$6` is marshalled, in the tail jump's delay slot -- so the callee takes
 * three arguments and this wrapper supplies the last one.
 * ★ Twin of factory_MotionEventSeBeginThunk_504eb0, which passes 1 through the same call.
 */

/*rgp*/

s32 factory_MotionEventSeFireThunk_504ea0(void *p, s32 a)
{
    return MotionEventSePlay_1b1250(p, a, 0);
}
