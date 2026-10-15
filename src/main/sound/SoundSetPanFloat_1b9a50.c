#include "types.h"

extern void SoundSetPan_1b8590(s32 a, s32 b, s32 n, s32 c);

void SoundSetPanFloat_1b9a50(s32 a, s32 b, s32 c, f32 v)
{
    s32 n;

    n = (s32)(64.0f * v) + 0x40;
    if (n < 0) {
        n = 0;
    }
    if (n > 0x7F) {
        n = 0x7F;
    }
    SoundSetPan_1b8590(a, b, n, c);
}
