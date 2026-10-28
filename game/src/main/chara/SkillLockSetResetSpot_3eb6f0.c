/* rgp:protos */
#define RGP_SELF_SkillLockSetResetSpot_3eb6f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
extern u8 D_004839A4;
/*rgp*/
void SkillLockSetResetSpot_3eb6f0(s32 a, s32 b)
{
    if (b != 0) {
        D_004839A4 = 1;
    }
    GameDataResetSpotState_3eb690(a);
}
