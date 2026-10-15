#include "types.h"

typedef struct A1450c0 {
    u8 pad00[0x8];
    s32 m08;
    u8 pad0C[0x4];
    s32 m10;
} A1450c0;

typedef struct B1450c0 {
    u8 pad000[0x270];
    A1450c0 *m270;
} B1450c0;

s32 DrawEnvGetTop_1450c0(B1450c0 *p)
{
    A1450c0 *q = p->m270;

    return q->m10 - q->m08 / 2;
}
