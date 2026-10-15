#include "types.h"

struct T1B4160 { u8 pad000[0x40]; s32 f40; s32 f44; s32 f48; s32 f4C; s32 f50; };

s32 MotionEventCfgEventEndCmd_1b4160(s32 a, s32 b, struct T1B4160 **pp)
{
    struct T1B4160 *q = *pp;

    q->f40 = 0;
    q->f44 = 0;
    q->f48 = 0;
    q->f4C = 0;
    q->f50 = 0;
    return 1;
}
