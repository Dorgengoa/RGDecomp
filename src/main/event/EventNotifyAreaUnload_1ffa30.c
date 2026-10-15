#include "types.h"

extern void *GetGameData_1fede0(void);
extern s32 GetEventObjMgr_2d1960(void);
extern void EventObjMgrNotifyAreaUnload_2e8720(s32 arg0, s32 arg1);
extern void EvRemoveAreaMonographs_2e9000(s32 arg0, s32 arg1);
extern void StateFlagSet_3ccb70(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

void EventNotifyAreaUnload_1ffa30(s32 arg0)
{
    s32 temp_2;
    u8 *temp_2_2;

    temp_2 = GetEventObjMgr_2d1960();
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
