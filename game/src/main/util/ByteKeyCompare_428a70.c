/* rgp:protos */
#define RGP_SELF_ByteKeyCompare_428a70 1
#include "port/game_protos.h"
#line 1
#include "types.h"

s32 ByteKeyCompare_428a70(s32 arg0, u8 *arg1, s32 arg2, u8 *arg3) {
    s32 var_8;
    s32 var_9;
    u8 *var_5;
    u8 *var_7;
    u8 temp_2;
    u8 temp_3;

    var_5 = arg1;
    var_7 = arg3;
    if (var_5 == NULL) {
        return -(var_7 != NULL);
    }
    if (var_7 == NULL) {
        return 1;
    }
    if (((arg0 <= 0) || (!((arg0 < 8) && (arg2 > 0)))) || (arg2 >= 8)) return 1;
    if (arg0 < arg2) {
        var_8 = arg0;
    } else {
        var_8 = arg2;
    }
    if ((var_8 < 0) || (var_8 >= 8)) {
        return 1;
    }
    for (var_9 = 0; var_9 < var_8; var_9++) {
        temp_3 = *var_5;
        temp_2 = *var_7;
        var_5 += 1;
        var_7 += 1;
        if ((s32) temp_3 < (s32) temp_2) {
            return -1;
        }
        if ((s32) temp_2 < (s32) temp_3) {
            return 1;
        }
    }
if (arg0 >= arg2) goto ge; return -1; ge: return arg2 < arg0;
}
