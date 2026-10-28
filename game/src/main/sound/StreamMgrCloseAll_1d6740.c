/* rgp:protos */
#define RGP_SELF_StreamMgrCloseAll_1d6740 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

void StreamMgrCloseAll_1d6740(void *p)
{
    s32 i;

    SoundStreamSetMasterVolumeThunkMaybe_1bc6f0(0.0f);
    SoundStreamSlotThreadResumeThunk_1bd660();
    for (i = 0; i < 4; i++) {
        StreamMgrCloseChan_1d67a0(p, i);
    }
}
