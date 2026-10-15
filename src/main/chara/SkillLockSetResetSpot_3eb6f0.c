#include "types.h"
extern u8 D_004839A4;
extern void GameDataResetSpotState_3eb690(s32 a, s32 b);
void SkillLockSetResetSpot_3eb6f0(s32 a, s32 b)
{
    if (b != 0) {
        D_004839A4 = 1;
    }
    GameDataResetSpotState_3eb690(a, b);
}
