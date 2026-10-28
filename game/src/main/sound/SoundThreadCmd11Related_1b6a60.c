/* rgp:protos */
#define RGP_SELF_SoundThreadCmd11Related_1b6a60 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct S { s32 f00; s32 f04; } S;

/*rgp*/

void SoundThreadCmd11Related_1b6a60(S *p)
{
    SoundIopSendCmdG2S2_165c70(p->f00, 0x32, 0, p->f04);
}
