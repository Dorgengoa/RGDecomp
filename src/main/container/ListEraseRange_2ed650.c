#include "types.h"
#pragma opt_common_subs off

extern void OperatorDelete_100840(void **);

void ListEraseRange_2ed650(void ***arg0, s32 *arg1, void ***__restrict arg2, void ***__restrict arg3) {
    void **temp_3;
    void **temp_4_2;
    void **temp_6;
    void *temp_5;

    temp_3 = *(void **volatile *)arg3;
    temp_6 = *(void **volatile *)arg2;
    if (temp_6 == temp_3) {
        *arg0 = temp_3;
        return;
    }
    temp_5 = *temp_3;
    *(void ***)((u8 *)*temp_6 + 4) = *(void ***)((u8 *)temp_5 + 4);
    *(void **)*(void **)((u8 *)temp_5 + 4) = *temp_6;
    while (temp_3 = *arg3, *arg2 != temp_3) {
        temp_4_2 = *arg2;
        *arg2 = *(void ***)((u8 *)temp_4_2 + 4);
        OperatorDelete_100840(temp_4_2);
        *arg1 -= 1;
    }
    *arg0 = temp_3;
}
