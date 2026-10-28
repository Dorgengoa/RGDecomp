/* rgp:protos */
#define RGP_SELF_StreamMgrStartChan_1d66f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

void StreamMgrStartChan_1d66f0(u8 *base, s32 i, void *a, void *b)
{
    if (i < 0 || i >= 4) return;
    StreamChanStart_1d6d00(base + i * 224, a, b);
}
