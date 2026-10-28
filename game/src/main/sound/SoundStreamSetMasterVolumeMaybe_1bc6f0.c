/* rgp:protos */
#define RGP_SELF_SoundStreamSetMasterVolumeMaybe_1bc6f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

void SoundStreamSetMasterVolumeMaybe_1bc6f0(f32 v)
{
    u32 n;

    n = (u32)((f32)32767 * v);
    SoundRpcCall_1bc5e0(0x200, 1, (n & 0xFFFF) | (n << 16));
}
