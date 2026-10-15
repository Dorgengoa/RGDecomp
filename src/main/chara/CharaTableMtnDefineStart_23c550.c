#include "types.h"

extern s32 ParseFlagNames_1ca700(s32, void *, s32);
extern s32 CharaTableGetStepCount_225410(void *);
extern s32 CharaTableGetStepArray_225470(void *);
extern void CharaTableEntryInit_226380(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
extern s32 ScriptArgGetStr_23fba0(s32);
extern s32 StrDupArena_23fc40(s32);
extern u8 D_0044C500[];
extern u8 D_0044C6A0[];
extern s32 D_00481EA0;
extern s32 D_00481EA4;
extern s32 D_00481EA8;
extern s32 D_00481EAC;
extern s32 D_00481EB0;
extern s32 D_00481EB4;
extern s32 D_00481EB8;
extern s32 D_00481EBC;
extern s32 D_00481EC0;
extern s32 D_00481EC4;
extern s32 D_00481EC8;
extern s32 D_00481ECC;
extern s32 D_00481ED0;
extern s32 D_00481ED4;
extern s32 D_00481ED8;
extern s32 D_00481EDC;
extern u8 D_004BCDE0[];

s32 CharaTableMtnDefineStart_23c550(s32 arg0, s32 arg1)
{
    s32 temp_16;
    s32 temp_20;
    s32 temp_19;
    s32 var_2;
    s32 var_2_2;

    if ((arg1 != 1) && (arg1 != 2) && (arg1 != 3)) {
        return 0;
    }
    if (CharaTableGetStepArray_225470(D_004BCDE0) == 0 || CharaTableGetStepCount_225410(D_004BCDE0) >= 0x10) {
        return 1;
    }
    temp_16 = CharaTableGetStepArray_225470(D_004BCDE0);
    temp_20 = temp_16 + (CharaTableGetStepCount_225410(D_004BCDE0) * 0x44);
    temp_19 = StrDupArena_23fc40(ScriptArgGetStr_23fba0(arg0));
    if (arg1 > 1) {
        var_2 = ParseFlagNames_1ca700(ScriptArgGetStr_23fba0(arg0 + 8), D_0044C500, 0);
    } else {
        var_2 = 0;
    }
    if (arg1 > 2) {
        var_2_2 = ParseFlagNames_1ca700(ScriptArgGetStr_23fba0(arg0 + 0x10), D_0044C6A0, 0);
    } else {
        var_2_2 = -1;
    }
    CharaTableEntryInit_226380(temp_20, temp_19, var_2, var_2_2,
                  D_00481EA0 + (D_00481EA4 * 8), 0,
                  D_00481EA8 + (D_00481EAC * 0x10), 0,
                  D_00481EB0 + (D_00481EB4 << 5), 0,
                  D_00481EB8 + (D_00481EBC * 0x10), 0,
                  D_00481EC0 + (D_00481EC4 * 0x14), 0,
                  D_00481EC8 + (D_00481ECC * 0x10), 0,
                  D_00481ED0 + (D_00481ED4 * 0x14), 0,
                  D_00481ED8 + (D_00481EDC * 0x14), 0);
    return 1;
}
