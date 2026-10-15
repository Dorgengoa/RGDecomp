#include "types.h"

extern void SoundIopSendCmdG2S1_165bd0(s32, s32);

void SoundThreadCmdSeqDetach_1b69d0(s32 *p0)
{
    SoundIopSendCmdG2S1_165bd0(5, *p0);
}
