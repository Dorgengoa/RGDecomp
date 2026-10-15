#include "types.h"

s32 GetLoadedOverlayId_1c3200(void);
s32 InsectBattleGet_31a8d0(void);
s32 func_50DF90(s32 a, s32 b);

s32 InsectBattleBuildNpcPath_3195b0(s32 arg0)
{
    s32 val;

    if (GetLoadedOverlayId_1c3200() != 5) {
        return 0;
    }
    val = InsectBattleGet_31a8d0();
    if (val != 0) {
        return func_50DF90(val, arg0);
    }
    return 0;
}
