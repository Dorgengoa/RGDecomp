/* rgp:protos */
#define RGP_SELF_BattleRebindEncounterMaybe_2f2d90 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* A caller inside the SetGameModePhase_1f59a0 family's phase space: it forces the phase
   to 0x1004, steps the big driver twice, and restores the saved phase. */

struct Root {
    u8  pad0[0x20];
    s32 m20;
};

extern s16 D_004821E8;

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

void BattleRebindEncounterMaybe_2f2d90(s32 idx)
{
    s32 saveA;
    s32 saveB;
    struct Root *root;

    if (GetGameModeAt_1f5830(0) == 0xB && GetGameModeAt_1f5830(1) == 7) {
        saveA = GetGameMode_1f59c0();
        saveB = GetGameModePhase_1f59b0();
        GameModeStackPop_1f58a0();
        SetGameModePhase_1f59a0(0x1004);
        BattleModeUpdate_280220();
        BattleModeUpdate_280220();
        SetGameReqHold_1f5890();
        root = ((struct Root *)GetGameData_1fede0());
        GameDataBattleBroadcastPhase_3e6890(root, 0);
        if (idx >= 0 && CharaSysEncounterBindAndStartMaybe_3a5340(root->m20, idx, D_004821E8, 0) >= 0) {
            SetGameModePhase_1f59a0(2);
        }
        GameModeStackPush_1f58f0(saveA, saveB);
    }
}
