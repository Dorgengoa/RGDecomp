#include "types.h"

extern void SoundIopSendCmdG3S1_165e78(s32, s32);

void SoundThreadCmdNoteStreamDetachMaybe_1b69c0(s32 *p0)
{
    SoundIopSendCmdG3S1_165e78(5, *p0);
}
