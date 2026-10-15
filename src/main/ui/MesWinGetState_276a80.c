#include "types.h"

extern s32 MesWinGetShownEnd_271680(s32 arg0);
extern s32 MesWinIsPageWait_2721f0(s32 arg0);
extern s32 MesWinGetCharCount_274c70(s32 arg0);
extern f32 MesWinGetOpenRate_277540(s32 arg0);

s32 MesWinGetState_276a80(s32 arg0)
{
    s32 temp_16;

    if (!(!(MesWinGetOpenRate_277540(arg0) <= 0.0f))) {
        return 0;
    }
    if ((0.0f < MesWinGetOpenRate_277540(arg0)) && (MesWinGetOpenRate_277540(arg0) < 1.0f)) {
        return 1;
    }
    temp_16 = MesWinGetCharCount_274c70(arg0);
    if (temp_16 <= MesWinGetShownEnd_271680(arg0)) {
        return 3;
    }
    return MesWinIsPageWait_2721f0(arg0) != 0 ? 5 : 2;
    return 0;
}
