#include "types.h"

extern void SoundIopSendCmdG2S1_165bd0(s32, s32);

void SoundThreadCmdSeqDataRelease_1b6a00(s32 *p0)
{
    SoundIopSendCmdG2S1_165bd0(0, *p0);
}
