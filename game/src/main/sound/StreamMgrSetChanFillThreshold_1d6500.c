/* rgp:protos */
#define RGP_SELF_StreamMgrSetChanFillThreshold_1d6500 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Member of the 9-clone group headed by StreamMgrSetChanGain_1d63f0 (64 B each).
   This member differs from the head in the worker called.  The reading is
   written up in StreamMgrSetChanGain_1d63f0.c. */

/*rgp*/

void StreamMgrSetChanFillThreshold_1d6500(void *base, s32 i, float rgp_f0)
{
    if (i < 0 || i >= 4) {
        return;
    }
    StreamChanSetFillThreshold_1d6b10((u8 *)base + i * 224, (float)rgp_f0);
}
