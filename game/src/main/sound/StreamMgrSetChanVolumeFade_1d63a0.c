/* rgp:protos */
#define RGP_SELF_StreamMgrSetChanVolumeFade_1d63a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

void StreamMgrSetChanVolumeFade_1d63a0(u8 *base, s32 i, void *a, float rgp_f0)
{
    if (i < 0 || i >= 4) return;
    StreamChanSetVolumeFade_1d6f90(base + i * 224, a, (float)rgp_f0);
}
