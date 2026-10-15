#include "types.h"

/* Tail-call adapter: marshal and forward a global address. */

extern u8 D_004E72B0[];

extern s32 StepHeadNpcTask_2fad80(void *);

s32 TaskStepHeadNpc_3127c0(void)
{
    return StepHeadNpcTask_2fad80(D_004E72B0);
}
