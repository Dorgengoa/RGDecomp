#include "types.h"

typedef struct P { u8 pad0[0x18]; s16 f18; } P;

void OptionsSetVoiceVolume_3d60a0(P *p, s16 v)
{
    p->f18 = v;
    if (v < 0) p->f18 = 0;
    else if (v > 10) p->f18 = 10;
}
