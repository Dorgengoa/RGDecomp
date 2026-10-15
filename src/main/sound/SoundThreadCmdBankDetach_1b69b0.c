#include "types.h"

extern void SoundIopSendCmdG1S1_165900(s32, s32);

void SoundThreadCmdBankDetach_1b69b0(s32 *p0)
{
    SoundIopSendCmdG1S1_165900(5, *p0);
}
