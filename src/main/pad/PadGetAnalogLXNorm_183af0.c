#pragma divbyzerocheck on
#include "types.h"

f32 PadGetAnalogLXNorm_183af0(void *param_1)
{
    s32 v = *(s32 *)((u8 *)param_1 + 0xC) - 0x80;
    s32 n;

    if (v < 50 && v > -50)
    {
        n = 0;
    }
    else if (v > 0)
    {
        n = ((v - 49) * 128) / 78;
    }
    else
    {
        n = ((v + 50) * 128) / 78;
    }
    return (f32)n / 128.0f;
}
