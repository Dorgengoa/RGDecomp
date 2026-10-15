#include "types.h"

extern void SoundIopSendCmdG3S0_165dc8(s32, s32);

void SoundThreadCmdNoteStreamCreateMaybe_1b6bc0(s32 *p0)
{
    SoundIopSendCmdG3S0_165dc8(0, *p0);
}
