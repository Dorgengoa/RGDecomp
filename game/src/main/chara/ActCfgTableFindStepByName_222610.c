/* rgp:protos */
#define RGP_SELF_ActCfgTableFindStepByName_222610 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

s8 **ActCfgTableFindStepByName_222610(s32 pad0, s32 pad1, s8 *arg2) {
    s8 *temp_4;
    s8 **var_18;
    s32 var_17;
    void *temp_2;
    s8 **ret;

    temp_2 = ActCfgTableFindActionByName_223d20((void *)pad0, (void *)pad1);
    if (temp_2 == NULL) {
        return NULL;
    }
    if (arg2 == NULL) {
        ret = NULL;
    } else {
        var_18 = *(s8 ***)((u8 *)temp_2 + 0x2C);
        if (var_18 == NULL) {
            ret = NULL;
        } else {
            var_17 = 0;
            while (var_17 < *(s16 *)((u8 *)temp_2 + 0x30)) {
                temp_4 = *var_18;
                if (*arg2 == *temp_4 && StrNotEqual_1f5300(temp_4 + 1, arg2 + 1) == 0) {
                    ret = var_18;
                    goto out;
                }
                var_17++;
                var_18 = (s8 **)((u8 *)var_18 + 0x44);
            }
            ret = NULL;
        }
    }
out:
    return ret;
}
