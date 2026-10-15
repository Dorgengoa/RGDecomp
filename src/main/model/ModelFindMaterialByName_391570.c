#include "types.h"

extern s32 ArrayGetCountIndirect_1527c0(s32 arg0);
extern void *ArrayGetCheckedIndirect_1527e0(s32 arg0, s32 arg1);
extern s32 StrNotEqual_1f5300(s32 arg0, s32 arg1);

void *ModelFindMaterialByName_391570(s32 arg0, s32 arg1)
{
    s32 temp_16;
    s32 var_18;
    void *temp_2;

    if ((arg0 == 0) || (arg1 == 0)) return NULL;
    temp_16 = ArrayGetCountIndirect_1527c0(arg0 + 0x120);
    var_18 = 0;
    while (var_18 < temp_16) {
        temp_2 = ArrayGetCheckedIndirect_1527e0(arg0 + 0x120, var_18);
        if ((temp_2 != NULL) && (StrNotEqual_1f5300(*(s32 *)((u8 *)temp_2 + 0x10), arg1) == 0)) {
            return temp_2;
        }
        var_18 += 1;
    }
    return NULL;
}
