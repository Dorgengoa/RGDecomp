#include "types.h"

/* Tail-call adapter: marshal and forward a global address. */

extern u8 D_00527020[];

extern s32 func_4F88B0(void *);

s32 FieldHudLogClose_203fa0(void)
{
    return func_4F88B0(D_00527020);
}
