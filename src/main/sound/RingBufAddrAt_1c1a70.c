#include "types.h"
typedef struct P1C1A70 { u8 pad000[0x4]; s32 m04; u32 m08; } P1C1A70;
s32 RingBufAddrAt_1c1a70(P1C1A70 *p, u32 i)
{
    s32 r;

    if (i >= p->m08) {
        r = 0;
    } else {
        r = p->m04 + i;
    }
    return r;
}
