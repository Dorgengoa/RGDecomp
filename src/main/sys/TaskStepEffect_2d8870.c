#include "types.h"

/* Tail-call adapter: marshal and forward a global address. */

extern u8 D_004DCD50[];

extern s32 EffectMgrTick_2e3070(void *);

s32 TaskStepEffect_2d8870(void)
{
    return EffectMgrTick_2e3070(D_004DCD50);
}
