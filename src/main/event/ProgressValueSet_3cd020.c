#include "types.h"
#pragma opt_common_subs off
s32 ProgressSlotSet_3cd130(void *, s32, s32, s32, s32, s32, s32);
s32 GroupTableFindSubEntry_422880(s32, s16, s16, s16);
void *GroupTableFindEntry_422950(s32, s16, s16);

s32 ProgressValueSet_3cd020(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 temp_16;
    void *temp_2;
    void *temp_2_2;

    temp_2 = (void *)((*(s32 *)((u8 *)(arg0) + 0x4)));
    if (temp_2 == NULL) {
        return 0;
    }
    temp_2_2 = GroupTableFindEntry_422950((*(s32 *)((u8 *)(temp_2) + 0x8)), arg1, arg2);
    if (temp_2_2 == NULL) {
        return 0;
    }
    temp_16 = *(s16 *)((u8 *)temp_2_2 + 0x8);
    if (temp_16 < 0 || temp_16 >= 0xF) {
        return 0;
    }
    if (GroupTableFindSubEntry_422880((*(s32 *)((u8 *)((*(void **)((u8 *)(arg0) + 0x4))) + 0x8)), arg1, arg2, arg3) != 0) {
        return ProgressSlotSet_3cd130(arg0, arg1, arg2, temp_16, arg3, arg4, arg5);
    }
    return 0;
}
