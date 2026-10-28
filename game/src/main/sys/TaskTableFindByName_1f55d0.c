/* rgp:protos */
#define RGP_SELF_TaskTableFindByName_1f55d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_common_subs off

/*rgp*/
extern s32 strcmp(s32, s32);

void *TaskTableFindByName_1f55d0(u8 *var_18, s32 arg1)
{
    s32 temp_16;

    if (var_18 == NULL || arg1 == 0) {
        return NULL;
    }
    {
        temp_16 = StrHash16_1f56d0(arg1) & 0xFFFF;
        while (*(s32 *)(var_18 + 0) != 0) {
            if ((*(u16 *)(var_18 + 0xE) == temp_16) && (strcmp(*(s32 *)(var_18 + 0), arg1) == 0)) {
                return var_18;
            }
            var_18 += 0x10;
            continue;
        }
        return NULL;
    }
    return NULL;
    return NULL;
}
