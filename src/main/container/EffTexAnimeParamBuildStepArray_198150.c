#include "types.h"
#pragma opt_common_subs off

extern s32 MemStackNew_14e1b0(s32);

void EffTexAnimeParamBuildStepArray_198150(void *arg0) {
    s32 temp_2;
    s32 var_17;
    s32 var_6;
    void *var_3;
    void *var_5;

    var_17 = 0;
    var_3 = *(void **)((u8 *)arg0 + 0x18);
    while (var_3 != NULL) {
        var_3 = *(void **)((u8 *)var_3 + 0x18);
        var_17 += 1;
    }
    if (var_17 != 0) {
        temp_2 = MemStackNew_14e1b0(var_17 * 4);
        *(s32 *)((u8 *)arg0 + 0x24) = temp_2;
        if (temp_2 != 0) {
            *(s32 *)((u8 *)arg0 + 0x20) = var_17;
            var_5 = *(void **)((u8 *)arg0 + 0x18);
            var_6 = 0;
            while (var_5 != NULL) {
                *(void **)(*(u8 **)((u8 *)arg0 + 0x24) + (var_6 * 4)) = var_5;
                var_6 += 1;
                var_5 = *(void **)((u8 *)var_5 + 0x18);
            }
        }
    }
}
