/* rgp:protos */
#define RGP_SELF_SoundThreadCmdSetVolume_1b68e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct S {
    s32 f00;
    s32 f04;
    s32 f08;
    s32 f0C;
    s32 f10;
} S;

/*rgp*/

void SoundThreadCmdSetVolume_1b68e0(S *p)
{
    SoundIopSendCmdG3S2_165f20(p->f00, 0x42, p->f04, p->f08, p->f0C, p->f10);
}
