#include "types.h"

extern void SoundIopSendCmdG3S1_165e78(s32, s32);

void SoundThreadCmdNoteStreamReleaseMaybe_1b69f0(s32 *p0)
{
    SoundIopSendCmdG3S1_165e78(0, *p0);
}
