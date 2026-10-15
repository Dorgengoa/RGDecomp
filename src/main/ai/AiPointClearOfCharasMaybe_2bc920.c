/* MATCH (s41m). Stale pre-match note follows -- PARK 1/3: RIGHT LENGTH (93w), 19 bad. */
#include "types.h"

f32 VecDistSq_1cb3c0(void *, void *);
s32 GetActionMgr_1fdb50(void);
s32 CharaGetActionMode_213850(s32);
s32 CharaGetId_214a80(s32);
s32 ActionMgrGetCharaList_233b40(s32);
void CharaGetPos_2388a0(s32, void *);
s32 DListGetHead_42ea60(s32);
s32 DListGetNext_42eb30(s32);

s32 AiPointClearOfCharasMaybe_2bc920(u8 *arg0, s32 arg1, u8 *arg2) {
    u8 sp90[16];
    u8 sp80[16];
    f32 temp_f21;
    f32 var_f20;
    s32 temp_16;
    s32 temp_20;
    s32 temp_21;
    s32 var_16;

    if (arg1 == 0) {
        return 0;
    }
    temp_16 = GetActionMgr_1fdb50();
    CharaGetPos_2388a0(arg1, sp90);
    temp_f21 = VecDistSq_1cb3c0(arg2, sp90);
    var_16 = DListGetHead_42ea60(ActionMgrGetCharaList_233b40(temp_16));
    while (var_16 != 0) {
        temp_21 = var_16 + 0x10;
        var_16 = DListGetNext_42eb30(var_16);
        temp_20 = CharaGetId_214a80(temp_21);
        if (temp_20 != CharaGetId_214a80(arg1)) {
            CharaGetPos_2388a0(temp_21, sp80);
            var_f20 = 800.0f;
            if (CharaGetActionMode_213850(temp_21) == 4) {
                var_f20 = 1600.0f;
            }
            if (VecDistSq_1cb3c0(arg2, sp80) < var_f20) {
                *(s8 *)(arg0 + 0x262) = -0xF;
                return 0;
            }
            if ((VecDistSq_1cb3c0(sp90, sp80) < var_f20) && !(temp_f21 <= VecDistSq_1cb3c0(arg2, sp80))) {
                *(s8 *)(arg0 + 0x262) = -0xF;
                return 0;
            }
        }
    }
    return 1;
}
