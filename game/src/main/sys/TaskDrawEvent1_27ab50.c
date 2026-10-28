/* rgp:protos */
#define RGP_SELF_TaskDrawEvent1_27ab50 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

void TaskDrawEvent1_27ab50(void)
{
    if (SysModeMsgIsKeyCapWarpStartMaybe_27bc40() == 0) {
        MenuWinUpdateAll_26b390();
    }
}
