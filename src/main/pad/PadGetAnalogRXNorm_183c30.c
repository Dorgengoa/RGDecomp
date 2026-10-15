#include "types.h"

#pragma divbyzerocheck on

f32 PadGetAnalogRXNorm_183c30(void *arg0) {
    s32 v;
    s32 t;

    t = *(s32 *)((u8 *)arg0 + 0x14) - 0x80;
    if (t < 0x32 && t > -0x32) {
        v = 0;
    } else if (t > 0) {
        v = ((t - 0x31) << 7) / 0x4E;
    } else {
        v = ((t + 0x32) << 7) / 0x4E;
    }
    return (f32)v / 128.0f;
}
