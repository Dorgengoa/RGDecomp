#include "types.h"
#pragma optimization_level 3
#pragma opt_common_subs off
#pragma opt_propagation off
extern void MemStackReturnToOwnerMaybe_14dad0(void *);
extern s32 MemStackHeapAlloc_14db10(void *, s32, s32, s32);
extern void MemStackHeapFree_14dcb0(void *, s32);
extern s32 MemStackHeapAllocFront_14dd10(void *, s32);
extern s32 MapAreaHeapInit_1d8c50(void *, s32, s32);
extern void MapDataSetLightRef_1e74a0(void *, s32);
extern s32 MapDataGetHeapSize_1e7ba0();

static inline s32 busy1d8(void *p)
{
    return *(s32 *)((u8 *)p + 0x28) != 0;
}

s32 MapAreaHeapAllocMax_1d8d20(void *arg0) {
    void *temp_4;
    s32 temp_17_2;
    s32 var_18;
    s32 temp_17;
    void *temp_2;

    *(s32 *)((u8 *)arg0 + 0) = 0;
    temp_2 = *(void **)((u8 *)arg0 + 4);
    if (temp_2 == NULL) {
        return -1;
    }
    if (busy1d8(temp_2) != 0) {
        return -1;
    }
    if (!(MapDataGetHeapSize_1e7ba0() <= 0)) {
        var_18 = MapDataGetHeapSize_1e7ba0(arg0);
    } else {
        temp_17_2 = MemStackHeapAlloc_14db10(*(void **)((u8 *)arg0 + 4), 2, 0, 0x40);
        temp_4 = *(void **)((u8 *)arg0 + 4);
        var_18 = (*(s32 *)((u8 *)temp_4 + 0x34) - *(s32 *)((u8 *)temp_4 + 0x2C)) - 4;
        MemStackReturnToOwnerMaybe_14dad0(temp_4);
        MemStackHeapFree_14dcb0(*(void **)((u8 *)arg0 + 4), temp_17_2);
    }
    temp_17 = MemStackHeapAllocFront_14dd10(*(void **)((u8 *)arg0 + 4), var_18);
    MapDataSetLightRef_1e74a0(arg0, -1);
    return MapAreaHeapInit_1d8c50(arg0, temp_17, var_18);
}
