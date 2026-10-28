/* rgp:protos */
#define RGP_SELF_normal_BtlChgMenuScissorDrawCb_5038a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x005038A0 -- forwarder whose THIRD argument is the caller's FIFTH
 * integer ($8): under the PS2 EABI $4-$8 are all integer argument registers,
 * so the prototype needs five ints for `$8` to be reachable.  The gp datum is
 * ADDRESS-TAKEN, so it must be declared small to stay in small data.
 * Twin of normal_FUN_005038D0 (gp-0x4C40). */

extern s32 D_00480540;            /* gp - 0x4C30 */

/*rgp*/

s32 normal_BtlChgMenuScissorDrawCb_5038a0(void *a, s32 b, s32 c, s32 d, s32 e)
{
    GsPktSetScissor_28c2e0(a, &D_00480540, e, 0);
    return 1;
}
