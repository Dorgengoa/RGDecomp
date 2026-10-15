#include "types.h"

extern s32 SoundIopSendCmdG2S2_165c70(void *, s32, s32);

s32 SoundThreadCmdPause_1b6ad0(void **p)
{
    return SoundIopSendCmdG2S2_165c70(*p, 0x3, 0);
}
