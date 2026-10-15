#include "types.h"

extern s32 SoundIopSendCmdG2S2_165c70(void *, s32, s32);

s32 SoundThreadCmdSeqStop_1b6aa0(void **p)
{
    return SoundIopSendCmdG2S2_165c70(*p, 0x2, 0);
}
