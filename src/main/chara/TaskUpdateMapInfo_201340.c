#include "types.h"
#pragma peephole off

extern s32 GetActionMgr_1fdb50(void);
extern void *GetGameData_1fede0(void);
extern void MapUpdatePlayerLocationMaybe_1ff710(void *arg0, void *arg1);
extern s32 ActionMgrFindById_233b50(s32 arg0, s32 arg1);
extern void CharaGetPos_2388a0(s32 arg0, void *arg1);
extern void CharaGetRot_2388b0(s32 arg0, void *arg1);
extern s32 PartyGetMemberId_3c2490(s32 arg0, s32 arg1);

void TaskUpdateMapInfo_201340(void)
{
    f32 spC0[3];
    u8 spA0[3][0x10];
    u8 sp80[0x10];
    s32 temp_21;
    s32 temp_2_2;
    s32 var_20;
    s32 var_19;
    s32 temp_2_3;
    void *temp_16;
    u8 *temp_17;

    temp_16 = GetGameData_1fede0();
    temp_21 = GetActionMgr_1fdb50();
    if (temp_16 == NULL || temp_21 == 0) {
        return;
    }
    {
        var_20 = 0;
        var_19 = 0;
        do {
            temp_17 = spA0[var_19];
            *(s32 *)(temp_17 + 0x0) = 0;
            *(s32 *)(temp_17 + 0x4) = 0;
            *(s32 *)(temp_17 + 0x8) = 0;
            *(s32 *)(temp_17 + 0xC) = 0;
            *(s32 *)&spC0[var_19] = 0;
            temp_2_2 = PartyGetMemberId_3c2490(*(s32 *)((u8 *)temp_16 + 0x18), var_19);
            if (temp_2_2 >= 0) {
                temp_2_3 = ActionMgrFindById_233b50(temp_21, temp_2_2);
                if (temp_2_3 != 0) {
                    CharaGetPos_2388a0(temp_2_3, temp_17);
                    CharaGetRot_2388b0(temp_2_3, sp80);
                    spC0[var_19] = *(f32 *)(sp80 + 0x4);
                    if (var_19 == 0) {
                        var_20 = temp_2_3;
                    }
                }
            }
            var_19 += 1;
        } while (var_19 < 3);
        if (var_20 != 0) {
            MapUpdatePlayerLocationMaybe_1ff710(spA0, spC0);
        }
    }
}
