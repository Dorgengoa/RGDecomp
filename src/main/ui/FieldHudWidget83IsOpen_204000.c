#include "types.h"

/* Tail-call adapter: marshal and forward a global address. */

extern u8 D_00527020[];

extern s32 func_4F9590(void *);

s32 FieldHudWidget83IsOpen_204000(void)
{
    return func_4F9590(D_00527020);
}
