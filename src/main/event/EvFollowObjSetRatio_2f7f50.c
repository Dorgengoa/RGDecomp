#include "types.h"

/* MAIN EvFollowObjSetRatio_2f7f50 -- clamp to [0,1].  The `sw $0` sits in the delay
   slot of a NON-likely bc1f, so it is unconditional: the member is
   zeroed first, then the clamped value is stored. */

void EvFollowObjSetRatio_2f7f50(u8 *p, f32 v)
{
    *(s32 *)(p + 0x138) = 0;
    if (v < 0.0f) {
        v = 0.0f;
    }
    if (v > 1.0f) {
        v = 1.0f;
    }
    *(f32 *)(p + 0x138) = v;
}
