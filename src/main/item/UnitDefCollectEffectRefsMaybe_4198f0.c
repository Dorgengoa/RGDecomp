#include "types.h"

extern s32 AbilityDataCollectEffectRefsMaybe_3f4290(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
extern s32 BtlEffSetRowCollectRefsMaybe_3f9da0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

s32 UnitDefCollectEffectRefsMaybe_4198f0(void *arg0, void *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5)
{
    s32 temp_18;
    s32 *var_17;
    s32 temp_4;
    s32 var_16;
    s32 var_2;
    void *temp_2;

    if (arg1 == NULL) {
        return arg5;
    }
    temp_2 = *(void **)((u8 *)arg0 + 4);
    if (temp_2 == NULL) {
        return arg5;
    }
    temp_4 = *(s32 *)((u8 *)temp_2 + 0x48);
    if (temp_4 == 0) {
        return arg5;
    }
    temp_18 = *(s32 *)((u8 *)temp_2 + 0x44);
    if (temp_4 == 0) {
        return arg5;
    }
    var_2 = BtlEffSetRowCollectRefsMaybe_3f9da0(temp_4, *(s32 *)((u8 *)arg1 + 0x74), arg3, arg4, arg5);
    if (arg2 != 0) {
        var_17 = *(s32 **)((u8 *)arg1 + 0x7C);
        for (var_16 = 0; var_16 < *(s16 *)((u8 *)arg1 + 0x78); var_16++, var_17++) {
            var_2 = AbilityDataCollectEffectRefsMaybe_3f4290(temp_18, *var_17, arg3, arg4, var_2);
        }
    }
    return var_2;
}
