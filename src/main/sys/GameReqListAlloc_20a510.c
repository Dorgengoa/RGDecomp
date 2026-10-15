#include "types.h"

struct T20A510 { void *f00; u8 pad004[0x2]; s16 f06; };

extern void *MemStackNew_14e1b0(s32 n, void *a);

void GameReqListAlloc_20a510(struct T20A510 *p, s32 n, void *a)
{
    void *r;

    if (a == 0) return;
    r = MemStackNew_14e1b0(n * 20, a);
    p->f00 = r;
    if (r == 0) return;
    p->f06 = (s16)n;
}
