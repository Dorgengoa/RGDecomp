/* rgp:protos */
#define RGP_SELF_normal_ShopMenuScissorDrawCb_510ce0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00510CE0 -- pass-through: `$4` is forwarded untouched and the
 * FIFTH integer parameter (EABI `$8`) becomes argument three. */
extern u8 normal_D_00527E80[];
/*rgp*/

s32 normal_ShopMenuScissorDrawCb_510ce0(void *a, s32 b, s32 c, s32 d, s32 e)
{
    GsPktSetScissorDefault_28c2d0(a, normal_D_00527E80, e);
    return 1;
}
