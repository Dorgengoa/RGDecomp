/* rgp:protos */
#define RGP_SELF_StreamMgrChanGetStatus_1d65f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

s32 StreamMgrChanGetStatus_1d65f0(u8 *base, s32 i)
{
    if (i < 0) goto fail;
    if (i < 4) goto ok;
fail:
    return -2;
ok:
    return StreamChanGetStatus_1d6bb0(base + i * 224);
}
