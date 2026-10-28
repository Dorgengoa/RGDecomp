/* rgp:protos */
#define RGP_SELF_ArenaSync_370540 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_common_subs off

/*rgp*/

s32 ArenaSync_370540(void *arg0, s32 arg1)
{
    s32 temp_5;
    s32 var_2;
    s32 flag;
    void *temp_2;
    void *temp_4;

    temp_4 = *(void **)((u8 *)arg0 + 0);
    if (temp_4 == NULL) {
        return 0;
    }
    if (arg1 != 0) {
        if (temp_4 != NULL) {
            if (*(s32 *)((u8 *)arg0 + 8) > 0) {
                temp_5 = *(s32 *)((u8 *)arg0 + 8);
                flag = (temp_5 % 16) > 0;
                var_2 = temp_5 >> 4;
                if (temp_5 < 0) {
                    var_2 = (temp_5 + 0xF) >> 4;
                }
                MemStackAllocQw_14d950(temp_4, var_2 + flag);
            }
            temp_2 = *(void **)((u8 *)arg0 + 0);
            *(s32 *)((u8 *)arg0 + 4) = *(s32 *)((u8 *)temp_2 + 0x28) + (*(s32 *)((u8 *)temp_2 + 0x2C) * 0x10);
            *(s32 *)((u8 *)arg0 + 8) = 0;
        }
    } else if (temp_4 != NULL) {
        *(s32 *)((u8 *)arg0 + 4) = *(s32 *)((u8 *)temp_4 + 0x28) + (*(s32 *)((u8 *)temp_4 + 0x2C) * 0x10);
        *(s32 *)((u8 *)arg0 + 8) = 0;
    }
    return 1;
}
