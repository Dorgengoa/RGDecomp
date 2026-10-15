#include "types.h"

struct N1B4910 { struct N1B4910 *f00; };
struct T1B4910 { struct N1B4910 *f00; };

extern s32 MotionEventBlockReleaseHandlers_1b2420(u8 *q);

s32 MotionEventListReleaseHandlers_1b4910(struct T1B4910 *p)
{
    struct N1B4910 *n;
    s32 sum;
    s32 r;

    n = p->f00;
    sum = 0;
    while (n != 0) {
        r = MotionEventBlockReleaseHandlers_1b2420((u8 *)n + 0x10);
        n = n->f00;
        sum += r;
    }
    return sum;
}
