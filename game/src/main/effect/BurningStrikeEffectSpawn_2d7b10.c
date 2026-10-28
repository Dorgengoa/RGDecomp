/* rgp:protos */
#define RGP_SELF_BurningStrikeEffectSpawn_2d7b10 1
#include "port/game_protos.h"
#line 1
#include "types.h"

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
/*rgp*/
/*rgp*/
extern f32 D_0045B080[];
extern u8 D_00461660[];

typedef struct { f32 x, y, z, w; } V4;

void BurningStrikeEffectSpawn_2d7b10(s32 arg0, f32 fparg0) {
    V4 sp90 __attribute__((aligned(16)));
    u8 sp70[0x20] __attribute__((aligned(16)));
    s32 temp_16;
    s32 temp_2;
    s32 var_20;
    u8 *temp_2_2;
    u8 *temp_18;

    temp_2 = ((s32)ActionMgrFindById_233b50(((s32)GetActionMgr_1fdb50()), arg0));
    if (temp_2 != 0) {
        temp_18 = ((u8 *)GetGameData_1fede0());
        temp_16 = ((s32)GetEffectMgr_2d9040());
        CharaGetPos_2388a0(temp_2, &sp90);
        sp90.y += D_0045B080[0];
        var_20 = 0;
        do {
            temp_2_2 = ((u8 *)CharaSysStatusGet_3a1770(*(s32 *)(temp_18 + 0x20), var_20, 0));
            if (StatusEntryIsStartPending_3a61f0(temp_2_2) != 0) {
                EffectCreateByName_2e1020(sp70, temp_16, D_00461660, -1);
                EffectSetPos_2e0bb0(temp_16, sp70, &sp90);
                EffectSetId_2e0100(temp_16, sp70, arg0);
                EffectSetParamInt_2e0530(temp_16, sp70, 0, *temp_2_2);
                EffectSetParamFloat_2e0600(temp_16, sp70, 1, fparg0);
                EffectStep_2e0e00(temp_16, sp70);
                StatusEntryClearStartPending_3a5fb0(temp_2_2, 0);
            }
            var_20 += 1;
        } while (var_20 < 0x20);
    }
}
