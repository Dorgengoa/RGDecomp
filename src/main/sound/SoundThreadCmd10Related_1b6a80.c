#include "types.h"

typedef struct S { s32 f00; s32 f04; } S;

extern void SoundIopSendCmdG2S2_165c70(s32 a, s32 b, s32 c, s32 d);

void SoundThreadCmd10Related_1b6a80(S *p)
{
    SoundIopSendCmdG2S2_165c70(p->f00, 0x31, 0, p->f04);
}
