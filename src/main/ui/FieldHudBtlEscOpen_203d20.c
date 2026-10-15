#include "types.h"

/* Tail-call adapter: marshal and forward a global address. */

extern u8 D_00527020[];

extern s32 func_4F1030(void *, s32);

s32 FieldHudBtlEscOpen_203d20(s32 a4)
{
    return func_4F1030(D_00527020, a4);
}
