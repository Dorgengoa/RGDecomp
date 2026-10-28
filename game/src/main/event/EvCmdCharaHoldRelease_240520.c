/* rgp:protos */
#define RGP_SELF_EvCmdCharaHoldRelease_240520 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma optimization_level 3

/*rgp*/
typedef struct { u8 pad[0x10]; s32 unk10; u8 pad14[4]; s32 unk18; } S240520;
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern u8 D_0045E9A8[0x400];

s32 EvCmdCharaHoldRelease_240520(void) {
    s32 arg_h1;

    u32 var_19;
    s32 temp_18;
    s32 temp_2_2;
    s32 temp_17;
    S240520 *temp_2;

    temp_2 = ((S240520 *)GetGameData_1fede0());
    arg_h1 = 0x7F1;
    if (StateFlagTest_3ccd70(temp_2->unk10, arg_h1) == 0) {
        arg_h1 = 1;
        temp_18 = PartyCountMembers_3c2010(temp_2->unk18, arg_h1, arg_h1);
        var_19 = 0;
        while ((s32)var_19 < (s32)temp_18) {
            temp_17 = ((short)PartyGetMemberId_3c2490(temp_2->unk18, var_19));
            temp_2_2 = ((s32)ActionMgrFindById_233b50(((s32)GetActionMgr_1fdb50()), temp_17));
            if (temp_2_2 != 0) {
                CharaResetBattleStateMaybe_212f20(temp_2_2, 1);
            }
            var_19 += 1;
        }
    }
    TaskSetEnabled_27c2a0(0, &(*(u8 *)D_0045E9A8));
    return 1;
}
