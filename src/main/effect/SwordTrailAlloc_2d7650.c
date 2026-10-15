#include "types.h"

struct T2D7650 { u8 pad000[0x4]; void *f04; s32 f08; };

extern void *MemStackNew_14e1b0(s32 n, void *a);

void SwordTrailAlloc_2d7650(struct T2D7650 *p, void *a, s32 n)
{
    void *r;

    if (a == 0) return;
    r = MemStackNew_14e1b0(n * 48, a);
    p->f04 = r;
    if (r == 0) return;
    p->f08 = n;
}
