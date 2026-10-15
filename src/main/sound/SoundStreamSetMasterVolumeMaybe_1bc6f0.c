#include "types.h"

extern void SoundRpcCall_1bc5e0(s32, s32, u32);

void SoundStreamSetMasterVolumeMaybe_1bc6f0(f32 v)
{
    u32 n;

    n = (u32)((f32)32767 * v);
    SoundRpcCall_1bc5e0(0x200, 1, (n & 0xFFFF) | (n << 16));
}
