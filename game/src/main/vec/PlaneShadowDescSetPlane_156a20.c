/* rgp:protos */
#define RGP_SELF_PlaneShadowDescSetPlane_156a20 1
#include "port/game_protos.h"
#line 1
#include "types.h"
typedef rg_u128 u128;

/*rgp*/

void PlaneShadowDescSetPlane_156a20(u8 *p0, s32 p1, u128 *p2, s32 p3)
{
    VecNormalize_13bd90(p0, p1);
    *(u128 *)(p0 + 0x10) = *p2;
    VecNormalize_13bd90(p0 + 0x20, p3);
}
