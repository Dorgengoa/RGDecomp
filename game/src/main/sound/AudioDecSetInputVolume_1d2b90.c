/* rgp:protos */
#define RGP_SELF_AudioDecSetInputVolume_1d2b90 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
extern f32 D_0047E304 __attribute__((section(".sdata")));

void AudioDecSetInputVolume_1d2b90(u32 x)
{
    f32 s = (f32)0x7FFF;
    f32 t;

    t = (f32)x / s;
    SoundSendCmd_1b6cc0(0x25, 2, 0, (s32)(s * (t * D_0047E304)));
}
