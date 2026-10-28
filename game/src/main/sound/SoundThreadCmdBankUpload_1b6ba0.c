/* rgp:protos */
#define RGP_SELF_SoundThreadCmdBankUpload_1b6ba0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct S1B6BA0 { s32 f00; s32 f04; s32 f08; s32 f0C; s32 f10; };

/*rgp*/

s32 SoundThreadCmdBankUpload_1b6ba0(struct S1B6BA0 *p)
{
    return SoundIopSendCmdG1S0_165828(3, p->f00, p->f04, p->f08, p->f0C, p->f10);
}
