#include "types.h"

struct T1B66B0 { s32 f00; s32 f04; };
struct L1B66B0 { s32 f00; s32 f04; s16 f08; s16 f0A; s32 f0C; s32 f10; s32 f14; s32 f18; s32 f1C; };

extern void sceSdRemote_1229e8(s32 a, s32 b, s32 c, struct L1B66B0 *l);

s32 SoundThreadCmdSetReverbMode_1b66b0(struct T1B66B0 *p)
{
    struct L1B66B0 l;
    s32 c;

    c = p->f00 != 0;
    l.f04 = p->f04 | 0x100;
    l.f08 = 0;
    l.f0A = 0;
    sceSdRemote_1229e8(1, 0x8130, c, &l);
    return 0;
}
