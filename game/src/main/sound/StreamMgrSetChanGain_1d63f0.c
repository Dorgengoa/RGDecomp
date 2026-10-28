/* rgp:protos */
#define RGP_SELF_StreamMgrSetChanGain_1d63f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Head of a 9-member clone group (64 B each).  Members differ in ONE token,
   the worker called.  A bounds-checked dispatch into a 4-entry array of
   224-byte records: retail strength-reduces the stride to
   `sll 3 / subu / sll 5`, i.e. ((2^3 - 1) * 2^5) = 224. */

/*rgp*/

void StreamMgrSetChanGain_1d63f0(void *base, s32 i, float rgp_f0)
{
    if (i < 0 || i >= 4) {
        return;
    }
    StreamChanSetGain_1d7000((u8 *)base + i * 224, (float)rgp_f0);
}
