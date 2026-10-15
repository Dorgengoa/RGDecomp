#pragma opt_propagation off
#include "types.h"

extern s32 DebugMenuWidgetGetChild_209d90(void *, s32);
extern s32 DebugMenuWidgetIsDisabledMaybe_209e80(s32);

typedef struct {
    u8 pad0[0x18];
    s32 unk18;
    s16 unk1C;
} T209c40_arg0;

s32 DebugMenuWidgetCursorNext_209c40(T209c40_arg0 *arg0, s32 arg1) {
    s16 temp_3;
    s32 var_16;
    s32 var_18;

    var_16 = arg1;
    if (arg0->unk18 == 0) {
        return -1;
    }
    temp_3 = arg0->unk1C;
    if (var_16 >= temp_3) {
        var_16 = temp_3 - 1;
    }
    var_18 = var_16;
    do {
        var_18 += 1;
        if (var_18 >= arg0->unk1C) {
            var_18 = 0;
        }
    } while ((DebugMenuWidgetIsDisabledMaybe_209e80(DebugMenuWidgetGetChild_209d90(arg0, var_18)) != 0) && (var_18 != var_16));
    return var_18;
}
