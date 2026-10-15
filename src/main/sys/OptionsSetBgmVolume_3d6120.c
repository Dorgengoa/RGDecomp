#include "types.h"

typedef struct P { u8 pad0[0x14]; s16 f14; } P;

void OptionsSetBgmVolume_3d6120(P *p, s16 v)
{
    p->f14 = v;
    if (v < 0) p->f14 = 0;
    else if (v > 10) p->f14 = 10;
}
