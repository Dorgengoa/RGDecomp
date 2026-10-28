/* rgp:protos */
#define RGP_SELF_InsectBattleBuildNpcPath_3195b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

s32 InsectBattleBuildNpcPath_3195b0(s32 arg0)
{
    s32 val;

    if (GetLoadedOverlayId_1c3200() != 5) {
        return 0;
    }
    val = InsectBattleGet_31a8d0();
    if (val != 0) {
        return ((s32)func_50DF90(val, arg0));
    }
    return 0;
}
