/* PARK (round 1): length 0x104 vs retail 0x108 (4 short), close. */
#include "types.h"

extern void ActTimeClsnInit_227c30(s32, f32, s32, f32, s32);
extern void ClsnInfoSetForce_228190(s32, f32);
extern s32 ScriptArgGetStr_23fba0(s32);
extern f32 ScriptArgGetFloat_23fbc0(s32);
extern s32 StrDupArena_23fc40(s32);
extern s32 D_00481EB0;
extern s32 D_00481EB4;

s32 ActTimeClsn_23bd30(s32 arg0, s32 arg1)
{
    f32 temp_f20;
    f32 temp_f21;
    s32 temp_19;
    s32 temp_18;

    if (arg1 < 4) {
        return 0;
    }
    if ((D_00481EB0 == 0) || (D_00481EB4 >= 0x40)) return 1;
    temp_19 = D_00481EB0 + (D_00481EB4 << 5);
    temp_f21 = ScriptArgGetFloat_23fbc0(arg0);
    temp_f20 = ScriptArgGetFloat_23fbc0(arg0 + 8);
    temp_18 = StrDupArena_23fc40(ScriptArgGetStr_23fba0(arg0 + 0x10));
    ActTimeClsnInit_227c30(temp_19, temp_f21, temp_18, temp_f20, StrDupArena_23fc40(ScriptArgGetStr_23fba0(arg0 + 0x18)));
    if (arg1 > 4) {
        ClsnInfoSetForce_228190(temp_19 + 4, ScriptArgGetFloat_23fbc0(arg0 + 0x20));
    }
    D_00481EB4 += 1;
    return 1;
    return 1;
}
