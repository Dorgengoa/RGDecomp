/* rgp:protos */
#define RGP_SELF_OptionsSetSeVolume_3d60e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct P { u8 pad0[0x16]; s16 f16; } P;

void OptionsSetSeVolume_3d60e0(P *p, s16 v)
{
    p->f16 = v;
    if (v < 0) p->f16 = 0;
    else if (v > 10) p->f16 = 10;
}
