#include "types.h"

/* Tail-call adapter: marshal and forward a global address. */

extern u8 D_00527020[];

extern s32 func_4F0CF0(void *);

s32 TaskStepMenuBtlEsc_203d10(void)
{
    return func_4F0CF0(D_00527020);
}
