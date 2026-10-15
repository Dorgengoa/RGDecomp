#include "types.h"

s32 EventVoiceCountPlayingChans_24fae0(u8 *arg0)
{
    u8 *temp_3;
    u8 *temp_3_2;
    s32 *var_5_2;
    s32 var_2;
    s32 var_5;

    var_2 = 0;
    if (*(void **)(arg0 + 4) != NULL) {
        var_5 = -1;
    } else {
        var_5 = 0;
        *(void **)(arg0 + 4) = *(void **)(arg0 + 0);
        *(s32 *)(arg0 + 8) = 0;
    }
    if (var_5 != 0) {
        return 0;
    }
    goto pop;
loop:
    if (*var_5_2 == 2) {
        var_2 += 1;
    }
pop:
    temp_3 = *(u8 **)(arg0 + 4);
    if (temp_3 == NULL) {
        var_5_2 = NULL;
    } else {
        var_5_2 = (s32 *)(temp_3 + 0x10);
        temp_3_2 = *(u8 **)temp_3;
        *(void **)(arg0 + 4) = temp_3_2;
        if (temp_3_2 == NULL) {
            *(s32 *)(arg0 + 8) = 1;
        }
    }
    if (var_5_2 != NULL) {
        goto loop;
    }
    *(void **)(arg0 + 4) = NULL;
    *(s32 *)(arg0 + 8) = 0;
    return var_2;
}
