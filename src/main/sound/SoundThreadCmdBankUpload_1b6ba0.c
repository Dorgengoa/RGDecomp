#include "types.h"

struct S1B6BA0 { s32 f00; s32 f04; s32 f08; s32 f0C; s32 f10; };

extern s32 SoundIopSendCmdG1S0_165828(s32 z, s32 a, s32 b, s32 c, s32 d, s32 e);

s32 SoundThreadCmdBankUpload_1b6ba0(struct S1B6BA0 *p)
{
    return SoundIopSendCmdG1S0_165828(3, p->f00, p->f04, p->f08, p->f0C, p->f10);
}
