#include "types.h"

extern f32 VecDistance_13d3d0(void *, void *);
extern f32 VecLength_13d4a0(void *);
extern void ScriptSetRefFloat_26a1c0(u8 *, f32);
extern void ScriptArgsToVec4_26a220(void *, u8 *);

s32 EvCmdVecLength_25db40(u8 *arg0, s32 arg1)
{
    u8 sp30[0x10];
    u8 sp20[0x10];
    f32 var_f0;

    switch (arg1) {
    case 4:
        ScriptArgsToVec4_26a220(sp30, arg0);
        arg0 += 0x18;
        var_f0 = VecLength_13d4a0(sp30);
        break;
    case 7:
        ScriptArgsToVec4_26a220(sp30, arg0);
        ScriptArgsToVec4_26a220(sp20, arg0 + 0x18);
        arg0 += 0x30;
        var_f0 = VecDistance_13d3d0(sp30, sp20);
        break;
    default:
        return 0;
    }
    ScriptSetRefFloat_26a1c0(arg0, var_f0);
    return 1;
}
