#include "types.h"

/* Tail-call adapter: marshal and forward a global address. */

extern u8 D_00527020[];

extern s32 func_4F8D10(void *);

s32 FieldHudLogOpen_203fb0(void)
{
    return func_4F8D10(D_00527020);
}
