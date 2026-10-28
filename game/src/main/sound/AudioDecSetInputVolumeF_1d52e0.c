/* rgp:protos */
#define RGP_SELF_AudioDecSetInputVolumeF_1d52e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

void AudioDecSetInputVolumeF_1d52e0(f32 x)
{
    AudioDecSetInputVolume_1d2b90((s32)(32767 * x));
}
