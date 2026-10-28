/* rgp:protos */
#define RGP_SELF_SoundThreadCmdPause_1b6ad0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

s32 SoundThreadCmdPause_1b6ad0(void **p)
{
    return SoundIopSendCmdG2S2_165c70(*p, 0x3, 0);
}
