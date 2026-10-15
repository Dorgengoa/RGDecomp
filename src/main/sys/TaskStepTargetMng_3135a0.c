#include "types.h"

/* Tail-call adapter: marshal and forward a global address. */

extern u8 D_004E7E60[];

extern s32 TargetMngStep_31f330(void *);

s32 TaskStepTargetMng_3135a0(void)
{
    return TargetMngStep_31f330(D_004E7E60);
}
