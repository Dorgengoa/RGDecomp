#include "types.h"

extern f32 StreamChanGetVolume_1d72a0(void *);

f32 StreamMgrChanGetVolume_1d68c0(u8 *p, s32 i)
{
    if (i < 0 || i >= 4) {
        return 0.0f;
    }
    return StreamChanGetVolume_1d72a0(p + i * 224);
}
