#include "types.h"

extern void SoundPlayScaledVolume_1b9520(s32 arg0, s32 arg1, f32 arg3, s32 arg2);
extern f32 ScriptArgGetFloat_302cf0(s32 arg0);
extern s32 ScriptArgGetInt_302d70(s32 arg0);

s32 EvScriptSoundSlotPlay_302600(s32 arg0, s32 arg1, s32 arg2)
{
    f32 var_f20;
    s32 var_19;

    if (arg2 > 0) goto A;
    return 1;
A:
    if (arg0 != -1) goto B;
    return 1;
B:
    if (arg2 >= 3) {
        var_19 = (ScriptArgGetInt_302d70(arg1 + 0xA) % 31) + 1;
    } else {
        var_19 = 0;
    }
    if (arg2 >= 2) {
        var_f20 = ScriptArgGetFloat_302cf0(arg1 + 5);
    } else {
        var_f20 = 1.0f;
    }
    SoundPlayScaledVolume_1b9520(arg0, ScriptArgGetInt_302d70(arg1), var_f20, var_19);
    return 1;
}
