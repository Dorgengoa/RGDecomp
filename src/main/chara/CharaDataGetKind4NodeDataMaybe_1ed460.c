#include "types.h"
#pragma opt_propagation off

extern s32 CharaDataCollectNodes_1ed670(s32, s32, s32, s32, void *, s32);
extern void *CharaDataFindNode_1ed6d0(s32 xa0, s32 xa1, s32, s32);
extern s32 CharaDataNodeGetData_1eeb00(void *, s32, s32);

s32 CharaDataGetKind4NodeDataMaybe_1ed460(s32 pdA, s32 pdB, s32 arg2, s32 arg3, s32 arg4)
{
    u8 *sp40[0x80];
    s32 temp_2_2;
    s32 var_2;
    s32 var_5;
    u8 *temp_2;
    u8 *temp_4;
    u8 **pp;

    if (arg2 == -1) {
        temp_2 = (u8 *)CharaDataFindNode_1ed6d0((s32)pdA, (s32)pdB, 0, 4);
        if (temp_2 == NULL) {
            var_2 = 0;
        } else {
            var_2 = CharaDataNodeGetData_1eeb00(temp_2, arg3, arg4);
        }
        return var_2;
    }
    temp_2_2 = CharaDataCollectNodes_1ed670(pdA, pdB, 0, 4, sp40, 0x80);
    var_5 = 0;
    while (var_5 < temp_2_2) {
        pp = &sp40[var_5];
        temp_4 = *pp;
        if ((temp_4 != NULL) && (arg2 == *(s16 *)(temp_4 + 0xA))) {
            return CharaDataNodeGetData_1eeb00(temp_4, 0, 0);
        }
        var_5 += 1;
        continue;
    }
    return 0;
}
