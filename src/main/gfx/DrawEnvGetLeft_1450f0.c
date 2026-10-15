#include "types.h"

typedef struct A1450f0 {
    u8 pad00[0x4];
    s32 m04;
    u8 pad0C[0x4];
    s32 m0C;
} A1450f0;

typedef struct B1450f0 {
    u8 pad000[0x270];
    A1450f0 *m270;
} B1450f0;

s32 DrawEnvGetLeft_1450f0(B1450f0 *p)
{
    A1450f0 *q = p->m270;

    return q->m0C - q->m04 / 2;
}
