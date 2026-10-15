#include "types.h"

s32 GetLoadedOverlayId_1c3200(void);
s32 InsectBattleGet_31a8d0(void);
s32 func_4F45F0(s32 a);

s32 InsectBattleIsPhaseSeqDone_319610(void)
{
    s32 val;

    if (GetLoadedOverlayId_1c3200() != 5) {
        return 1;
    }
    val = InsectBattleGet_31a8d0();
    if (val != 0) {
        return func_4F45F0(val);
    }
    return 0;
}
