#include "types.h"

typedef struct T003da040 {
    u8 pad0[0xE08];
    s16 fieldE08;
} T003da040;

void *OpStackPop_3da040(T003da040 *arg0)
{
    s16 temp_3;
    s32 temp_2;
    void *var_2;

    temp_3 = arg0->fieldE08;
    var_2 = NULL;
    if (temp_3 > 0) {
        temp_2 = temp_3 - 1;
        arg0->fieldE08 = (s16)temp_2;
        temp_2 = (s16)temp_2;
        var_2 = (u8 *)arg0 + 8 + (temp_2 * 0x38);
    }
    return var_2;
}
