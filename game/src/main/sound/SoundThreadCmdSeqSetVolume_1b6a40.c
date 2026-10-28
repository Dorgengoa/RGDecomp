/* rgp:protos */
#define RGP_SELF_SoundThreadCmdSeqSetVolume_1b6a40 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct S { s32 f00; s32 f04; } S;

/*rgp*/

void SoundThreadCmdSeqSetVolume_1b6a40(S *p)
{
    SoundIopSendCmdG2S2_165c70(p->f00, 0x30, 0, p->f04);
}
