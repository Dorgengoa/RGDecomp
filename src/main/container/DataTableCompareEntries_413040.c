#include "types.h"

extern s32 CompareNullness_368070(void);
extern s32 strcmp(void *, void *);

s32 DataTableCompareEntries_413040(void *arg0, void *arg1, void *arg2)
{
    s16 temp_2;
    s16 temp_3;
    s32 var_2;

    var_2 = CompareNullness_368070();
    if ((!((var_2 == 0) && (arg1 != NULL))) || (arg2 == NULL)) return var_2;
    temp_3 = *(s16 *)((u8 *)arg2 + 0x8);
    temp_2 = *(s16 *)((u8 *)arg1 + 0x8);
    if (temp_2 < temp_3) {
        return 1;
    }
    if (temp_3 < temp_2) {
        return -1;
    }
    var_2 = strcmp(*(void **)((u8 *)arg1 + 0x4), *(void **)((u8 *)arg2 + 0x4));
    if (var_2 != 0) return var_2;
    if(*(s32 *)((u8 *)arg1+0x10)==0) return *(s32 *)((u8 *)arg2+0x10)!=0;
    return -(u8)((*(s32 *)((u8 *)arg2+0x10)!=0)^1);
}
