#include "types.h"
typedef struct A1B1DB0 { s32 m00; u8 pad004[0xC]; s32 m10; } A1B1DB0;
typedef struct P1B1DB0 { u8 pad000[0x14]; A1B1DB0 *m14; } P1B1DB0;
s32 ListIterNextItem_1b1db0(P1B1DB0 *p)
{
    A1B1DB0 *q;
    s32      r;

    q = p->m14;
    if (q == 0) return 0;
    r = q->m10;
    p->m14 = (A1B1DB0 *)q->m00;
    return r;
}
