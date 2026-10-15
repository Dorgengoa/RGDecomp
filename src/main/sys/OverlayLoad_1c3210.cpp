#include "types.h"

extern s32 D_0044AF90[][7];
extern s32 D_0047D134[];
extern s32 D_0047E254;
extern s32 D_0048155C;

extern "C" {
extern s32 OverlayLoadFile_100410(s32, s32);
extern void OverlayCdSeek_1c32b0(void);

s32 OverlayLoad_1c3210(s32 arg0)
{
    s32 temp_17;

    temp_17 = D_0047D134[0];
    OverlayCdSeek_1c32b0();
    if (arg0 < 0 || arg0 >= 7) {
        return 1;
    }
    while (!OverlayLoadFile_100410(D_0044AF90[D_0048155C][arg0], temp_17)) {
    }
    D_0047E254 = arg0;
    return 0;
}
}
