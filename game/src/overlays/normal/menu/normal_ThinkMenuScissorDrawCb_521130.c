/* rgp:protos */
#define RGP_SELF_normal_ThinkMenuScissorDrawCb_521130 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00521130 -- five-integer-argument forwarder; only the first and the
 * FIFTH ($8 under the PS2 EABI) are read. */

extern u8 normal_D_00528070[];

/*rgp*/

s32 normal_ThinkMenuScissorDrawCb_521130(void *a, s32 b, s32 c, s32 d, s32 e)
{
    GsPktSetScissorDefault_28c2d0(a, normal_D_00528070, e);
    return 1;
}
