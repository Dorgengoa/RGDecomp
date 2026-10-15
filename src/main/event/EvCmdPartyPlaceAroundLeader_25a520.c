#pragma opt_propagation off
#pragma opt_loop_invariants off
#include "types.h"

f32 AngleWrap_1cbf30(f32);                                /* extern */
s32 GetActionMgr_1fdb50();                                 /* extern */
u8 *GetGameData_1fede0();                               /* extern */
s32 ActionMgrFindById_233b50(s32, s16);                         /* extern */
s32 CharaGetPos_2388a0(s32, u8 *);                           /* extern */
s32 CharaGetRot_2388b0(s32, u8 *);                           /* extern */
s32 CharaPlaceAtOffset_2f3910(s32, u8 *, s32, f32, f32);                /* extern */
s32 PartyCountExcludingLeader_3c2610(s32, s32, s32);                     /* extern */
s32 PartyGetNonLeaderId_3c2750(s32, s32);                      /* extern */
extern f32 D_0047DCAC;

s32 EvCmdPartyPlaceAroundLeader_25a520(void) {
    u8 sp60[0x10];
    u8 sp50[0x10];
    s32 temp_18;
    u8 *temp_16;
    s32 var_19;
    s32 n;
    s32 temp_2;
    s32 temp_17;

    temp_16 = GetGameData_1fede0();
    temp_2 = ActionMgrFindById_233b50(GetActionMgr_1fdb50(), *(s16 *)(*(u8 **)(temp_16 + 0x18) + 0x18E));
    if (temp_2 != 0) {
        CharaGetPos_2388a0(temp_2, sp60);
        CharaGetRot_2388b0(temp_2, sp50);
        n = PartyCountExcludingLeader_3c2610(*(s32 *)(temp_16 + 0x18), 1, 1);
        temp_18 = n;
        for (var_19 = 0; var_19 < temp_18; var_19++) {
            temp_17 = PartyGetNonLeaderId_3c2750(*(s32 *)(temp_16 + 0x18), var_19);
            CharaPlaceAtOffset_2f3910(temp_17, sp60, 0,
                         AngleWrap_1cbf30(*(f32 *)&sp50[4] +
                                      D_0047DCAC * (f32)(((var_19 & 1) * 2) - 1)),
                         40.0f);
        }
    }
    return 1;
}
