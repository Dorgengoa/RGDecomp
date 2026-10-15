#include "types.h"

extern s32 CompareNullness_368070(void);

s32 DataTableCompareEntries_41eb00(void *arg0, void *arg1, void *arg2)
{
    s16 temp_2;
    s16 temp_2_2;
    s16 temp_3;
    s16 temp_3_2;
    s16 temp_3_3;
    s32 var_2;

    var_2 = CompareNullness_368070();
    if ((!((var_2 == 0) && (arg1 != NULL))) || (arg2 == NULL)) return var_2;
    temp_3 = *(s16 *)((u8 *)arg2 + 2);
    temp_2 = *(s16 *)((u8 *)arg1 + 2);
    if (temp_2 < temp_3) {
        return -1;
    }
    if (temp_3 < temp_2) {
        return 1;
    }
    temp_3_2 = *(s16 *)((u8 *)arg1 + 4);
    if ((temp_3_2 >= 0) && (*(s16 *)((u8 *)arg2 + 4) < 0)) {
        return -1;
    }
    if ((temp_3_2 < 0) && (*(s16 *)((u8 *)arg2 + 4) >= 0)) {
        return 1;
    }
    temp_3_3 = *(s16 *)((u8 *)arg2 + 0);
    temp_2_2 = *(s16 *)((u8 *)arg1 + 0);
    if (temp_2_2 < temp_3_3) {
        return -1;
    }
    var_2 = temp_3_3 < temp_2_2;
    return var_2;
    return var_2;
}
