#include "types.h"

extern f32 VecDistance_13d3d0(void *, void *);

/* Three edge lengths summed into +0x130, then divided by 6.0f (0x40C00000). */
void EvMapObjPartCalcRadiusMaybe_363850(u8 *o)
{
    *(f32 *)(o + 0x130) = VecDistance_13d3d0(o + 0xC0, o + 0xD0);
    *(f32 *)(o + 0x130) = *(f32 *)(o + 0x130) + VecDistance_13d3d0(o + 0xD0, o + 0xE0);
    *(f32 *)(o + 0x130) = *(f32 *)(o + 0x130) + VecDistance_13d3d0(o + 0xE0, o + 0xC0);
    *(f32 *)(o + 0x130) = *(f32 *)(o + 0x130) / 6.0f;
}
