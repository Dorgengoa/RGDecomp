#include "types.h"
typedef struct T2C6BE0 { u8 pad000[0x13C]; s16 m13C; } T2C6BE0;
typedef struct H2C6BE0 { T2C6BE0 *p; s32 pad[3]; } H2C6BE0;
extern H2C6BE0 D_004DB930;
s32 AiCmdClearTarget_2c6be0(void)
{
    T2C6BE0 *q;

    q = D_004DB930.p;
    if (q == 0) return 0;
    q->m13C = -1;
    return 1;
}
