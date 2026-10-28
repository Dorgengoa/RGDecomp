/* rgp:protos */
#define RGP_SELF_SoundThreadCmdKeyOff_1b6970 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

void SoundThreadCmdKeyOff_1b6970(s32 *p)
{
    SoundIopSendCmdG3S2_165f20(p[0], 0x13, p[1], p[2], p[3], p[4], p[5], 0, 0);
}
