#include "types.h"

struct S1B6BD0 { s32 f00; s32 f04; s32 f08; };

extern s32 SoundIopSendCmdG2S0_165b20(s32 z, s32 a, s32 b, s32 c);

s32 SoundThreadCmdSeqDataUpload_1b6bd0(struct S1B6BD0 *p)
{
    return SoundIopSendCmdG2S0_165b20(0, p->f00, p->f04, p->f08);
}
