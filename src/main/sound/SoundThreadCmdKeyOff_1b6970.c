#include "types.h"

extern void SoundIopSendCmdG3S2_165f20(s32, s32, s32, s32, s32, s32, s32, s32, s32);

void SoundThreadCmdKeyOff_1b6970(s32 *p)
{
    SoundIopSendCmdG3S2_165f20(p[0], 0x13, p[1], p[2], p[3], p[4], p[5], 0, 0);
}
