#include "types.h"

extern void EventVolumeRecSetPoint_2e4d30(void *, f32, f32, f32);
extern f32 ScriptArgGetFloat_301a20(s32);
extern s32 D_00482830;
extern u8 D_004E66D0[];

s32 EvScriptCmdVolumeSetPoint_301530(s32 arg0, s32 arg1) {
    f32 temp_f20;
    f32 temp_f21;

    if (arg1 != 3) {
        return 0;
    }
    if (D_00482830 == 0) {
        return 1;
    }
    temp_f21 = ScriptArgGetFloat_301a20(arg0);
    temp_f20 = ScriptArgGetFloat_301a20(arg0 + 8);
    EventVolumeRecSetPoint_2e4d30(D_004E66D0, temp_f21, temp_f20, ScriptArgGetFloat_301a20(arg0 + 0x10));
    return 1;
}
