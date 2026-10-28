/* rgp:protos */
#define RGP_SELF_InsectBattleIsPhaseSeqDone_319610 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

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
