#include "types.h"

struct T140830 { u8 pad000[0x3BB4]; s32 f3BB4; s32 *f3BB8; };

extern s32 DrawListEmitBucket_1405a0(struct T140830 *p, s32 i);

s32 DrawListEmitBucketById_140830(struct T140830 *p, s32 i)
{
    s32 *tab;

    if (i < 0 || i >= p->f3BB4) return 0;
    tab = p->f3BB8;
    if (tab != 0) {
        i = tab[i];
    }
    if (i < 0) return 0;
    return DrawListEmitBucket_1405a0(p, i);
}
