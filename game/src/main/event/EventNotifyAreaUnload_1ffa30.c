/* rgp:protos */
#define RGP_SELF_EventNotifyAreaUnload_1ffa30 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void EventNotifyAreaUnload_1ffa30(s32 arg0)
{
    s32 temp_2;
    u8 *temp_2_2;

    temp_2 = ((s32)GetEventObjMgr_2d1960());
    EventObjMgrNotifyAreaUnload_2e8720(temp_2, arg0);
    if (arg0 == 0x866) {
        temp_2_2 = (u8 *)GetGameData_1fede0();
        if (temp_2_2 != NULL) {
            StateFlagSet_3ccb70(*(s32 *)(temp_2_2 + 0x10), 0x2C, 0, 0);
            StateFlagSet_3ccb70(*(s32 *)(temp_2_2 + 0x10), 0x2D, 0, 0);
        }
        EvRemoveAreaMonographs_2e9000(temp_2, arg0);
    }
}
