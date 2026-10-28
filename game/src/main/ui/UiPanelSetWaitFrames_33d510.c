/* rgp:protos */
#define RGP_SELF_UiPanelSetWaitFrames_33d510 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct P { u8 pad[0x60]; s32 f60; } P;

void UiPanelSetWaitFrames_33d510(P *p, s32 v)
{
    if (v < 0) v = 0x3C;
    p->f60 = v;
}
