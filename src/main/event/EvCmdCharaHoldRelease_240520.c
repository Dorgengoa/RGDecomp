#include "types.h"
#pragma optimization_level 3

extern s32 GetActionMgr_1fdb50(void);
typedef struct { u8 pad[0x10]; s32 unk10; u8 pad14[4]; s32 unk18; } S240520;
extern S240520 *GetGameData_1fede0(void);
extern void CharaResetBattleStateMaybe_212f20(s32, s32);
extern s32 ActionMgrFindById_233b50(s32, s32);
extern void TaskSetEnabled_27c2a0(s32, void *);
extern s32 PartyCountMembers_3c2010(s32, s32, s32);
extern s32 PartyGetMemberId_3c2490(s32, u32);
extern s32 StateFlagTest_3ccd70(s32, s32);
extern u8 D_0045E9A8[0x400];

s32 EvCmdCharaHoldRelease_240520(void) {
    s32 arg_h1;

    u32 var_19;
    s32 temp_18;
    s32 temp_2_2;
    s32 temp_17;
    S240520 *temp_2;

    temp_2 = GetGameData_1fede0();
    arg_h1 = 0x7F1;
    if (StateFlagTest_3ccd70(temp_2->unk10, arg_h1) == 0) {
        arg_h1 = 1;
        temp_18 = PartyCountMembers_3c2010(temp_2->unk18, arg_h1, arg_h1);
        var_19 = 0;
        while ((s32)var_19 < (s32)temp_18) {
            temp_17 = PartyGetMemberId_3c2490(temp_2->unk18, var_19);
            temp_2_2 = ActionMgrFindById_233b50(GetActionMgr_1fdb50(), temp_17);
            if (temp_2_2 != 0) {
                CharaResetBattleStateMaybe_212f20(temp_2_2, 1);
            }
            var_19 += 1;
        }
    }
    TaskSetEnabled_27c2a0(0, &(*(u8 *)D_0045E9A8));
    return 1;
}
