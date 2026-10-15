#include "types.h"
#pragma opt_propagation off

typedef struct Item0023b910 {
    f32 unk0;
    f32 unk4;
    u8 pad8[0xC];
} Item0023b910;

extern void ActTimeMoveInit_227970(void *, f32, f32, f32, f32, f32);
extern f32 FrameToRatioClamp_23fb30(s32, f32);
extern f32 ScriptArgGetFloat_23fbc0(s32);
extern s32 ScriptArgGetInt_23fc00(s32);
extern Item0023b910 *D_00481EC0;
extern s32 D_00481EC4;

s32 ActTimeMove_23b910(s32 arg0, s32 arg1) {
    Item0023b910 *temp_18;
    s32 var_17;
    s32 var_16;
    s32 temp_4;
    f32 temp_f23;
    f32 temp_f22;
    f32 temp_f21;
    f32 temp_f20;

    var_17 = arg0;
    if ((arg1 != 5) && (arg1 != 6)) {
        return 0;
    }
    if (D_00481EC0 == 0 || D_00481EC4 >= 0x40) {
        return 1;
    }
    {
        if (arg1 == 6) {
            temp_4 = var_17;
            var_17 += 8;
            var_16 = ScriptArgGetInt_23fc00(temp_4);
        } else {
            var_16 = 0;
        }
        temp_18 = D_00481EC0 + D_00481EC4;
        temp_f23 = ScriptArgGetFloat_23fbc0(var_17);
        temp_f22 = ScriptArgGetFloat_23fbc0(var_17 + 8);
        temp_f21 = ScriptArgGetFloat_23fbc0(var_17 + 0x10);
        temp_f20 = ScriptArgGetFloat_23fbc0(var_17 + 0x18);
        ActTimeMoveInit_227970(temp_18, temp_f23, temp_f22, temp_f21, temp_f20, ScriptArgGetFloat_23fbc0(var_17 + 0x20));
        if (var_16 > 0) {
            temp_18->unk0 = FrameToRatioClamp_23fb30(var_16, temp_18->unk0);
            temp_18->unk4 = FrameToRatioClamp_23fb30(var_16, temp_18->unk4);
        }
        D_00481EC4 += 1;
        return 1;
    }
}
