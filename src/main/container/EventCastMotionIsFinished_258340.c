#include "types.h"
struct E258340 { s32 f00; u8 pad004[0x8]; u8 *f0C; };
extern s32 MotionListIsFinished_171d90(u8 *q, s32 k);

s32 EventCastMotionIsFinished_258340(u8 *p, s32 i)
{
    struct E258340 *e;
    u8 *q;

    if (i < 0 || i >= 0x20) return 0;
    e = (struct E258340 *)(p + i * 16);
    if (e->f00 == 0) goto next;
    return 0;
next:
    q = e->f0C;
    if (q == 0) goto zero;
    return MotionListIsFinished_171d90(q + 0x1F0, -1);
zero:
    return 0;
}
