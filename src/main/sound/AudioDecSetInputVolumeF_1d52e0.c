#include "types.h"

extern void AudioDecSetInputVolume_1d2b90(s32 v);

void AudioDecSetInputVolumeF_1d52e0(f32 x)
{
    AudioDecSetInputVolume_1d2b90((s32)(32767 * x));
}
