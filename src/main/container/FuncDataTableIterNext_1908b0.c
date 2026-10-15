#include "types.h"
typedef struct A1908B0 { s32 m00; u8 pad004[0xC]; s32 m10; } A1908B0;
typedef struct P1908B0 { u8 pad000[0x8]; A1908B0 *m08; } P1908B0;
s32 FuncDataTableIterNext_1908b0(P1908B0 *p)
{
    A1908B0 *q;

    q = p->m08;
    if (q == 0) return 0;
    p->m08 = (A1908B0 *)q->m00;
    return q->m10;
}
