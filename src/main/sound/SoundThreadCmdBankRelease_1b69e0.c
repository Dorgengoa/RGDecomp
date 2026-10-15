#include "types.h"

extern void SoundIopSendCmdG1S1_165900(s32, s32);

void SoundThreadCmdBankRelease_1b69e0(s32 *p0)
{
    SoundIopSendCmdG1S1_165900(3, *p0);
}
