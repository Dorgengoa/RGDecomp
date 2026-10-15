#include "types.h"

typedef struct P { u8 pad0[0x54]; s16 f54[5][2]; } P;

void CharaSetStat54_3b7d60(P *p, s32 a, s16 v, s32 b)
{
    if (b >= 0 && b < 2 && a >= 0 && a < 5) {
        p->f54[a][b] = v;
    }
}
