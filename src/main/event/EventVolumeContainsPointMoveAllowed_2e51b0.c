#include "types.h"

typedef struct O {
    u32 m00;
} O;

extern s32 EventVolumeContainsPoint_2e51f0(O *o, f32 t);

s32 EventVolumeContainsPointMoveAllowed_2e51b0(O *o)
{
    if ((o->m00 & 0x100) != 0) return 0;
    return EventVolumeContainsPoint_2e51f0(o, 0.0f);
}
