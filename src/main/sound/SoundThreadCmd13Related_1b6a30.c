#include "types.h"

struct Obj0;

struct Obj0 {
    s32 m00;
    s32 m04;
};

extern void SoundIopSendCmdG2S3_165d28(s32, s32);

void SoundThreadCmd13Related_1b6a30(struct Obj0 *p0)
{
    SoundIopSendCmdG2S3_165d28(p0->m00, p0->m04);
}
