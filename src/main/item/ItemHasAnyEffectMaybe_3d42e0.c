#include "types.h"

s32 ItemHasUseEffectMaybe_3d42c0(void *arg0);
s32 ItemHasEffect28Maybe_3d42a0(void *arg0);

s32 ItemHasAnyEffectMaybe_3d42e0(void *arg0)
{
    if (ItemHasUseEffectMaybe_3d42c0(arg0) || ItemHasEffect28Maybe_3d42a0(arg0)) {
        return 1;
    }
    return 0;
}
