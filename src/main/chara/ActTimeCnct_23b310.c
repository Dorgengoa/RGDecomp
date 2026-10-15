/* MATCH (s41m). Stale pre-match note follows -- PARK (round 1): length 0x134 vs retail 0x12C. */
#include "types.h"

extern s32 ActCfgTableFindCmndByName_222db0(s32, s32);
extern void ActTimeCnctInit_227420(s32, f32, s32, f32, f32, f32);
extern s32 ScriptArgGetStr_23fba0(s32);
extern f32 ScriptArgGetFloat_23fbc0(s32);
extern s32 D_00481ED8;
extern s32 D_00481EDC;
extern s32 D_00481EEC;

#define S32(p, o) (*(s32 *)((u8 *)(p) + (o)))

s32 ActTimeCnct_23b310(s32 arg0, s32 arg1)
{
    f32 temp_f20;
    f32 temp_f21;
    f32 temp_f22;
    f32 var_f23;
    s32 temp_17;

    if ((arg1 != 4) && (arg1 != 5)) {
        return 0;
    }
    if ((D_00481ED8 == 0) || (D_00481EDC >= 0x40)) return 1;
    temp_17 = D_00481ED8 + (D_00481EDC * 0x14);
    if (arg1 == 5) {
        var_f23 = ScriptArgGetFloat_23fbc0(arg0 + 0x20);
    } else {
        var_f23 = 1.0f;
    }
    temp_f22 = ScriptArgGetFloat_23fbc0(arg0);
    temp_f21 = ScriptArgGetFloat_23fbc0(arg0 + 8);
    temp_f20 = ScriptArgGetFloat_23fbc0(arg0 + 0x10);
    ActTimeCnctInit_227420(temp_17, temp_f22, ActCfgTableFindCmndByName_222db0(D_00481EEC, ScriptArgGetStr_23fba0(arg0 + 0x18)), temp_f21, temp_f20, var_f23);
    if (S32(temp_17, 0xC) == 0) {
        return 1;
    }
    D_00481EDC += 1;
    return 1;
}
