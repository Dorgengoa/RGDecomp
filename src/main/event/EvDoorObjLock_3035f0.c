#include "types.h"

extern void MapSetDataFlag2ById_1e4da0(s32 arg0, s16 arg1, s32 arg2);
extern s32 GetMapMgr_201a90(void);
extern void TargetRefSetAreaFlag2_2e6790(void *arg0);
extern s32 EvDoorObjGetState_304040(void *arg0);

void EvDoorObjLock_3035f0(void *arg0)
{
    s32 t;
    s32 f;
    s32 i;

    f = *(s32 *)((u8 *)arg0 + 0xD0);
    if ((((f & 0x80000000) != 0) ^ 1) && (f & 0x02000000) && (EvDoorObjGetState_304040(arg0) != 0)) {
        TargetRefSetAreaFlag2_2e6790((u8 *)arg0 + 0xA0);
        t = GetMapMgr_201a90();
        for (i = 0; i < *(s16 *)((u8 *)arg0 + 0x18A); i++) {
            MapSetDataFlag2ById_1e4da0(t, *(s16 *)((u8 *)(*(s32 *)((u8 *)arg0 + 0x184)) + i * 2), 1);
        }
    }
}
