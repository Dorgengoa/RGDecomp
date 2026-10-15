#include "types.h"

/* Tail-call adapter: marshal and forward a global address. */

extern u8 D_00527020[];

extern s32 func_4F4B30(void *, s32);

s32 FieldHudPartyPanelShakeStart_204060(s32 a4)
{
    return func_4F4B30(D_00527020, a4);
}
