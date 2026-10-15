#include "types.h"

extern char *ScriptArgGetStr_30aaf0(s32 arg0);
extern f32 VariantGetFloat_30ab10(s32 arg0);
extern s32 NavGraphGetNode_310cd0(s32 arg0, s32 arg1);
extern s32 NavGraphStrPoolAdd_30f390(s32 arg0, char *arg1);
extern s32 NavGraphAddNodeXYZ_30f6b0(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4);
extern void NavNodeSetFlags_3118a0(s32 arg0, s32 arg1);
extern void NavNodeSetLinkName_3118b0(s32 arg0, s32 arg1);
extern s32 ParseFlagNames_1ca700(char *arg0, void *arg1, s32 arg2);
extern s32 strcmp(char *arg0, void *arg1);
extern s32 D_0048296C;
extern u8 D_00452300[0x400];
extern u8 D_004622F0[0x400];

s32 NavCfgCmdAddNode_30a8b0(s32 arg0, s32 arg1)
{
    f32 temp_f20;
    f32 temp_f21;
    s32 temp_2;
    s32 temp_2_2;
    char *temp_2_3;

    if ((arg1 < 3) && (arg1 > 5)) {
        return 0;
    }
    if (D_0048296C == 0) {
        return 1;
    }
    temp_f21 = VariantGetFloat_30ab10(arg0);
    temp_f20 = VariantGetFloat_30ab10(arg0 + 8);
    temp_2 = NavGraphAddNodeXYZ_30f6b0(D_0048296C, temp_f21, temp_f20, VariantGetFloat_30ab10(arg0 + 0x10), 0.0f);
    if (temp_2 < 0) {
        return 1;
    }
    temp_2_2 = NavGraphGetNode_310cd0(D_0048296C, temp_2);
    if (temp_2_2 == 0) {
        return 1;
    }
    if (arg1 >= 4) {
        temp_2_3 = ScriptArgGetStr_30aaf0(arg0 + 0x18);
        if (strcmp(temp_2_3, D_004622F0) != 0) {
            NavNodeSetLinkName_3118b0(temp_2_2, NavGraphStrPoolAdd_30f390(D_0048296C, temp_2_3));
        }
    }
    if (arg1 >= 5) {
        NavNodeSetFlags_3118a0(temp_2_2, ParseFlagNames_1ca700(ScriptArgGetStr_30aaf0(arg0 + 0x20), D_00452300, 0));
    }
    return 1;
}
