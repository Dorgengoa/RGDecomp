#include "types.h"
typedef unsigned __int128 u128;

extern void VecNormalize_13bd90(void *, s32);

void PlaneShadowDescSetPlane_156a20(u8 *p0, s32 p1, u128 *p2, s32 p3)
{
    VecNormalize_13bd90(p0, p1);
    *(u128 *)(p0 + 0x10) = *p2;
    VecNormalize_13bd90(p0 + 0x20, p3);
}
