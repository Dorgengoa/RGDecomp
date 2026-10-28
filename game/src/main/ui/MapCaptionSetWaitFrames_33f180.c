/* rgp:protos */
#define RGP_SELF_MapCaptionSetWaitFrames_33f180 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct P { u8 pad[0x34]; s32 f34; } P;

void MapCaptionSetWaitFrames_33f180(P *p, s32 v)
{
    if (v < 0) v = 0x3C;
    p->f34 = v;
}
