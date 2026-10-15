#include "types.h"

struct T3045F0 { u8 pad000[0x4]; u8 *f04; s32 f08; };

extern void TargetRefResolve_2e5ed0(u8 *q, s32 z);

s32 EventRefListResolve_3045f0(struct T3045F0 *p)
{
    u8 *q;
    s32 i;

    q = p->f04;
    i = 0;
    while (i < p->f08) {
        TargetRefResolve_2e5ed0(q, 0);
        i++;
        q += 0x30;
    }
    return 1;
}
