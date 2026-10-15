#include "types.h"

extern void SoundSendCmd_1b6cc0(s32 a, s32 b, s32 c, s32 d);
extern const f32 D_0047E304 __attribute__((section(".sdata")));

void AudioDecSetInputVolume_1d2b90(u32 x)
{
    f32 s = (f32)0x7FFF;
    f32 t;

    t = (f32)x / s;
    SoundSendCmd_1b6cc0(0x25, 2, 0, (s32)(s * (t * D_0047E304)));
}
