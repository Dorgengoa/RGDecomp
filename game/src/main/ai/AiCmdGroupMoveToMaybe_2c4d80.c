/* rgp:protos */
#define RGP_SELF_AiCmdGroupMoveToMaybe_2c4d80 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#include "vec.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern s32 D_004DB928[4];

s32 AiCmdGroupMoveToMaybe_2c4d80(s64 *arg0, s32 arg1)
{
    s32 temp_21;
    s32 temp_16;
    s32 var_20;
    s32 temp_17;
    f32 vecTmp[4] __attribute__((aligned(16)));
    s32 temp_2;
    s32 temp_2_2;
    s32 var_19;
    void *temp_2_3;
    s32 sp70[0x80] __attribute__((aligned(16)));

    temp_21 = ((s32)GetActionMgr_1fdb50());
    temp_16 = ScriptSlotGetInt_2cc9c0((s32)arg0++);
    vecTmp[0] = ScriptSlotGetFloat_2cc9a0((s32)arg0++);
    vecTmp[1] = ScriptSlotGetFloat_2cc9a0((s32)arg0++);
    vecTmp[2] = ScriptSlotGetFloat_2cc9a0((s32)arg0++);
    vecTmp[3] = ScriptSlotGetFloat_2cc9a0((s32)arg0++);
    var_20 = 0x5A;
    if (arg1 >= 6) {
        var_20 = ScriptSlotGetInt_2cc9c0((s32)arg0);
    }
    temp_17 = D_004DB928[0];
    temp_2 = AiCollectIdsByGroup_2cd1a0(temp_17, temp_16, sp70, 0x80);
    if (temp_2 == 0) {
        return 1;
    }
    var_19 = 0;
    while (var_19 < temp_2) {
        temp_2_2 = ((s32)ActionMgrFindById_233b50(temp_21, sp70[var_19]));
        if (temp_2_2 != 0) {
            temp_2_3 = CharaGetAi_214a10(temp_2_2);
            if (temp_2_3 != NULL) {
                AiSetState_2bbc40(temp_2_3, 0x26C);
                *(s16 *)((u8 *)temp_2_3 + 0x144) = (s16)temp_17;
                *(u128 *)((u8 *)temp_2_3 + 0xC0) = *(u128 *)vecTmp;
                *(s16 *)((u8 *)temp_2_3 + 0x146) = var_20;
            }
        }
        var_19 += 1;
    }
    return 1;
}
