#include "types.h"

extern f32 FloatInRange_1c9280(void);

f32 FloatOutOfRange_1c9210(void)
{
    f32 x;
    f32 z;
    s32 temp_2;

    x = FloatInRange_1c9280();
    z = 0.0f;
    temp_2 = (x != z) ^ 1;
    return (f32) (u32) temp_2;
}
