/* PARK 1/3: length-wrong (120w vs retail 121w), close. */
#include "types.h"

s32 ParseFlagNames_1ca940(s32, void *, u8 *);
s32 ScriptArgGetStr_301a00(void);
s32 EventStrDup_301aa0(s32);
s32 GetEvScriptCallTable_301dc0(void);
void ScriptCallSetArgc_302a90(s32, s32);
s32 ScriptCallGetArgc_302aa0(s32);
s32 ScriptCallGetArgs_302ab0(s32);
void ScriptCallInit_302ad0(s32, s32, s32, s32, s32);
void VariantSetString_302e00(s32, s32);
void VariantSetFloat_302e40(s32, f32);
void VariantSetInt_302e80(s32, s32);
s32 NameValueTableLookup_302f50(s32, s32);
extern u8 D_00451DE0[];
extern s32 D_00482820;
extern s32 D_00482824;
extern s32 D_00482828;
extern s32 D_0048282C;

s32 EvScriptCmdScriptRecAddCall_3016b0(u8 *arg0, s32 arg1) {
    u8 sp6F;
    s32 temp_16;
    s32 temp_18;
    s32 temp_2;
    s32 temp_2_2;
    s32 temp_3;
    s32 temp_8;
    s32 var_17;
    s32 var_16;

    if ((arg1 <= 0) || (arg1 > 0x401)) {
        return 0;
    }
    if (D_00482828 == 0 || D_0048282C >= 0x40) {
        return 1;
    }
    temp_16 = ScriptArgGetStr_301a00();
    temp_2 = NameValueTableLookup_302f50(GetEvScriptCallTable_301dc0(), temp_16);
    if (temp_2 == 0) {
        return 0;
    }
    arg0 += 8;
    temp_8 = D_0048282C * 0xC;
    temp_18 = D_00482828 + temp_8;
    ScriptCallInit_302ad0(temp_18, temp_2, D_00482820 + (D_00482824 * 5), 0, temp_8);
    var_17 = ScriptCallGetArgs_302ab0(temp_18);
    var_16 = 1;
    while (var_16 < arg1) {
        if (D_00482824 >= 0x40) {
            return 0;
        }
        temp_3 = *(s32 *)(arg0 + 0);
        switch (temp_3) {
        case 0:
            temp_2_2 = ParseFlagNames_1ca940(*(s32 *)(arg0 + 4), D_00451DE0, &sp6F);
            if (sp6F != 0) {
                VariantSetInt_302e80(var_17, temp_2_2);
            } else {
                VariantSetString_302e00(var_17, EventStrDup_301aa0(*(s32 *)(arg0 + 4)));
            }
            break;
        case 1:
            VariantSetInt_302e80(var_17, *(s32 *)(arg0 + 4));
            break;
        case 2:
            VariantSetFloat_302e40(var_17, *(f32 *)(arg0 + 4));
            break;
        }
        arg0 += 8;
        var_17 += 5;
        ScriptCallSetArgc_302a90(temp_18, ScriptCallGetArgc_302aa0(temp_18) + 1);
        var_16 += 1;
        D_00482824 += 1;
    }
    D_0048282C += 1;
    return 1;
}
