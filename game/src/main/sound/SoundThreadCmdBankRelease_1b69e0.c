/* rgp:protos */
#define RGP_SELF_SoundThreadCmdBankRelease_1b69e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

void SoundThreadCmdBankRelease_1b69e0(s32 *p0)
{
    SoundIopSendCmdG1S1_165900(3, *p0);
}
