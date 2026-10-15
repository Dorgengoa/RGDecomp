#include "types.h"

/* Tail-call adapter: marshal and forward a global address. */

extern u8 D_004E72B0[];

extern s32 NpcObjTableStepMaybe_2fae50(void *);

s32 TaskStepNpc_3127d0(void)
{
    return NpcObjTableStepMaybe_2fae50(D_004E72B0);
}
