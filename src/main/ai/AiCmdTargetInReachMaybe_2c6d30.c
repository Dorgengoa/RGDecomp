#pragma opt_propagation off
#include "types.h"

extern s32 CharaGetFrontTargetRefMaybe_214a20(s32 arg0);
extern f32 CharaGetCollRadius_2386a0(s32 arg0);
extern void CharaGetPos_2388a0(s32 arg0, void *arg1);
extern void CharaGetRot_2388b0(s32 arg0, void *arg1);
extern void ScriptSlotStoreIntRef_2cc900(s32 arg0, s32 arg1);
extern s32 TargetFindInFrontMaybe_2d0aa0(s32 arg0, void *arg1, f32 arg2, f32 arg3);
extern s32 D_004DB92C[];
extern f32 D_0045B080[];

s32 AiCmdTargetInReachMaybe_2c6d30(s32 arg0)
{
    u8 sp60[0x10];
    u8 sp50[0x10];
    s32 temp_17;
    s32 temp_16;

    temp_17 = D_004DB92C[0];
    CharaGetPos_2388a0(temp_17, &sp60);
    CharaGetRot_2388b0(temp_17, &sp50);
    temp_16 = CharaGetFrontTargetRefMaybe_214a20(temp_17);
    if (TargetFindInFrontMaybe_2d0aa0(temp_16, &sp60, *(f32 *)&sp50[4],
                      CharaGetCollRadius_2386a0(temp_17) + 1.5f * D_0045B080[0]) != 0) {
        ScriptSlotStoreIntRef_2cc900(arg0, 1);
    } else {
        ScriptSlotStoreIntRef_2cc900(arg0, 0);
    }
    return 0;
}
