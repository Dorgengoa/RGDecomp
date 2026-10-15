#include "types.h"

#pragma opt_common_subs off

extern u16 *CfgVmStep_42f6e0(void *arg0, s32 arg1);

u16 *CfgVmFindOp_42f650(void *arg0, s32 arg1, s32 arg2) {
    s32 temp_16;
    s32 temp_17;
    u16 *var_2;

loop_1:
    temp_17 = *(s32 *)((u8 *)arg0 + 0x424);
    temp_16 = *(s32 *)((u8 *)arg0 + 0x420);
    var_2 = CfgVmStep_42f6e0(arg0, 0);
    if (var_2 != NULL) {
        if (*var_2 == (arg1 & 0xFFFF)) {
            if (arg2 != 0) {
                *(s32 *)((u8 *)arg0 + 0x424) = temp_17;
                *(s32 *)((u8 *)arg0 + 0x420) = temp_16;
            }
            return var_2;
        }
        goto loop_1;
    }
    return NULL;
}
