/* rgp:protos */
#define RGP_SELF_EvCmdEventPlayerEnd_260f30 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Ctx00260f30 {
    u8 pad0[0x10];
    s32 unk10;
    u8 pad14[4];
    s32 unk18;
} Ctx00260f30;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern u8 D_0045F0E8[0x400];
extern s32 D_0047E960;
extern void *D_00481F78;
extern s32 D_00482040;

s32 EvCmdEventPlayerEnd_260f30(void)
{
    Ctx00260f30 *temp_2;
    s32 var_19;
    s32 temp_2_2;
    u32 temp_18;
    s32 temp_17;

    if (D_00482040 == 0) {
        return 0;
    }
    CharaResMgrSetMonSndLoad_1f0050(((s32)GetCharaResMgr_1fdb60()), 1);
    EventPlayerEnd_249480(D_00482040, D_00481F78);
    D_00482040 = 0;
    *(s32 *) ((u8 *) D_00481F78 + 0x4344) = D_0047E960;
    temp_2 = ((Ctx00260f30 *)GetGameData_1fede0());
    if (StateFlagTest_3ccd70(temp_2->unk10, 0x7F1) == 0) {
        temp_18 = PartyCountMembers_3c2010(temp_2->unk18, 1, 1);
        var_19 = 0;
        while (var_19 < (s32)temp_18) {
            temp_17 = ((short)PartyGetMemberId_3c2490(temp_2->unk18, var_19));
            temp_2_2 = ((s32)ActionMgrFindById_233b50(((s32)GetActionMgr_1fdb50()), temp_17));
            if (temp_2_2 != 0) {
                CharaResetBattleStateMaybe_212f20(temp_2_2, 1);
            }
            var_19 += 1;
        }
    }
    TaskSetEnabled_27c2a0(0, &(*(u8 *)D_0045F0E8));
    StateFlagSet_3ccb70(temp_2->unk10, 0x7E4, 0, 1);
    return 1;
}
