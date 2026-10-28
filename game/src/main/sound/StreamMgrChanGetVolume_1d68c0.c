/* rgp:protos */
#define RGP_SELF_StreamMgrChanGetVolume_1d68c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

f32 StreamMgrChanGetVolume_1d68c0(u8 *p, s32 i)
{
    if (i < 0 || i >= 4) {
        return 0.0f;
    }
    return StreamChanGetVolume_1d72a0(p + i * 224);
}
