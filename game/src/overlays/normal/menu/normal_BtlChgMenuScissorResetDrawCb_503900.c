/* rgp:protos */
#define RGP_SELF_normal_BtlChgMenuScissorResetDrawCb_503900 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00503900 -- third member of the 0x005038A0 forwarder family, but
 * into func_28C2D0 (THREE arguments, $7 never set) and against an absolute
 * rodata object rather than a gp datum. */

extern u8 normal_D_005278F0;

/*rgp*/

s32 normal_BtlChgMenuScissorResetDrawCb_503900(void *a, s32 b, s32 c, s32 d, s32 e)
{
    GsPktSetScissorDefault_28c2d0(a, &normal_D_005278F0, e);
    return 1;
}
