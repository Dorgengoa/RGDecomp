/* rgp:protos */
#define RGP_SELF_EvCmdMenuShopIsTransitioning_25c140 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

s32 EvCmdMenuShopIsTransitioning_25c140(s32 p0)
{
    s32 r0;
    s32 r1;

    r0 = ShopMenuIsTransitioningThunk_50ab10();
    r1 = (ScriptSetRefInt_26a1e0(p0, (s16)r0), (s32)0);
    return 1;
}
