#include "types.h"

/* Tail-call adapter: marshal and forward a global address. */

extern u8 D_00527020[];

extern s32 func_4EFB10(void *, s32);

s32 FieldHudAllySuggestRefreshMaybe_203c70(s32 a4)
{
    return func_4EFB10(D_00527020, a4);
}
