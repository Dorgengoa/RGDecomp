/* rgp:protos */
#define RGP_SELF_StreamMgrPauseChan_1d6630 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Member of the 9-clone group headed by StreamMgrSetChanGain_1d63f0 (64 B each).
   This member differs from the head in the worker called.  The reading is
   written up in StreamMgrSetChanGain_1d63f0.c. */

/*rgp*/

void StreamMgrPauseChan_1d6630(void *base, s32 i)
{
    if (i < 0 || i >= 4) {
        return;
    }
    StreamChanPause_1d6c00((u8 *)base + i * 224);
}
