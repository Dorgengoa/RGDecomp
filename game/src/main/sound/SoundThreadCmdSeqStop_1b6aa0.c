/* rgp:protos */
#define RGP_SELF_SoundThreadCmdSeqStop_1b6aa0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

s32 SoundThreadCmdSeqStop_1b6aa0(void **p)
{
    return SoundIopSendCmdG2S2_165c70(*p, 0x2, 0);
}
