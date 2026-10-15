#include "types.h"

s32 EventCastFindKeyByObjId_24b1d0(u8 *arg0, s32 arg1, s32 arg2, s32 arg3)
{
    s32 var_2;
    s32 var_6;
    s32 var_7;
    u8 *temp_3;
    u8 *temp_3_2;
    u8 *var_6_2;

    var_7 = arg3;
    var_2 = -1;
    if (*(void **)(arg0 + 4) != NULL) {
        var_6 = -1;
    } else {
        var_6 = 0;
        *(void **)(arg0 + 4) = *(void **)(arg0 + 0);
        *(s32 *)(arg0 + 8) = 0;
    }
    if (var_6 != 0) {
        return -1;
    }
    goto pop_7;
loop_7:
    if (arg1 == *(s32 *)(var_6_2 + 0x1C)) {
        var_2 = var_7;
        goto done_7;
    }
pop_7:
    temp_3 = *(u8 **)(arg0 + 4);
    if (temp_3 == NULL) {
        var_6_2 = NULL;
    } else {
        var_7 = *(s32 *)(temp_3 + 0xC);
        var_6_2 = temp_3 + 0x10;
        temp_3_2 = *(u8 **)temp_3;
        *(void **)(arg0 + 4) = temp_3_2;
        if (temp_3_2 == NULL) {
            *(s32 *)(arg0 + 8) = 1;
        }
    }
    if (var_6_2 != NULL) {
        goto loop_7;
    }
done_7:
    *(void **)(arg0 + 4) = NULL;
    *(s32 *)(arg0 + 8) = 0;
    return var_2;
}
