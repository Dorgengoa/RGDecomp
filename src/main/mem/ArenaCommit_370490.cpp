#undef NULL
#define NULL 0
#pragma opt_common_subs off
#include "types.h"
#undef NULL
#define NULL 0
extern "C" {

extern s32 MemStackAllocQw_14d950(void *arg0, s32 arg1);

bool ArenaCommit_370490(void *arg0)
{
    s32 temp_5;
    bool var_16;
    s32 var_2;
    void *temp_3;
    void *temp_4;

    temp_4 = *(void **)((u8 *)arg0 + 0x0);
    if (temp_4 == NULL) {
        return 0;
    }
    var_16 = 1;
    if (*(s32 *)((u8 *)arg0 + 0x8) > 0) {
        temp_5 = *(s32 *)((u8 *)arg0 + 0x8);
        var_2 = temp_5 / 16;
        if (MemStackAllocQw_14d950(temp_4, var_2 + ((temp_5 % 16) > 0)) == 0) {
            var_16 = 0;
        }
    }
    temp_3 = *(void **)((u8 *)arg0 + 0x0);
    *(s32 *)((u8 *)arg0 + 0x4) = *(s32 *)((u8 *)temp_3 + 0x28) + (*(s32 *)((u8 *)temp_3 + 0x2C) * 0x10);
    *(s32 *)((u8 *)arg0 + 0x8) = 0;
    return var_16;
    return 0;
}
}
