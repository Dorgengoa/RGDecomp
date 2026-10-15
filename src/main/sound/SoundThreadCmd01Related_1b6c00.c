#include "types.h"

extern void SoundIopSendCmdG1S2_1659a8(s32, s32);

void SoundThreadCmd01Related_1b6c00(s32 *p0)
{
    SoundIopSendCmdG1S2_1659a8(*p0, 0x1E);
}
