/* rgp:protos */
#define RGP_SELF_ItemHasAnyEffectMaybe_3d42e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

s32 ItemHasAnyEffectMaybe_3d42e0(void *arg0)
{
    if (ItemHasUseEffectMaybe_3d42c0(arg0) || ItemHasEffect28Maybe_3d42a0(arg0)) {
        return 1;
    }
    return 0;
}
