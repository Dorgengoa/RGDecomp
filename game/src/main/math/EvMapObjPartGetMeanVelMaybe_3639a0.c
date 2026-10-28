/* rgp:protos */
#define RGP_SELF_EvMapObjPartGetMeanVelMaybe_3639a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef rg_u128 u128;

/*rgp*/
/*rgp*/
extern f32 D_0047D2A8;   /* %gp_rel */

void EvMapObjPartGetMeanVelMaybe_3639a0(u8 *a, u8 *b)
{
    u128 t;

    *(u128 *)b = *(u128 *)(a + 0x10);
    t = *(u128 *)(a + 0x50);
    VecAdd_13be20(b, b, &t);
    *(u128 *)b = *(u128 *)(a + 0x90);
    VecAdd_13be20(b, b, &t);
    VecScale_13be00(b, b, D_0047D2A8);
}
