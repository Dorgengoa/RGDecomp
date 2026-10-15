#include "types.h"

extern s32 MemStackAllocAligned64_14da10(s32, s32);
extern s32 NameTableRegisterImArchive_1594d0(s32, s32, s32, s32, s32);
extern s32 GetDrawCtxNameTable_15de40(void);
extern void MemMoveIfDiff_289c60(s32, s32, s32, s32);
extern void memcpy(void *, const void *, s32);

s32 TexGroupLoadFromBuf_202ad0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6)
{
    s32 temp_2;
    s32 var_5;

    if (arg0 == 0 || arg1 <= 0 || arg2 == 0) {
        return -1;
    }
    var_5 = ((u32) arg1 >> 4) + ((arg1 & 0xF) ? 1 : 0);
    if (arg5 != 0) {
        var_5 = 0xF081;
    }
    temp_2 = MemStackAllocAligned64_14da10(arg2, var_5);
    if (temp_2 == 0) {
        return -1;
    }
    if (arg6 == 0) {
        memcpy((void *) temp_2, (void *) arg0, arg1);
    }
    if (arg5 != 0) {
        MemMoveIfDiff_289c60(temp_2, arg1, temp_2, 0xF081);
    }
    return NameTableRegisterImArchive_1594d0(GetDrawCtxNameTable_15de40(), temp_2, arg3, arg4, 0);
}
